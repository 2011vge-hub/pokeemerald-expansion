#!/usr/bin/env python3
"""Source test for four accessible Rustboro University levels.

This checks file/warp coherency, not runtime collision or visual design.
"""
from pathlib import Path
import json

ROOT=Path(__file__).resolve().parents[2]
read=lambda p:(ROOT/p).read_text(encoding="utf-8")
groups=json.loads(read("data/maps/map_groups.json"))
group=groups["gMapGroup_IndoorRustboro"]
school=json.loads(read("data/maps/RustboroCity_PokemonSchool/map.json"))
s=read("data/maps/RustboroCity_PokemonSchool/scripts.inc")
assert len(school["warp_events"])==3
assert any(x["x"]==8 and x["y"]==2 and x["script"]=="RustboroCity_PokemonSchool_EventScript_UniversityLift" for x in school["bg_events"])
assert "warp MAP_RUSTBORO_CITY_UNIVERSITY_2F, 3, 7" in s
assert "giveitem ITEM_QUICK_CLAW" in s
assert sum(x["script"]=="RustboroCity_PokemonSchool_EventScript_Blackboard" for x in school["bg_events"])==3
expect={
"2F":("LAYOUT_NEO_RUSTBORO_UNIVERSITY_2F",["MAP_RUSTBORO_CITY_POKEMON_SCHOOL","MAP_RUSTBORO_CITY_UNIVERSITY_3F"]),
"3F":("LAYOUT_NEO_RUSTBORO_UNIVERSITY_3F",["MAP_RUSTBORO_CITY_UNIVERSITY_2F","MAP_RUSTBORO_CITY_UNIVERSITY_4F"]),
"4F":("LAYOUT_NEO_RUSTBORO_UNIVERSITY_4F",["MAP_RUSTBORO_CITY_UNIVERSITY_3F"]),
}
for floor,(layout,targets) in expect.items():
    name=f"RustboroCity_University_{floor}"
    assert name in group
    m=json.loads(read(f"data/maps/{name}/map.json"))
    src=read(f"data/maps/{name}/scripts.inc")
    assert m["layout"]==layout
    assert [w["dest_map"] for w in m["warp_events"]]==targets
    assert len(m["object_events"])==2
    assert all(f'{e["script"]}::' in src for e in m["object_events"])
# Both map_events and maps.s refer to labels defined in data/event_scripts.s.
# Ensure that actual event assembly includes all new floor scripts, not just
# that their files exist in the source checkout.
assembly=read("data/event_scripts.s")
for floor in ("2F", "3F", "4F"):
    include=f'\t.include "data/maps/RustboroCity_University_{floor}/scripts.inc"'
    assert assembly.count(include)==1, f"University {floor} scripts not linked exactly once"
assert "OBJ_EVENT_GFX_ROXANNE" in read("data/maps/RustboroCity_University_4F/map.json")
assert "I lead this university" in read("data/maps/RustboroCity_University_4F/scripts.inc")
print("Four-floor Rustboro University source checks PASS; still needs compile/emulator walkability test")

# Flood fill the usable aisles with NPCs and furniture in place.
import struct
from collections import deque
layouts = {entry["id"]: entry for entry in json.loads(read("data/layouts/layouts.json"))["layouts"]}
floors = [school] + [json.loads(read(f"data/maps/RustboroCity_University_{n}F/map.json")) for n in (2, 3, 4)]
by_id = {floor["id"]: floor for floor in floors}
for n, floor in enumerate(floors, 1):
    layout = layouts[floor["layout"]]
    assert layout["id"] == f"LAYOUT_NEO_RUSTBORO_UNIVERSITY_{n}F"
    width, height = layout["width"], layout["height"]
    blocks = struct.unpack(f"<{width * height}H", (ROOT / layout["blockdata_filepath"]).read_bytes())
    walkable = {(i % width, i // width) for i, tile in enumerate(blocks) if not tile & 0xc00}
    npcs = {(event["x"], event["y"]) for event in floor["object_events"]}
    assert npcs <= walkable
    walkable -= npcs
    landings = {(warp["x"], warp["y"]) for warp in floor["warp_events"]}
    seed = (2, 2) if n > 1 else (5, 9)
    reached = {seed}
    queue = deque([seed])
    def neighbors(x, y):
        return {(x+1,y), (x-1,y), (x,y+1), (x,y-1)}
    while queue:
        for tile in neighbors(*queue.popleft()) & walkable - landings - reached:
            reached.add(tile)
            queue.append(tile)
    for tile in npcs | landings:
        assert neighbors(*tile) & reached, (n, tile)
    for index, warp in enumerate(floor["warp_events"]):
        target = by_id.get(warp["dest_map"])
        if target:
            back = target["warp_events"][int(warp["dest_warp_id"])]
            assert back["dest_map"] == floor["id"] and int(back["dest_warp_id"]) == index
print("University stair round trips and aisle access PASS on all four floors")
