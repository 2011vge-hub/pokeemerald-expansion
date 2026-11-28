#!/usr/bin/env python3
"""Validate committed landmark changes and safely finish the waterfront door on a real checkout.
Run with --apply-waterfront to patch only that door. No sprite or other asset edits.
"""
import argparse
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
def load_json(path):
    return json.loads((ROOT / path).read_text())
def read_words(path, size=None):
    data = path.read_bytes()
    if len(data) % 2 or (size is not None and len(data) != size * 2):
        raise ValueError(f"Unexpected binary size: {path}: {len(data)} bytes")
    return list(struct.unpack("<" + "H" * (len(data)//2), data))
def require(condition, message):
    if not condition:
        raise ValueError(message)
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply-waterfront", action="store_true")
    args = parser.parse_args()
    moss = load_json("data/maps/MossdeepCity/map.json")
    water = load_json("data/maps/MossdeepCity_Waterfront/map.json")
    base = load_json("data/maps/MossdeepCity_RangerBase_1F/map.json")
    station = load_json("data/maps/MossdeepCity_WeatherStation/map.json")
    require(not any(w["dest_map"] == "MAP_MOSSDEEP_CITY_GYM" for w in moss["warp_events"]), "Old gym still reachable")
    require(moss["warp_events"][1]["dest_map"] == "MAP_MOSSDEEP_CITY_WEATHER_STATION" and (moss["warp_events"][1]["x"], moss["warp_events"][1]["y"]) == (33, 19), "Weather station entry changed")
    require(all(w["dest_map"] == "MAP_MOSSDEEP_CITY" and str(w["dest_warp_id"]) == "1" for w in station["warp_events"]), "Weather station exit not reciprocal")
    require(water["warp_events"][0]["dest_map"] == "MAP_MOSSDEEP_CITY_RANGER_BASE_1F" and (water["warp_events"][0]["x"], water["warp_events"][0]["y"]) == (17,32), "Waterfront HQ entry changed")
    require(all(w["dest_map"] == "MAP_MOSSDEEP_CITY_WATERFRONT" and str(w["dest_warp_id"]) == "0" for w in base["warp_events"][:2]), "HQ exit not reciprocal")
    require(not any((o["x"],o["y"]) == (17,32) for o in water["object_events"]), "HQ door blocked by NPC")
    storm = read_words(ROOT/"data/layouts/MossdeepCity_Storm/map.bin", 80*40)
    require(all(storm[(5+y)*80+35+x] == (0x4001 if y==0 else 0x5001) for y in range(5) for x in range(6)), "Old gym footprint not cleared (or replaced by newer art; review)")
    require(storm[9*80+34] == 0x5001, "Old gym sign remains")
    require(storm[19*80+33] == 0x06ed, "Weather station door mismatch")
    attrs = read_words(ROOT/"data/tilesets/secondary/rustboro/metatile_attributes.bin")
    require(all(attrs[mid-512] == (0x1069 if mid==0x37d else 0x1000) for mid in range(0x37a,0x381)), "University facade attributes changed; inspect newer art before overriding")
    rust = load_json("data/maps/RustboroCity/map.json")
    require(any((w["x"],w["y"]) == (27,34) and w["dest_map"] == "MAP_RUSTBORO_CITY_POKEMON_SCHOOL" for w in rust["warp_events"]), "University entry moved")
    ma = read_words(ROOT/"data/tilesets/secondary/mossdeep/metatile_attributes.bin")
    require(ma[749-512] & 0xff == 0x69, "HQ tile is not a door behavior")
    print("PASS: committed storm map, station/HQ warp pairs and university facade attributes")
    path = ROOT/"data/layouts/MossdeepCity_Waterfront/map.bin"
    words = read_words(path, 32*40)
    door = 32*32+17
    require(words[door] & 1023 == 749, "Unexpected HQ door graphic; inspect map before patching")
    require(words[door+32] >> 12 == 5 and (words[door+32] >> 10) & 3 == 0, "HQ approach is not a walkable elevation-5 dock")
    desired = words[door] & 0x0fff
    if words[door] != desired:
        if not args.apply_waterfront:
            raise ValueError("HQ door needs its elevation cleared; rerun with --apply-waterfront after reviewing")
        words[door] = desired
        path.write_bytes(struct.pack("<" + "H"*len(words), *words))
        require(read_words(path, 32*40)[door] == desired, "Waterfront write verification failed")
        print("Applied only HQ door elevation repair")
    print("PASS: waterfront door and approach source checks; compile/emulator render and traversal still required")

if __name__ == "__main__":
    main()
