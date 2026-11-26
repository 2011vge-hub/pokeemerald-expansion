#!/usr/bin/env python3
import json
from pathlib import Path
R=Path(__file__).resolve().parents[2]
plan=json.loads((R/"neo_emerald/design/battle_difficulty_phase1.json").read_text())
party=(R/"src/data/trainers.party").read_text()
for entry in plan["trainers"]:
    block=party.split("=== "+entry["trainer"]+" ===",1)[1].split("===",1)[0]
    for mon in entry["team"]:
        species,level,moves,*item=mon.split("|")
        assert (species+(" @ "+item[0] if item else "")+"\nLevel: "+level) in block,entry["trainer"]
        assert all("- "+move in block for move in moves.split(",")),entry["trainer"]
    assert 1<=len(entry["team"])<=6
print("Curated trainer roster source checks passed; gameplay balance pending")
