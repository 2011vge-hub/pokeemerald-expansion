#!/usr/bin/env python3
"""Chapter 2 source checks. Compiler/emulator tests remain required."""
import json
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
assert "TRAINER_NEO_AQUA_ROUTE104" in opps
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
    for w in m["warp_events"]:
        assert (w["x"],w["y"]) not in coords,"NPC blocks map warp"
# Regression: vanilla's initial hide flags must not strand Neo Rangers.
assert "goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, Route104_MrBrineysHouse_NeoHomeTransition" in house
home=house.split("Route104_MrBrineysHouse_NeoHomeTransition:",1)[1].split("Route104_MrBrineysHouse_EventScript_HideRustboroRival::",1)[0]
assert "goto_if_eq VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_MrBrineysHouse_NeoHomeDone" in home
assert "goto_if_eq VAR_BOARD_BRINEY_BOAT_STATE, 2, Route104_MrBrineysHouse_NeoShowHome" in home
assert "goto_if_set FLAG_VISITED_DEWFORD_TOWN, Route104_MrBrineysHouse_NeoHomeDone" in home
assert "clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY" in home
assert "clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO" in home
raid=route.split("Route104_EventScript_NeoAquaGrunt::",1)[1].split("Route104_EventScript_C2AquaWait:",1)[0]
assert raid.index("setflag FLAG_NEO_C2_AQUA_DONE") < raid.index("pokenavcall Route104_Text_C2RivalRadio")
assert route.count("pokenavcall Route104_Text_C2RivalRadio")==1
battle_msg=read("src/battle_message.c")
assert 'sText_NeoMagmaClass[] = _("Neo Magma")' in battle_msg
assert 'sText_NeoAquaClass[] = _("Neo Aqua")' in battle_msg
# Partner phase gates: one map at a time, no repeat spar after old completed missions.
assert all(o["flag"]=="FLAG_TEMP_1" for o in wm["object_events"] if o.get("local_id")=="LOCALID_NEO_C2_WOODS_RIVAL")
cm=json.loads(read("data/maps/RustboroCity/map.json"))
assert next(o for o in cm["object_events"] if o.get("local_id")=="LOCALID_NEO_RUSTBORO_RIVAL")["flag"]=="FLAG_TEMP_1"
partner=next(o for o in rm["object_events"] if o.get("local_id")=="LOCALID_NEO_ROUTE104_PARTNER")
assert partner["flag"]=="FLAG_TEMP_1"
spar_tiles={(o["x"],o["y"]) for o in rm["coord_events"] if o["script"]=="Route104_NeoPartnerSpar"}
assert spar_tiles=={(10,28),(11,28)}
import struct
raw=(R/"data/layouts/Route104/map.bin").read_bytes()
tiles=struct.unpack("<3200H",raw)
for x,y in spar_tiles|{(partner["x"],partner["y"])}:
    assert ((tiles[y*40+x]>>10)&3)==0 and tiles[y*40+x]>>12==3
for name in ("MAY","BRENDAN"):
    for variant in ("TREECKO","MUDKIP","TORCHIC"):
        ident=f"TRAINER_{name}_RUSTBORO_{variant}"
        assert f"trainerbattle_no_intro {ident}, Route104_NeoPartnerLoseText" in route
        party=trainers.split(f"=== {ident} ===",1)[1].split("===",1)[0]
        assert ("Name: NESSA" if name=="MAY" else "Name: VERN") in party
assert "goto_if_set FLAG_NEO_C2_MAGMA_DONE, Route104_NeoPartnerVisibilityDone" in route
assert "setflag FLAG_DEFEATED_RIVAL_ROUTE_104" in route.split("Route104_NeoPartnerSparWon:",1)[1].split("Route104_NeoPartnerSparEnd:",1)[0]
assert "goto_if_set FLAG_NEO_C2_BRINEY_REPORTED, PetalburgWoods_NeoPartnerVisibilityDone" in woods
print("Chapter 2 source checks PASS; full playthrough still required")
