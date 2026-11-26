#!/usr/bin/env python3
import json,re
from pathlib import Path
R=Path(__file__).resolve().parents[2]
def read(p):return (R/p).read_text()
manifest=json.loads(read("neo_emerald/design/ecology_expansion_phase1.json"))
wild=json.loads(read("src/data/wild_encounters.json"))["wild_encounter_groups"][0]["encounters"]
maps={e["map"]:e for e in wild if "map" in e}
dex=read("include/constants/pokedex.h").split("#define FOREACH_SPECIES_IN_HOENN_DEX_ORDER(F)",1)[1].split("// Hoenn Pokédex order",1)[0]
names=re.findall(r"\bF\((\w+)\)",dex)
assert len(names)==len(set(names))
for name in manifest["added_regional_species"]:
    assert name in names,name
for map,kind,slot,old,new,lo,hi in manifest["replacements"]:
    table=maps[map][kind]["mons"]
    assert len(table)=={"land_mons":12,"water_mons":5,"fishing_mons":10,"rock_smash_mons":5}[kind]
    assert table[slot]=={"species":new,"min_level":lo,"max_level":hi},(map,slot)
    assert new.removeprefix("SPECIES_") in names
sc=read("data/maps/RustboroCity_PokemonSchool/scripts.inc")
gift=sc.split("RustboroCity_PokemonSchool_EventScript_RioluResearcher::",1)[1]
assert gift.index("getpartysize")<gift.index("giveegg SPECIES_RIOLU")<gift.index("setflag FLAG_NEO_RECEIVED_RIOLU_EGG")
assert "goto_if_ne VAR_RESULT, MON_GIVEN_TO_PARTY" in gift
assert "goto_if_set FLAG_NEO_RECEIVED_RIOLU_EGG" in gift
assert any(o["script"]=="RustboroCity_PokemonSchool_EventScript_RioluResearcher" for o in json.loads(read("data/maps/RustboroCity_PokemonSchool/map.json"))["object_events"])
print("Ecology slots, regional dex and Riolu egg source checks passed")
