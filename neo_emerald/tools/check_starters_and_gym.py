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
assert "ScriptGiveMon(starterMon, 5, ITEM_NONE);" in battle
assert "GiveMoveToMon(partner, signature)" in battle
gym=json.loads(read("data/maps/MossdeepCity/map.json"))
door=next(x for x in gym["warp_events"] if x["dest_map"]=="MAP_MOSSDEEP_CITY_GYM")
assert (door["x"], door["y"])==(38,9)
guards=[o for o in gym["object_events"] if o["local_id"]=="LOCALID_NEO_MOSSDEEP_GYM_GUARD"]
assert len(guards)==1
guard=guards[0]
assert (guard["x"],guard["y"],guard["elevation"])==(38,10,5)
assert guard["flag"]=="FLAG_NEO_MOSSDEEP_GYM_ACCESS_GRANTED"
assert guard["script"]=="MossdeepCity_EventScript_NeoGymClosed"
city=read("data/maps/MossdeepCity/scripts.inc")
for k in ["MossdeepCity_EventScript_NeoGymClosed::", "VAR_NEO_FERRY_DISPATCH, 3",
          "VAR_NEO_FERRY_DISPATCH, 5", "RANGER_RANK_RANGER", "Now's not the time. I should"]:
    assert k in city,k
assert "FLAG_NEO_MOSSDEEP_GYM_ACCESS_GRANTED 0x24" in read("include/constants/flags.h")
rust=json.loads(read("data/maps/RustboroCity/map.json"))
assert any(o["dest_map"]=="MAP_RUSTBORO_CITY_GYM" for o in rust["warp_events"])
print("Starter moves and Mossdeep-only gym lock source checks OK")
