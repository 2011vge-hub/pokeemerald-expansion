#!/usr/bin/env python3
"""Chapter 2 source checks. Compiler/emulator tests remain required."""
import json
import re
from pathlib import Path
R=Path(__file__).resolve().parents[2]
read=lambda p:(R/p).read_text(encoding="utf-8")
flags=read("include/constants/flags.h")
woods=read("data/maps/PetalburgWoods/scripts.inc")
route=read("data/maps/Route104/scripts.inc")
house=read("data/maps/Route104_MrBrineysHouse/scripts.inc")
city=read("data/maps/RustboroCity/scripts.inc")
opps=read("include/constants/opponents.h")
trainers=read("src/data/trainers.party")
for suffix in ("MAGMA_DONE","CUTTER_DEMO","AQUA_DONE","BRINEY_REPORTED","DEBRIEF_DONE"):
    assert "FLAG_NEO_C2_"+suffix in flags
wm=json.loads(read("data/maps/PetalburgWoods/map.json"))
assert all(o["flag"]=="FLAG_NEO_C2_CUTTER_DEMO" for o in wm["object_events"][:2])
assert wm["object_events"][0]["local_id"]=="LOCALID_NEO_C2_WOODS_TREE_N"
assert wm["object_events"][1]["local_id"]=="LOCALID_NEO_C2_WOODS_TREE_S"
assert woods.count("setflag FLAG_NEO_C2_MAGMA_DONE")==1
assert woods.count("setflag FLAG_NEO_C2_CUTTER_DEMO")==1
assert "removeobject LOCALID_NEO_C2_WOODS_TREE_N" in woods
assert "removeobject LOCALID_NEO_C2_WOODS_TREE_S" in woods
assert any(o.get("local_id")=="LOCALID_NEO_C2_WOODS_RIVAL" for o in wm["object_events"])
foresttrainer=trainers.split("=== TRAINER_GRUNT_PETALBURG_WOODS ===")[1].split("===")[0]
assert "Class: Team Magma" in foresttrainer
assert "Pic: Magma Grunt M" in foresttrainer
def trainer_constant(name):
    match = re.search(r"^#define\s+" + name + r"\s+(\d+)\b", opps, re.MULTILINE)
    assert match, name
    return int(match[1])

assert trainer_constant("TRAINER_NEO_AQUA_ROUTE104") == 855
assert trainer_constant("TRAINER_NEO_TUNNEL") == 856
assert 856 < trainer_constant("TRAINERS_COUNT_EMERALD") <= trainer_constant("MAX_TRAINERS_COUNT_EMERALD")
assert "=== TRAINER_NEO_AQUA_ROUTE104 ===" in trainers
assert route.count("setflag FLAG_NEO_C2_AQUA_DONE")==1
rm=json.loads(read("data/maps/Route104/map.json"))
assert any(o.get("local_id")=="LOCALID_NEO_C2_ROUTE104_AQUA_GRUNT" for o in rm["object_events"])
assert house.count("setflag FLAG_NEO_C2_BRINEY_REPORTED")==1
assert "SPECIES_WINGULL" in house
assert city.count("setflag FLAG_NEO_C2_DEBRIEF_DONE")==1
report=city.split("RustboroCity_EventScript_C2ReportComplete:",1)[1].split("RustboroCity_EventScript_C2ReportDone:",1)[0]
assert report.index("setflag FLAG_NEO_C2_DEBRIEF_DONE") < report.index("addvar VAR_NEO_RANGER_MISSIONS, 1")
assert report.count("special NeoRangerCreditMissionTraining")==1
for m in (wm,rm):
    coords=[(o["x"],o["y"]) for o in m["object_events"]]
    assert len(coords)==len(set(coords)), "NPC overlap"
    # Native Emerald's Route104 rival stands on its south cottage warp when
    # hidden by story flag. Preserve that older vanilla design while ensuring
    # our *new* Chapter 2 actors never block a doorway.
    new_scripts={"Route104_EventScript_NeoAquaGrunt",
                 "Route104_EventScript_NeoSupplyWorker",
                 "PetalburgWoods_EventScript_NeoRivalCutter"}
    added={(o["x"],o["y"]) for o in m["object_events"] if o.get("script") in new_scripts}
    for w in m["warp_events"]:
        assert (w["x"],w["y"]) not in added, "New Chapter 2 NPC blocks map warp"
print("Chapter 2 source checks PASS; full playthrough still required")
