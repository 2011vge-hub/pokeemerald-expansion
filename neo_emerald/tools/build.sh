#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO_ROOT"

if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
  echo "Missing ARM GCC toolchain. Use the repo's .devcontainer or follow docs/install/linux/UBUNTU.md." >&2
  exit 127
fi

# Restore the missing final 17 cave tile graphics before gbagfx runs.
# Preserve all 432 original indexed tiles, the existing metatile IDs,
# palette banks, and the native lava animation slots. The new overlays
# are provisional shelter art until the environment art pass replaces them.
python3 - <<'PY'
from pathlib import Path
from PIL import Image, ImageDraw
import struct

path = Path("data/tilesets/secondary/cave/tiles.png")
with Image.open(path) as src:
    src.load()
    if src.mode != "P" or src.width != 128 or src.height not in (216, 232):
        raise SystemExit(f"Unexpected cave atlas format: {src.mode} {src.size}")
    if src.height == 216:
        atlas = Image.new("P", (128, 232), 0)
        atlas.putpalette(src.getpalette())
        atlas.paste(src, (0, 0))
        # Tile IDs 944–960 correspond to secondary slots 432–448.
        def put(slot, tile):
            atlas.paste(tile, ((slot % 16) * 8, (slot // 16) * 8))
        # Retain the other three quadrants of the existing first overlay.
        # Mirror the existing bottom-left quadrant to restore its right edge.
        left = atlas.crop((120, 208, 128, 216))  # slot 431
        put(432, left.transpose(Image.Transpose.FLIP_LEFT_RIGHT))

        def prop(start, kind):
            img = Image.new("P", (16, 16), 0)
            d = ImageDraw.Draw(img)
            if kind in ("bunk", "cot"):
                d.rectangle((2, 2, 13, 14), fill=6, outline=7)
                d.rectangle((3, 3, 12, 13), fill=4)
                d.rectangle((4, 3, 11, 6), fill=1)
                d.rectangle((4, 7, 11, 12), fill=10 if kind == "bunk" else 3)
                d.line((4, 11, 11, 11), fill=5)
                d.point((3, 15), fill=7)
                d.point((12, 15), fill=7)
            elif kind == "crate":
                d.rectangle((2, 4, 13, 13), fill=5, outline=7)
                d.rectangle((3, 3, 12, 5), fill=3, outline=6)
                d.line((4, 6, 4, 12), fill=2)
                d.line((11, 6, 11, 12), fill=6)
                d.line((5, 7, 10, 11), fill=4)
            elif kind == "support":
                d.rectangle((2, 2, 13, 4), fill=5, outline=7)
                d.rectangle((3, 4, 5, 14), fill=4, outline=6)
                d.rectangle((10, 4, 12, 14), fill=4, outline=6)
                d.line((5, 5, 9, 2), fill=3)
                d.line((10, 5, 6, 2), fill=3)
            for k in range(4):
                x, y = (k % 2) * 8, (k // 2) * 8
                put(start + k, img.crop((x, y, x+8, y+8)))

        prop(433, "bunk")
        prop(437, "cot")
        prop(441, "crate")
        prop(445, "support")
        atlas.save(path, bits=4)
        print("Restored cave atlas slots 432–448; original slots preserved.")
with Image.open(path) as atlas:
    assert atlas.mode == "P" and atlas.width * atlas.height // 64 >= 449
    assert max(atlas.getdata()) < 16
raw = path.with_name("metatiles.bin").read_bytes()
assert len(raw) % 16 == 0
ids = [word & 0x3ff for (word,) in struct.iter_unpack("<H", raw)]
assert max(ids) < 512 + 449, "Cave metatile references an unloaded secondary tile"
print("Cave atlas capacity and metatile tile references verified.")
PY

python3 neo_emerald/tools/validate_design.py
python3 neo_emerald/tools/check_source.py
python3 neo_emerald/tools/check_rescue_once.py
python3 neo_emerald/tools/check_chapter2_mainland.py
python3 neo_emerald/tools/check_build23_story_entry.py
python3 neo_emerald/tools/check_chapter3_continuity.py
python3 neo_emerald/tools/check_ecology_expansion.py
python3 neo_emerald/tools/check_battle_difficulty.py
python3 neo_emerald/tools/check_ferry_visuals.py
python3 neo_emerald/tools/check_ranger_opening.py
python3 neo_emerald/tools/check_starters_and_gym.py
python3 neo_emerald/tools/check_mission_training.py
python3 neo_emerald/tools/check_rustboro_university.py
python3 neo_emerald/tools/check_chapter1_hale_bridge.py
python3 neo_emerald/tools/check_delta_playtest_fixes.py
python3 neo_emerald/tools/check_native_ranger_sprites.py
python3 neo_emerald/tools/check_university_four_floors.py
JOBS="${JOBS:-2}"
if [[ ! "$JOBS" =~ ^[1-9][0-9]*$ ]]; then
  echo "JOBS must be a positive integer." >&2
  exit 2
fi
echo "Building Neo Emerald prototype with $JOBS make jobs..."
make -j"$JOBS" TITLE="NEO EMERALD"

if [[ ! -s pokeemerald.gba ]]; then
  echo "Build did not produce pokeemerald.gba." >&2
  exit 1
fi
mkdir -p neo_emerald/out
cp pokeemerald.gba neo_emerald/out/NeoEmerald_Prototype.gba
echo "Created neo_emerald/out/NeoEmerald_Prototype.gba"
echo "Note: Grimyena has temporary Mightyena graphics. This is not the finished Neo Emerald story."
