#!/usr/bin/env python3
"""Guard Ranger starter signature moves, and Mossdeep-only Gym restriction."""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
read=lambda x:(ROOT/x).read_text()
battle=read("src/battle_setup.c")
for token in ("SPECIES_POOCHYENA:", "signature = MOVE_FIRE_FANG",
              "SPECIES_SHROOMISH:", "signature = MOVE_GIGA_DRAIN",
              "SPECIES_SPHEAL:", "signature = MOVE_ICE_BEAM"):
    assert token in battle, token
assert "ScriptGiveMon(starterMon, (!IS_FRLG && VarGet(VAR_NEO_FERRY_DISPATCH) == 2) ? 10 : 5, ITEM_NONE);" in battle, "Neo Ranger starter must start at level 10; vanilla remains level 5"
assert "GiveMoveToMon(partner, signature)" in battle
gym=json.loads(read("data/maps/MossdeepCity/map.json"))
assert not any(w["dest_map"] == "MAP_MOSSDEEP_CITY_GYM" for w in gym["warp_events"])
hq=json.loads(read("data/maps/MossdeepCity_RangerBase_1F/map.json"))
for w in hq["warp_events"]:
    if w["dest_map"]=="MAP_MOSSDEEP_CITY":
        assert gym["warp_events"][int(w["dest_warp_id"])]["dest_map"]==hq["id"]
rust=json.loads(read("data/maps/RustboroCity/map.json"))
assert any(o["dest_map"]=="MAP_RUSTBORO_CITY_GYM" for o in rust["warp_events"])
print("Starter moves and Mossdeep-only gym lock source checks OK")
