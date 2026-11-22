#!/usr/bin/env python3
"""Checks the source integration contract without running the GBA compiler."""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
data = json.loads((ROOT / "neo_emerald/data/species.json").read_text(encoding="utf-8"))
grimyena = next(item for item in data if item["id"] == "GRIMYENA")

constants = (ROOT / "include/constants/species.h").read_text(encoding="utf-8")
species = (ROOT / "src/data/pokemon/species_info.h").read_text(encoding="utf-8")
families = (ROOT / "src/data/pokemon/species_info/gen_3_families.h").read_text(encoding="utf-8")

assert constants.count("    SPECIES_GRIMYENA,") == 1, "Grimyena species ID missing or duplicated"
assert species.count("[SPECIES_GRIMYENA]") == 1, "Grimyena species info missing or duplicated"
assert ".evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_GRIMYENA})" in families
body = species.split("[SPECIES_GRIMYENA]", 1)[1].split("[SPECIES_EGG]", 1)[0]
assert ".types = MON_TYPES(TYPE_DARK, TYPE_FIRE)," in body
for name, field in {
    "hp": "baseHP", "attack": "baseAttack", "defense": "baseDefense",
    "speed": "baseSpeed", "sp_attack": "baseSpAttack", "sp_defense": "baseSpDefense"
}.items():
    pattern = r"\." + field + r"\s*=\s*" + str(grimyena["stats"][name]) + r"\b"
    assert re.search(pattern, body), f"Grimyena {name} does not match canonical stats"
assert ".natDexNum = NATIONAL_DEX_NONE," in body, "Prototype Pokédex placeholder changed unexpectedly"
print("Neo Emerald source contract OK: Grimyena (Dark/Fire), 530 BST, Lv38 evolution")
