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
actors={o.get("local_id"):o for o in woods["object_events"]}
for key,hook in [("GRUNT","NeoMagmaContact"),("DEVON_EMPLOYEE","NeoResearcherContact")]:
    actor=actors["LOCALID_PETALBURG_WOODS_"+key]
    assert actor["script"]=="PetalburgWoods_EventScript_"+hook
    assert actor["flag"]=="FLAG_NEO_C2_MAGMA_DONE"
assert not woods["coord_events"]
assert not mapdata("RustboroCity")["coord_events"]
# Only the approved pre-Woods partner spar uses Route 104 triggers.
route_triggers=mapdata("Route104")["coord_events"]
assert len(route_triggers)==2
assert {(e["x"],e["y"]) for e in route_triggers}=={(10,28),(11,28)}
assert all(e["script"]=="Route104_NeoPartnerSpar" and e["var"]=="VAR_TEMP_3" and str(e["var_value"])=="1" for e in route_triggers)
assert any(o["script"]=="RustboroCity_PokemonSchool_EventScript_UniversityAttendant" for o in mapdata("RustboroCity_PokemonSchool")["object_events"])
assert any(o.get("local_id")=="LOCALID_NEO_RUSTBORO_RIVAL" for o in mapdata("RustboroCity")["object_events"])
assert "applymovement LOCALID_NEO_RUSTBORO_RIVAL, RustboroCity_Movement_NeoRivalApproach" in scripts("RustboroCity")
print("Build 23 active-entry source checks pass; runtime tests still required")
