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
assert len(school["warp_events"])==2
assert any(x["x"]==7 and x["y"]==2 and x["script"]=="RustboroCity_PokemonSchool_EventScript_UniversityLift" for x in school["bg_events"])
assert "warp MAP_RUSTBORO_CITY_UNIVERSITY_2F, 3, 7" in s
assert "giveitem ITEM_QUICK_CLAW" in s
assert sum(x["script"]=="RustboroCity_PokemonSchool_EventScript_Blackboard" for x in school["bg_events"])==3
expect={
"2F":("LAYOUT_RUSTBORO_CITY_FLAT2_1F",["MAP_RUSTBORO_CITY_POKEMON_SCHOOL","MAP_RUSTBORO_CITY_POKEMON_SCHOOL","MAP_RUSTBORO_CITY_UNIVERSITY_3F"]),
"3F":("LAYOUT_RUSTBORO_CITY_FLAT2_2F",["MAP_RUSTBORO_CITY_UNIVERSITY_2F","MAP_RUSTBORO_CITY_UNIVERSITY_4F"]),
"4F":("LAYOUT_RUSTBORO_CITY_FLAT2_3F",["MAP_RUSTBORO_CITY_UNIVERSITY_3F"]),
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
assert "OBJ_EVENT_GFX_ROXANNE" in read("data/maps/RustboroCity_University_4F/map.json")
assert "I lead this university" in read("data/maps/RustboroCity_University_4F/scripts.inc")
print("Four-floor Rustboro University source checks PASS; still needs compile/emulator walkability test")
