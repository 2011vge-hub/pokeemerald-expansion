#!/usr/bin/env python3
"""Regression checks for first human Delta playtest; source-only verification."""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parents[2]
def load(path):
    return (ROOT/path).read_text(encoding="utf-8")

hq = load("data/maps/MossdeepCity_RangerBase_2F/scripts.inc")
ferry = load("data/maps/MossdeepCity_Waterfront/scripts.inc")
school = load("data/maps/RustboroCity_PokemonSchool/scripts.inc")
moss = json.loads(load("data/maps/MossdeepCity/map.json"))
gym = next(o for o in moss["object_events"] if o.get("local_id") == "LOCALID_NEO_MOSSDEEP_GYM_GUARD")
warp = next(w for w in moss["warp_events"] if w["dest_map"] == "MAP_MOSSDEEP_CITY_GYM")
assert (gym["x"],gym["y"]) == (warp["x"],warp["y"]) == (38,9), "Gym guard must block actual door"
assert gym["flag"] == "FLAG_NEO_MOSSDEEP_GYM_ACCESS_GRANTED"

bridge = hq.split("MossdeepCity_RangerBase_2F_EventScript_Chapter1Debrief:",1)[1].split("MossdeepCity_RangerBase_2F_Text_Chapter1RescueDebrief:",1)[0]
assert bridge.index("setrespawn HEAL_LOCATION_RUSTBORO_CITY") < bridge.index("warp MAP_RUSTBORO_CITY"), "Last heal location must move to Rustboro before travel"
assert "fadescreen FADE_TO_BLACK" in bridge, "The transition must be visually masked"

boarding = ferry.split("MossdeepCity_Waterfront_EventScript_Boarding:",1)[1].split("MossdeepCity_Waterfront_Movement_Board:",1)[0]
assert boarding.index("applymovement LOCALID_WATERFRONT_RESCUE_CHILD, Common_Movement_FacePlayer") < boarding.index("MossdeepCity_Waterfront_Text_CrewSpotsThem")
assert boarding.index("applymovement LOCALID_WATERFRONT_RESCUE_POOCHYENA, Common_Movement_FacePlayer") < boarding.index("MossdeepCity_Waterfront_Text_CrewSpotsThem")
assert boarding.count("setvar VAR_NEO_FERRY_DISPATCH, 5")==1, "Do not duplicate rescue credit"

start = school.index("RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:")
end = school.index("RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:",start)
new_lines = school[start:end].splitlines()
for index, line in enumerate(new_lines):
    if not line.strip().startswith('.string'):
        continue
    # Each separate .string literal is a packed continuation in GBA scripts.
    # Do not concatenate unrelated words without a line/page/end command.
    if line.rstrip().endswith('"') and not any(code in line for code in (r'\n', r'\p', '$')):
        raise AssertionError(f"Unterminated line at {index}: {line}")
assert "giveitem ITEM_QUICK_CLAW" in school and "FLAG_RECEIVED_QUICK_CLAW" in school
print("Delta playtest source checks pass: Rustboro respawn, door-bound gym gate, ferry facing and dialogue")
