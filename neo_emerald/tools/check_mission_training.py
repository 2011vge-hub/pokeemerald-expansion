#!/usr/bin/env python3
"""Static guard for rank-scaled Ranger partner training credit."""
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
r=lambda p: (ROOT/p).read_text()
vars=r("include/constants/vars.h")
for v in ["VAR_NEO_STARTER_PERSONALITY_LO","VAR_NEO_STARTER_PERSONALITY_HI","VAR_NEO_PARTNER_EXP_PENDING"]:
    assert v in vars,v
b=r("src/battle_setup.c")
assert "VarSet(VAR_NEO_STARTER_PERSONALITY_LO, personality & 0xFFFF);" in b
assert "VarSet(VAR_NEO_STARTER_PERSONALITY_HI, personality >> 16);" in b
s=r("src/field_specials.c")
assert "void NeoRangerCreditMissionTraining(void)" in s
for constant in ["NEO_RANGER_TRAINING_XP_ROOKIE","NEO_RANGER_TRAINING_XP_STEP",
                 "NEO_RANGER_TRAINING_XP_MAJOR"]:
    assert constant in s,constant
assert "def_special NeoRangerCreditMissionTraining" in r("data/specials.inc")
battle=r("src/battle_script_commands.c")
assert "VarGet(VAR_NEO_PARTNER_EXP_PENDING)" in battle
assert "personality == registered" in battle and "VarSet(VAR_NEO_PARTNER_EXP_PENDING, pending - bonus)" in battle
assert battle.index("ApplyExperienceMultipliers(&gBattleStruct->battlerExpReward") < battle.index("personality == registered") < battle.index("B_EXP_CAP_TYPE == EXP_CAP_HARD && gBattleStruct->battlerExpReward != 0")
w=r("data/maps/MossdeepCity_Waterfront/scripts.inc")
script=w.split("MossdeepCity_Waterfront_EventScript_Boarding:",1)[1].split("\tend",1)[0]
assert script.index("setvar VAR_NEO_FERRY_DISPATCH, 5") < script.index("addvar VAR_NEO_RANGER_MISSIONS")
assert script.index("addvar VAR_NEO_RANGER_XP") < script.index("special NeoRangerCreditMissionTraining")
assert "MossdeepCity_Waterfront_Text_PartnerTraining" in w
print("Ranger partner EXP checks OK: saved rank credit, exact starter matching and vanilla battle level-ups")
