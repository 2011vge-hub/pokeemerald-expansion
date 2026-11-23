# Building Neo Emerald on a Windows Surface (free, local)

Build the current flooded Mossdeep test branch without consuming GitHub Actions or Codespaces.

## 1. Install WSL + Ubuntu (once)
Open PowerShell **as Administrator** and run:

```powershell
wsl --install -d Ubuntu
```

Restart Windows if prompted, open **Ubuntu**, and create a Linux username/password.

## 2. Install the build tools
In Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev pkg-config python3
arm-none-eabi-gcc --version
```


If your Ubuntu architecture doesn't offer those packages, follow the repository's current `docs/install/windows/WSL.md` guidance rather than downloading random third-party compilers.

## 3. Clone and select the flood branch
Keep files in the Linux home directory, not `/mnt/c/`.

```bash
git clone https://github.com/2011vge-hub/pokeemerald-expansion.git ~/pokeemerald-expansion
cd ~/pokeemerald-expansion
git switch neo-emerald/mossdeep-flood-m1
```


**Do not apply `mossdeep-flood-m1.patch`:** its storm terrain and NPCs are already committed to this branch, with the correct binary SHA.

## 4. Build and check
```bash
cd ~/pokeemerald-expansion
git pull --ff-only
bash neo_emerald/tools/build.sh
```


If successful, the output is `neo_emerald/out/NeoEmerald_Prototype.gba`.

## 5. Import to Delta
Use Windows File Explorer to open:

```text
\\wsl.localhost\Ubuntu\home\<linux-username>\pokeemerald-expansion\neo_emerald\out\
```


Copy the new .gba into iCloud Drive, OneDrive or another file-transfer location accessible on iPhone, then use Delta's import button. Start a **new save** to exercise Ranger initialization.

## 6. Playtest checklist
- Birch's briefing, Mossdeep spawn, animated rain/thunderstorm and starter choice (Poochyena / Spheal / Shroomish)
- Sailor check-in and all three NPC clue dialogue branches
- Reach the child/Poochyena below the south stairs; no completed rescue cutscene yet
- West stairs do not permit walking into the sea
- Save/reload and blackout return to Mossdeep's safe heal location
- Lower shelf is walkable but upper exits remain open

Run the map collision smoke check before changing geometry:

```bash
python3 neo_emerald/tools/map/mossdeep_paths.py data/layouts/MossdeepCity_Storm/map.bin
```

To regenerate terrain screenshots, optionally install Pillow via `sudo apt install python3-pil`, then run:

```bash
python3 neo_emerald/tools/map/render_layout.py data/layouts/MossdeepCity_Storm/map.bin mossdeep_storm.png
```

Record the **first build error** (not merely the last line) if compilation fails.

## Porymap
Open the WSL repo through the `\\wsl.localhost\Ubuntu\home\...` path. Edit `LAYOUT_MOSSDEEP_CITY_STORM` only; the original `LAYOUT_MOSSDEEP_CITY` is the preserved baseline. Modernize the upper city according to `neo_emerald/design/mossdeep_city_v2.md`.
