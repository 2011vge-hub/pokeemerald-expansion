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
assert "call MossdeepCity_RangerBase_2F_EventScript_CountBadges" in office
assert "goto_if_eq VAR_0x8004, 0, NeoOffice_Badge" in office
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
