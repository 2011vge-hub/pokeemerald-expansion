#!/usr/bin/env python3
"""Guard first-pass original Emerald Ranger overworld source artwork."""
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
assets=ROOT/"graphics/object_events/pics/people"
for gender,npc in [("brendan","camper.png"),("may","picnicker.png")]:
    with Image.open(assets/npc) as native:
        assert native.mode=="P" and native.size==(144,32), (npc,native.mode,native.size)
        assert max(native.getdata())<=15
    for action in ("walking.png","running.png"):
        with Image.open(assets/gender/action) as player:
            assert player.mode=="P" and player.size==(144,32), (gender,action)
text=(ROOT/"neo_emerald/tools/generate_ranger_sprites.py").read_text()
assert "NATIVE_RANGER_SOURCES = {'brendan':'camper.png', 'may':'picnicker.png'}" in text
assert "img=native_ranger_walking(img,isfemale)" in text
assert "img=reindex(img,isfemale,False)" in text, "Other action geometry must remain compatible"
print("Original Emerald Ranger base sprites validated; runtime art inspection still needed")
