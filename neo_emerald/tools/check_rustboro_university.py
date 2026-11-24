#!/usr/bin/env python3
"""Static sanity checks for Rustboro University stage A map and scripts.

This check does not substitute for an ARM compile, in-game map tests, or
collision/pathfinding validation after a metatile redesign.
"""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CITY = ROOT / "data/maps/RustboroCity"
SCHOOL = ROOT / "data/maps/RustboroCity_PokemonSchool"
HOUSE = ROOT / "data/maps/RustboroCity_House2"

data = json.loads((CITY / "map.json").read_text(encoding="utf-8"))
city = (CITY / "scripts.inc").read_text(encoding="utf-8")
school = (SCHOOL / "scripts.inc").read_text(encoding="utf-8")
house = (HOUSE / "scripts.inc").read_text(encoding="utf-8")

# The map assembler accepts string IDs that must exist in the graphics enum.
# A previously undefined female schoolkid ID caused an ARM linker failure.
gfx_source = (ROOT / "include/constants/event_objects.h").read_text(encoding="utf-8")
valid_gfx_ids = set(re.findall(r"^\s*(OBJ_EVENT_GFX_[A-Z0-9_]+)\s*,", gfx_source, re.MULTILINE))
valid_gfx_ids.update(re.findall(r"^#define\s+(OBJ_EVENT_GFX_VAR_[0-9A-F])\b", gfx_source, re.MULTILINE))

new_npcs = {
    (14, 22): "RustboroCity_CampusTutor",
    (16, 22): "RustboroCity_CampusSurvey",
    (26, 48): "RustboroCity_CampusCourier",
    (10, 52): "RustboroCity_CampusResident",
    (26, 36): "RustboroCity_EventScript_NeoCampusFieldStudent",
    (17, 33): "RustboroCity_EventScript_NeoCampusDevonIntern",
    (23, 40): "RustboroCity_EventScript_NeoCampusExchangeStudent",
    (32, 48): "RustboroCity_EventScript_NeoCampusResident",
}
objects = data["object_events"]
assert len(objects) == 25, f"Expected 25 Rustboro NPCs, got {len(objects)}"
positions = [(o["x"], o["y"]) for o in objects]
assert len(set(positions)) == len(positions), "Overlapping NPC coordinates"
warp_positions = {(w["x"], w["y"]) for w in data["warp_events"]}
assert len(data["warp_events"]) == 13 and data["warp_events"][12]["dest_map"] == "MAP_RUSTBORO_CITY_CLIMATE_ARCHIVE"
assert not warp_positions.intersection(new_npcs), "Campus NPC on a doorway"
coord_positions = {(e["x"], e["y"]) for e in data.get("coord_events", [])}
assert not coord_positions.intersection(new_npcs), "Campus NPC on story trigger"
for pos, script in new_npcs.items():
    matches = [o for o in objects if (o["x"], o["y"]) == pos]
    assert len(matches) == 1, f"Missing campus NPC: {pos}"
    assert matches[0]["script"] == script, f"Wrong script at {pos}"
    assert matches[0]["trainer_type"] == "TRAINER_TYPE_NONE"
    assert matches[0]["flag"] == "0", "Campus ambiance should have no progression flag"
    assert f"{script}::" in city, f"Missing script label {script}"
    assert matches[0]["graphics_id"] in valid_gfx_ids, (f"Unknown graphics ID for {script}: " f"{matches[0]['graphics_id']}")

contact = [o for o in objects if (o["x"], o["y"]) == (29, 37)]
assert len(contact) == 1, "Ranger contact missing or duplicated"
assert contact[0]["script"] == "RustboroCity_EventScript_NeoRivalContact"
assert contact[0]["graphics_id"] == "OBJ_EVENT_GFX_VAR_1"
assert contact[0]["graphics_id"] in valid_gfx_ids
assert (29, 37) not in warp_positions | coord_positions, "Contact blocks an event"
assert "RustboroCity_EventScript_SetupNeoRivalGfxId" in city
assert "RustboroCity_EventScript_NeoRivalContact::" in city
for required in (
    "RUSTBORO UNIVERSITY",
    "DEVON ENTERPRISES",
    "STEVEN STONE",
    "RustboroCity_Text_GymSign",
    "RustboroCity_Text_CitySign",
):
    assert required in city, f"City text missing {required}"

for required in ("Battle Studies 101", "Quick Claw", "RUSTBORO UNIVERSITY"):
    # Item constant remains uppercase; dialogue says QUICK CLAW
    if required == "Quick Claw":
        assert "ITEM_QUICK_CLAW" in school
    else:
        assert required in school, f"School dialogue missing {required}"

assert "FLAG_RECEIVED_QUICK_CLAW" in school
assert "ROXANNE teaches at the UNIVERSITY" in house
assert "RUSTBORO CITY POKéMON GYM" in city
print("Rustboro University Stage A static checks PASS (source only, not emulator).")
