#!/usr/bin/env python3
"""Check the Chapter 1 rescue-to-Hale-to-Rustboro source bridge.

Static source/map check only; successful checks are not gameplay verification.
"""
import json
import re
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
read = lambda path: (ROOT / path).read_text(encoding="utf-8")
flags = read("include/constants/flags.h")
hq = read("data/maps/MossdeepCity_RangerBase_2F/scripts.inc")
campus = read("data/maps/RustboroCity/scripts.inc")
waterfront = read("data/maps/MossdeepCity_Waterfront/scripts.inc")
city = json.loads(read("data/maps/RustboroCity/map.json"))
layouts = json.loads(read("data/layouts/layouts.json"))["layouts"]

assert re.search(r"^#define FLAG_NEO_C1_FLIGHT_RUSTBORO\s+0x25\b", flags, re.M)
assert "FLAG_UNUSED_0x025" not in flags, "Do not alias the same persistent flag ID"
assert "goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_RangerBase_2F_EventScript_Chapter1Debrief" in hq
assert "goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, MossdeepCity_RangerBase_2F_EventScript_RankCheck" in hq
assert "goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, RustboroCity_EventScript_NeoCampusFieldStudentRanger" in campus
assert "setvar VAR_NEO_FERRY_DISPATCH, 5" in waterfront, "Rescue credit must precede Hale debrief"
assert "HALE: The evacuation vessel made" in hq
assert "Near MR. BRINEY's old cottage" in hq
assert "siren sounded far too late" in hq

body = hq.split("MossdeepCity_RangerBase_2F_EventScript_Chapter1Debrief:", 1)[1].split(
    "MossdeepCity_RangerBase_2F_Text_Chapter1RescueDebrief:", 1
)[0]
assert body.count("warp MAP_RUSTBORO_CITY, 27, 35") == 1
assert body.index("setflag FLAG_NEO_C1_FLIGHT_RUSTBORO") < body.index(
    "warp MAP_RUSTBORO_CITY, 27, 35"
), "Flight flag must be set before transfer"
assert body.index("goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO") < body.index(
    "setflag FLAG_NEO_C1_FLIGHT_RUSTBORO"
), "Completed saves must not replay the transfer"

x, y = 27, 35
layout = next(row for row in layouts if row["id"] == "LAYOUT_RUSTBORO_CITY")
assert 0 <= x < layout["width"] and 0 <= y < layout["height"]
for kind in ["object_events", "warp_events", "coord_events", "bg_events"]:
    assert all((event["x"], event["y"]) != (x, y) for event in city[kind]), (
        f"Rustboro arrival overlaps {kind}"
    )
block_data = ROOT / layout["blockdata_filepath"]
raw = block_data.read_bytes()
assert len(raw) == layout["width"] * layout["height"] * 2
metatile_entry = struct.unpack_from("<H", raw, 2 * (y * layout["width"] + x))[0]
# Entries use two collision bits (bits 10–11) on the GBA map, distinct
# from encounter behavior/impassability on individual metatiles.
assert (metatile_entry >> 10) & 0x3 == 0, (
    f"Rustboro arrival has nonzero layout collision bits: 0x{metatile_entry:04x}"
)
print("Chapter 1 Hale-to-Rustboro bridge static checks PASS; emulator playthrough still required")
