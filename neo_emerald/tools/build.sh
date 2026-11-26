#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO_ROOT"

if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
  echo "Missing ARM GCC toolchain. Use the repo's .devcontainer or follow docs/install/linux/UBUNTU.md." >&2
  exit 127
fi

python3 neo_emerald/tools/validate_design.py
python3 neo_emerald/tools/check_source.py
python3 neo_emerald/tools/check_rescue_once.py
python3 neo_emerald/tools/check_chapter2_mainland.py
python3 neo_emerald/tools/check_ferry_visuals.py
python3 neo_emerald/tools/check_ranger_opening.py
python3 neo_emerald/tools/check_starters_and_gym.py
python3 neo_emerald/tools/check_mission_training.py
python3 neo_emerald/tools/check_rustboro_university.py
python3 neo_emerald/tools/check_chapter1_hale_bridge.py
python3 neo_emerald/tools/check_delta_playtest_fixes.py
python3 neo_emerald/tools/check_native_ranger_sprites.py
python3 neo_emerald/tools/check_university_four_floors.py
python3 neo_emerald/tools/generate_ranger_sprites.py
# Install the approved hatless visual direction after the legacy generator.
python3 neo_emerald/tools/install_hatless_rangers.py
python3 neo_emerald/tools/install_approved_ranger_portraits.py

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
