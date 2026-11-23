#!/usr/bin/env python3
"""Check real Ranger player pixel-art sheets, not NPC recolors.

The user-selected orange Ranger design is a custom original 4bpp artwork set.
These static checks cannot replace a gameplay inspection of Delta animation.
"""
from pathlib import Path
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
ASSETS=ROOT/"graphics/object_events/pics/people"
PALETTE=[
 (115,197,164),(255,215,184),(234,174,143),(166,105,95),
 (25,30,45),(52,59,91),(255,184,80),(238,125,52),
 (167,64,39),(29,43,70),(67,82,111),(23,35,60),
 (186,76,45),(10,19,36),(241,242,229),(255,209,104)
]
palette=[n for rgb in PALETTE for n in rgb]
for gender,npc in (("brendan","camper.png"),("may","picnicker.png")):
    with Image.open(ASSETS/npc) as source:
        assert source.mode=="P" and source.size==(144,32)
        native=list(source.getdata())
    frames={}
    for mode in ("walking.png","running.png"):
        p=ASSETS/gender/mode
        with Image.open(p) as im:
            assert im.mode=="P" and im.size==(144,32), p
            data=list(im.getdata())
            assert max(data)<=15, p
            assert im.getpalette()[:48]==palette, p
            assert data!=native, "Ranger is still the original NPC silhouette!"
            assert sum(px in (6,7,8) for px in data) >= 40, "Orange cap and vest missing"
            assert sum(px==13 for px in data)>=9, "Field equipment/gloves missing"
            assert all(im.crop((16*k,0,16*(k+1),32)).getbbox() is not None for k in range(9))
            # Visible cap near the top; nontransparent boot pixels at the bottom.
            for k in range(9):
                cap=im.crop((16*k+4,5,16*k+12,11))
                boots=im.crop((16*k+4,27,16*k+13,31))
                assert any(c in (6,7,8) for c in cap.getdata()), (gender,mode,k,"cap")
                assert any(c in (11,12,13) for c in boots.getdata()), (gender,mode,k,"boots")
            frames[mode]=data
    assert frames["walking.png"]!=frames["running.png"], "Running frames cannot be static walking clones"
generator=(ROOT/"neo_emerald/tools/generate_ranger_sprites.py").read_text()
assert "RANGER_PIXEL_ART_V1" in generator
assert "img=validate_ranger_art(img,path,colors)" in generator, "Build must preserve original art"
assert "img=native_ranger_walking" not in generator, "NPC recolor generator still active"
assert "img=reindex(img,isfemale,False)" in generator, "Other poses retain provisional compatibility"
print("Original orange Ranger walking/running art: four 9-frame 4bpp sheets PASS. Delta testing pending.")
