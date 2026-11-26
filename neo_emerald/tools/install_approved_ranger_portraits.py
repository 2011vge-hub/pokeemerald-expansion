#!/usr/bin/env python3
"""Install approved hatless Ranger front portraits after overworld generation.

Front and back trainer pictures share a palette in trainers.h. Keep the
legacy four-frame battle-back geometry but map its colors to the approved
palette. Dedicated hatless back poses remain a separate art deliverable.
"""
import base64
import hashlib
import io
import json
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
TRAINERS = ROOT / "graphics/trainers"
PEOPLE = ROOT / "graphics/object_events/pics/people"
OW_PALETTES = ROOT / "graphics/object_events/palettes"
MANIFEST = ROOT / "neo_emerald/design/approved_hatless_ranger_portraits.json"
EXPECTED = {
    "male": ("brendan", "20ea263d74d429a2bf9e1a2106e3fdbafa1a351175517417918d35fc8a64fae5", "71e1bed7b972ca32d322276a6d8a6d488bada412dd3e8eb38459973165c046fc"),
    "female": ("may", "3a251c39a5688c9a132a32635fa799d505a014015f5f536032328775465b8353", "22800d7693446bca5b0b2a44bbab4cfa737de71b81e1a72cf6743ca9f1672e9b"),
}
def sha(data):
    return hashlib.sha256(data).hexdigest()

def indexed(data, size):
    with Image.open(io.BytesIO(data)) as source:
        image = source.copy()
    assert image.mode == "P" and image.size == size
    assert len(image.getpalette()) >= 48 and max(image.getdata()) <= 15
    return image

def paltext(palette):
    return "JASC-PAL\n0100\n16\n" + "".join("%d %d %d\n" % tuple(palette[i:i+3]) for i in range(0,48,3))

def apply():
    entries = json.loads(MANIFEST.read_text())["assets"]
    assert len(entries) == 2 and {x["gender"] for x in entries} == set(EXPECTED)
    prepared = []
    # Validate both genders and prepare all output before writing anything.
    for entry in entries:
        gender, front_hash, walk_hash = EXPECTED[entry["gender"]]
        data = base64.b64decode(entry["png_base64"], validate=True)
        assert sha(data) == front_hash == entry["sha256"], gender
        front = indexed(data, (64,64))
        assert front.info.get("transparency") == 0
        palette = front.getpalette()[:48]
        for action in ("walking.png", "running.png"):
            raw = (PEOPLE/gender/action).read_bytes()
            assert sha(raw) == walk_hash, (gender, action, "approved overworld sheet not installed")
            ow = indexed(raw, (144,32))
            assert ow.info.get("transparency") == 0 and ow.getpalette()[:48] == palette
        assert (OW_PALETTES/(gender+".pal")).read_text().split() == paltext(palette).split()
        front_path = TRAINERS/"front_pics"/(gender+".png")
        indexed(front_path.read_bytes(), (64,64))
        back_path = TRAINERS/"back_pics"/(gender+".png")
        back = indexed(back_path.read_bytes(), (64,256))
        old = back.getpalette()[:48]
        colors = [palette[i:i+3] for i in range(0,48,3)]
        lut = [0] + [min(range(1,16), key=lambda j: sum((old[3*i+k]-colors[j][k])**2 for k in range(3))) for i in range(1,16)]
        mapped = Image.new("P", back.size)
        mapped.putdata([lut[i] for i in back.getdata()])
        mapped.putpalette(palette)
        assert bytes(i != 0 for i in back.getdata()) == bytes(i != 0 for i in mapped.getdata())
        out = io.BytesIO()
        mapped.save(out, format="PNG", bits=4, transparency=0)
        assert indexed(out.getvalue(), (64,256)).getpalette()[:48] == palette
        prepared.append((gender,front_path,data,back_path,out.getvalue(),paltext(palette),front_hash))
    for gender,front_path,data,back_path,back_data,pal,front_hash in prepared:
        front_path.write_bytes(data)
        back_path.write_bytes(back_data)
        (TRAINERS/"palettes"/(gender+".pal")).write_text(pal)
        assert sha(front_path.read_bytes()) == front_hash
        print("Installed approved Ranger trainer portrait:", gender, front_hash)
    print("Battle-back frame geometry preserved; hatless battle-back art remains provisional.")
if __name__ == "__main__":
    apply()
