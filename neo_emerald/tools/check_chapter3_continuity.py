#!/usr/bin/env python3
"""Source gates for Chapter 3 and Neo continuity."""
from pathlib import Path
import json
R=Path(__file__).resolve().parents[2]
def read(p): return (R/p).read_text()
def sc(n): return read("data/maps/"+n+"/scripts.inc")
def mp(n): return json.loads(read("data/maps/"+n+"/map.json"))
office=sc("RustboroCity_Flat1_1F")
assert "goto_if_unset FLAG_NEO_C2_DEBRIEF_DONE, NeoOffice_Early" in office
assert "goto_if_unset FLAG_BADGE01_GET, NeoOffice_Badge" in office
assert "setvar VAR_NEO_CH3_STEP, 6" in office
assert any(o["script"]=="NeoOffice_Hale" for o in mp("RustboroCity_Flat1_1F")["object_events"])
route=sc("Route116")
assert "goto_if_ne VAR_NEO_CH3_STEP, 6, NeoTreeWait" in route
assert "setflag FLAG_NEO_ROUTE116_CLEAR" in route
assert any(o["flag"]=="FLAG_NEO_ROUTE116_CLEAR" and o["script"]=="NeoPlayerCutter" for o in mp("Route116")["object_events"])
tunnel=sc("RusturfTunnel")
for a,b in [(7,11),(11,12),(12,8)]:
    assert f"goto_if_ne VAR_NEO_CH3_STEP, {a}," in tunnel
    assert f"setvar VAR_NEO_CH3_STEP, {b}" in tunnel
assert "THIRD SIGNAL: ORIGIN UNKNOWN" in tunnel
assert "trainerbattle_no_intro TRAINER_NEO_TUNNEL" in tunnel
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, RusturfTunnel_OnFrame" not in tunnel
assert not any("AquaGruntBackUp" in e["script"] for e in mp("RusturfTunnel")["coord_events"])
assert "OBJ_EVENT_GFX_STEVEN" in read("data/maps/RustboroCity_DevonCorp_3F/map.json")
assert "BRENDAN carries the Champion" in sc("RustboroCity_DevonCorp_3F")
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame" not in sc("RustboroCity_DevonCorp_3F")
for n in ["PetalburgWoods","Route104_MrBrineysHouse","RustboroCity"]:
    assert "M-17" in sc(n)
assert "Volcanion's power" not in sc("Route104")
print("Chapter 3 source and continuity checks passed (runtime test still required)")

# Field Log dispatch regression checks. Interpret only the tiny supported
# branch subset; fail closed if the dispatcher acquires another opcode.
import re
log = read("data/scripts/neo_field_log.inc").splitlines()
labels = {line.rstrip(":"): i for i, line in enumerate(log)
          if re.fullmatch(r"[A-Za-z_]\w*::?", line)}
def objective(flags, step=9):
    pc = labels["NeoRanger_FieldLog"] + 1
    for _ in range(100):
        line = log[pc].strip()
        pc += 1
        if not line or line == "lockall" or line.endswith(":"):
            continue
        match = re.fullmatch(r"goto_if_(set|unset) (\w+), (\w+)", line)
        if match:
            mode, flag, target = match.groups()
            if (flag in flags) == (mode == "set"):
                pc = labels[target] + 1
            continue
        match = re.fullmatch(r"goto_if_(eq|ge) (\w+), (\d+), (\w+)", line)
        if match:
            mode, var, value, target = match.groups()
            current = {"VAR_NEO_CH3_STEP": step, "VAR_NEO_FERRY_DISPATCH": 5}[var]
            if (current == int(value) if mode == "eq" else current >= int(value)):
                pc = labels[target] + 1
            continue
        match = re.fullmatch(r"msgbox (\w+), MSGBOX_DEFAULT", line)
        if match:
            assert match[1] in labels, match[1]
            return match[1]
        raise AssertionError(f"Unexpected Field Log dispatch instruction: {line}")
    raise AssertionError("Field Log failed to resolve an objective")

cases = [
    ([], "NeoLog_RefugeText"),
    (["CREW_CHECKED"], "NeoLog_GaugeText"),
    (["READING_CHECKED"], "NeoLog_BunksText"),
    (["CREW_CHECKED", "READING_CHECKED"], "NeoLog_CaveReportText"),
    (["CREW_CHECKED", "READING_CHECKED", "SURVEY"], "NeoLog_SailHomeText"),
    (["CREW_CHECKED", "READING_CHECKED", "SURVEY", "REPORTED"], "NeoLog_FiledText"),
]
for suffixes, expected in cases:
    flags = {"FLAG_NEO_C4_" + suffix for suffix in ["BRIEF"] + suffixes}
    assert objective(flags) == expected, (flags, expected)
assert objective(set()) == "NeoLog_DewfordText"
assert objective({"FLAG_NEO_C2_BRINEY_REPORTED"}, step=0) == "NeoLog_LiaisonText"

# Verify the newly referenced contacts and reciprocal cave warps exist.
assert any(o["script"] == "RustboroCity_EventScript_NeoCampusFieldStudent"
           for o in mp("RustboroCity")["object_events"])
hall = mp("GraniteCave_RefugeHall")
station = mp("GraniteCave_SurveyStation")
entrance = mp("GraniteCave_1F")
assert any(o["script"] == "GraniteCave_NeoRefugeCrew" for o in hall["object_events"])
assert any(o["script"] == "GraniteCave_NeoRefugeSurveyor" for o in station["object_events"])
cave_maps = {m["id"]: m for m in (hall, station, entrance)}
for source in cave_maps.values():
    for i, warp in enumerate(source["warp_events"]):
        if warp["dest_map"] not in cave_maps:
            continue
        back = cave_maps[warp["dest_map"]]["warp_events"][int(warp["dest_warp_id"])]
        assert back["dest_map"] == source["id"] and int(back["dest_warp_id"]) == i
print("Field Log dispatch and refuge warp references passed (static only)")
