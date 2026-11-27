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
def objective(flags, step=9, boat=0, dispatch=5):
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
            current = {"VAR_NEO_CH3_STEP": step, "VAR_NEO_FERRY_DISPATCH": dispatch, "VAR_BOARD_BRINEY_BOAT_STATE": boat}[var]
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
brief = {"FLAG_NEO_C4_BRIEF"}
survey = brief | {"FLAG_NEO_C4_CREW_CHECKED", "FLAG_NEO_C4_READING_CHECKED", "FLAG_NEO_C4_SURVEY"}
assert objective(brief, boat=2) == "NeoLog_DewfordText"
assert objective({"FLAG_VISITED_DEWFORD_TOWN"}) == "NeoLog_DewfordBriefText"
assert objective({"FLAG_VISITED_DEWFORD_TOWN"}, boat=2) == "NeoLog_DewfordText"
assert objective(survey, boat=0) == "NeoLog_SailHomeText"
assert objective(survey, boat=2) == "NeoLog_HaleReportText"
assert objective(survey | {"FLAG_NEO_C4_REPORTED"}, boat=2) == "NeoLog_FiledText"
assert objective({"FLAG_NEO_C2_DEBRIEF_DONE"}, step=0) == "NeoLog_BadgeText"
assert objective({"FLAG_NEO_C2_DEBRIEF_DONE", "FLAG_BADGE01_GET"}, step=0) == "NeoLog_CertificationText"
assert objective(set(), step=0, dispatch=2) == "NeoLog_SailorText"
assert objective(set(), step=0, dispatch=3) == "NeoLog_RescueText"
assert objective(set(), step=0, dispatch=4) == "NeoLog_DockText"
assert objective(set(), step=0, dispatch=5) == "NeoLog_HaleText"
assert objective({"FLAG_NEO_C1_FLIGHT_RUSTBORO"}, step=0) == "NeoLog_RivalText"
assert objective({"FLAG_NEO_C2_BRINEY_REPORTED"}, step=0) == "NeoLog_LiaisonText"

# Verify the newly referenced contacts and reciprocal cave warps exist.
assert any(o["script"] == "RustboroCity_EventScript_NeoCampusFieldStudent"
           for o in mp("RustboroCity")["object_events"])
hall = mp("GraniteCave_RefugeHall")
station = mp("GraniteCave_SurveyStation")
entrance = mp("GraniteCave_1F")
assert any(o["script"] == "GraniteCave_NeoRefugeCrew" for o in hall["object_events"])
assert any(o["script"] == "GraniteCave_NeoRefugeSurveyor" for o in station["object_events"])
annex = mp("GraniteCave_ResidentialAnnex")
cave_maps = {m["id"]: m for m in (hall, station, entrance, annex)}
for source in cave_maps.values():
    for i, warp in enumerate(source["warp_events"]):
        if warp["dest_map"] not in cave_maps:
            continue
        back = cave_maps[warp["dest_map"]]["warp_events"][int(warp["dest_warp_id"])]
        assert back["dest_map"] == source["id"] and int(back["dest_warp_id"]) == i
print("Field Log dispatch and refuge warp references passed (static only)")


# The residential annex must be included in the same release gate.
# Verify the actual little-endian engine blockdata from the checkout, not
# rendered previews or remotely transported binary data.
import struct
from collections import deque
layouts = {item["id"]: item for item in json.loads(read("data/layouts/layouts.json"))["layouts"]}
assembly = read("data/event_scripts.s")
groups = json.loads(read("data/maps/map_groups.json"))
assert any(w["dest_map"] == annex["id"] for w in hall["warp_events"])
assert any(w["dest_map"] == hall["id"] for w in annex["warp_events"])
assert any(o["script"] == "GraniteCave_AnnexResident" for o in annex["object_events"])
assert any(o["script"] == "GraniteCave_AnnexRoster" for o in annex["bg_events"])
for room in (hall, station, annex):
    name = room["name"]
    assert f'.include "data/maps/{name}/scripts.inc"' in assembly, name
    assert any(isinstance(group, list) and name in group for group in groups.values()), name
    layout = layouts[room["layout"]]
    width, height = layout["width"], layout["height"]
    raw = (R / layout["blockdata_filepath"]).read_bytes()
    assert len(raw) == width * height * 2, (name, "blockdata bytes", len(raw), width * height * 2)
    blocks = struct.unpack(f"<{width * height}H", raw)
    def in_bounds(x, y):
        return 0 <= x < width and 0 <= y < height
    def neighbors(x, y):
        return [(nx, ny) for nx, ny in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)) if in_bounds(nx, ny)]
    def walkable(x, y):
        if not in_bounds(x, y):
            return False
        block = blocks[y * width + x]
        return ((block >> 10) & 3) == 0 and (block >> 12) in (0, 3)
    events = room["warp_events"] + room["object_events"] + room["bg_events"]
    for event in events:
        pos = (event["x"], event["y"])
        assert in_bounds(*pos), (name, "event outside layout", event)
    for event in room["warp_events"] + room["object_events"]:
        pos = (event["x"], event["y"])
        assert walkable(*pos), (name, "blocked or wrong-elevation event", event)
        assert event["elevation"] in (0, 3), (name, "unexpected event elevation", event)
    occupied = {(o["x"], o["y"]) for o in room["object_events"]}
    warps = [(w["x"], w["y"]) for w in room["warp_events"]]
    assert len(occupied) == len(room["object_events"]), (name, "overlapping NPCs")
    assert len(set(warps)) == len(warps) and not occupied.intersection(warps), (name, "overlapping warp")
    # Collision-only reachability; actual warp behavior, facing, and sprite
    # display still require the emulator.
    for start in warps:
        visited = {start}
        queue = deque([start])
        while queue:
            x, y = queue.popleft()
            for pos in neighbors(x, y):
                if pos not in visited and pos not in occupied and walkable(*pos):
                    visited.add(pos)
                    queue.append(pos)
        assert set(warps) <= visited, (name, "disconnected warp approaches", start)
        for event in room["object_events"] + room["bg_events"]:
            pos = (event["x"], event["y"])
            assert any(adj in visited for adj in neighbors(*pos)), (name, "unreachable contact", event)
print("Cave settlement blockdata, event positions and collision-only routes passed (emulator still required)")
