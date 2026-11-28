#!/usr/bin/env python3
"""Build 24 playtest repairs. Keep original geometry and save IDs."""
import json
import struct
from pathlib import Path
from collections import deque
from PIL import Image

ROOT = Path(__file__).resolve().parents[3]

def read_words(path):
    raw = path.read_bytes()
    return list(struct.unpack("<" + "H"*(len(raw)//2), raw))

def write_words(path, words):
    path.write_bytes(struct.pack("<" + "H"*len(words), *words))

# University: original facade overlays draw on BG1 (NORMAL). Covered
# metatiles draw their upper artwork behind the player on BG2. Only change
# the ground-level facade; retain all behavior bits including the door.
rust = ROOT/"data/tilesets/secondary/rustboro/metatile_attributes.bin"
attrs = read_words(rust)
for mid in range(0x37a, 0x381):
    i = mid-512
    assert attrs[i] in (0,0x69,0x1000,0x1069), (mid,attrs[i])
    attrs[i] = (attrs[i]&0x0fff)|0x1000
assert attrs[0x37d-512]&0x0fff == 0x69
write_words(rust, attrs)

# Male battle-back: change only contiguous white/light-gray headwear
# regions in the upper part of each 64x64 frame. Dark navy/black existing
# palette entries are reused so no body or transparent colors are changed.
back = ROOT/"graphics/trainers/back_pics/brendan.png"
with Image.open(back) as img:
    img.load()
    assert img.mode == "P" and img.size == (64,256)
    palette = img.getpalette()
    assert tuple(palette[9*3:9*3+3]) == (222,230,238)
    assert tuple(palette[14*3:14*3+3]) == (255,255,255)
    assert tuple(palette[13*3:13*3+3]) == (45,58,89)
    pixels = img.load()
    changed = 0
    for frame in range(4):
        top = frame*64
        light = {(x,y) for y in range(top,top+40) for x in range(64)
                 if pixels[x,y] in (9,14)}
        while light:
            seed=light.pop()
            component={seed}
            queue=deque([seed])
            while queue:
                x,y=queue.popleft()
                for pos in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                    if pos in light:
                        light.remove(pos)
                        component.add(pos)
                        queue.append(pos)
            if len(component)<6 or min(y for x,y in component)>=top+32:
                continue
            for x,y in component:
                pixels[x,y]=13 if pixels[x,y]==14 else 8
                changed+=1
    if changed:
        kwargs={"bits":4}
        if "transparency" in img.info:
            kwargs["transparency"]=img.info["transparency"]
        img.save(back,**kwargs)
    print("Male Ranger battle-back dark hair pixels changed:",changed)

# Mossdeep: fit the existing Ranger HQ native building kit into the former
# Gym's six-by-five footprint. No old Gym metatile remains in this rectangle.
# The prior kit was a seven-row tower, so this is a compact provisional
# adaptation, not a claim of exact fidelity to the concept artwork.
mp=ROOT/"data/layouts/MossdeepCity_Storm/map.bin"
data=read_words(mp)
assert len(data)==80*40
city=json.loads((ROOT/"data/maps/MossdeepCity/map.json").read_text())
door=next(w for w in city["warp_events"] if (w["x"],w["y"])==(38,9))
assert door["dest_map"]=="MAP_MOSSDEEP_CITY_RANGER_BASE_1F"
kit=[
    [966,932,932,932,932,814],
    [944,948,948,948,948,859],
    [952,954,733,733,955,957],
    [738,740,740,741,742,719],
    [746,748,748,749,750,727],
]
old=[
    [426,427,427,427,427,428],
    [434,435,435,435,435,436],
    [440,441,442,435,443,444],
    [448,449,450,453,451,452],
    [456,457,458,461,459,460],
]
current=[[data[(5+y)*80+35+x]&1023 for x in range(6)] for y in range(5)]
assert current==old or current==kit, "Unexpected HQ footprint; protect newer art"
for y,row in enumerate(kit):
    for x,mid in enumerate(row):
        i=(5+y)*80+35+x
        data[i]=(data[i]&0xfc00)|mid
assert data[9*80+38]&1023==749
assert data[9*80+38]>>12==0
write_words(mp,data)
print("Mossdeep Ranger HQ facade replaced in former Gym footprint; entry preserved.")
print("University ground-level layering corrected; runtime inspection required.")
