#!/usr/bin/env python3
"""Guard active story entry points, not proof of gameplay."""
import json
from pathlib import Path
R=Path(__file__).resolve().parents[2]
def read(p): return (R/p).read_text()
def mapdata(n): return json.loads(read("data/maps/"+n+"/map.json"))
def scripts(n): return read("data/maps/"+n+"/scripts.inc")
for name in ("PetalburgCity","PetalburgCity_Gym","PetalburgWoods"):
    assert not any(chr(92)*2+c in scripts(name) for c in "npl"), name
city=mapdata("PetalburgCity")
assert not any("ShowGymToPlayer" in e["script"] or "Scott" in e["script"] for e in city["coord_events"])
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_OnFrame" not in scripts("PetalburgCity")
gym=mapdata("PetalburgCity_Gym")
assert not any(e["graphics_id"]=="OBJ_EVENT_GFX_NORMAN" for e in gym["object_events"])
assert not any(e["script"]=="PetalburgCity_Gym_EventScript_Norman" for e in gym["object_events"])
assert "map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_Gym_OnFrame" not in scripts("PetalburgCity_Gym")
woods=mapdata("PetalburgWoods")
for o in woods["object_events"]:
    if o.get("local_id") in ("LOCALID_PETALBURG_WOODS_GRUNT","LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE"):
        assert o["script"]=="PetalburgWoods_EventScript_NeoMagmaContact"
        assert o["flag"]=="FLAG_NEO_C2_MAGMA_DONE"
assert all(o["script"]=="PetalburgWoods_EventScript_NeoMagmaContact" for o in woods["coord_events"])
assert not mapdata("RustboroCity")["coord_events"]
assert not mapdata("Route104")["coord_events"]
assert "&& x == 38 && y == 9 && !FlagGet(FLAG_NEO_MOSSDEEP_GYM_ACCESS_GRANTED)" in read("src/field_control_avatar.c")
assert any(o["script"]=="RustboroCity_PokemonSchool_EventScript_UniversityAttendant" for o in mapdata("RustboroCity_PokemonSchool")["object_events"])
print("Build 23 active-entry source checks pass; runtime tests still required")
