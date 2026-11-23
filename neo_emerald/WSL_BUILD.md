# Building Neo Emerald on a Windows Surface (free, local)

Build the current Mossdeep City v3 streets test branch without consuming GitHub Actions or Codespaces.

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


Snapdragon (ARM) Surface models run ARM64 Ubuntu; the same packages are in Ubuntu's archive for ARM64.
If your Ubuntu architecture doesn't offer those packages, follow the repository's current `docs/install/windows/WSL.md` guidance rather than downloading random third-party compilers.

## 3. Clone and select the City v3 branch
Keep files in the Linux home directory, not `/mnt/c/`.

```bash
git clone https://github.com/2011vge-hub/pokeemerald-expansion.git ~/pokeemerald-expansion
cd ~/pokeemerald-expansion
git switch neo-emerald/mossdeep-city-v3-streets
```


**Do not apply any previous Claude Mossdeep patch:** the flood, city upgrades, third bridge access, annex removal, paving, lamps and waterfront source changes have been committed to this branch.

## 4. Check, then build
```bash
cd ~/pokeemerald-expansion
git pull --ff-only
bash neo_emerald/tools/wsl_doctor.sh           # environment check only; fix anything marked [FIX]
bash neo_emerald/tools/wsl_doctor.sh --build   # build with a saved log
```

The doctor never installs anything; it prints the exact command for missing tools.
On success it prints the ROM size and SHA-1 and opens the output folder in Windows Explorer;
the ROM is `neo_emerald/out/NeoEmerald_Prototype.gba`.
On failure it prints the **first** errors from `neo_emerald/out/build.log`: paste those lines into chat.
If the build is killed (out of memory), rerun with `JOBS=2 bash neo_emerald/tools/wsl_doctor.sh --build`.

## 5. Import to Delta
Use Windows File Explorer to open:

```text
\\wsl.localhost\Ubuntu\home\<linux-username>\pokeemerald-expansion\neo_emerald\out\
```


Copy the new .gba into iCloud Drive, OneDrive or another file-transfer location accessible on iPhone, then use Delta's import button. Start a **new save** to exercise Ranger initialization.

## 6. Playtest checklist
Test in mGBA first (easier to save states and read errors), then Delta. Start a **new game**.

Opening
- Birch's Ranger briefing, Mossdeep spawn, animated rain + lightning + thunder
- Dispatch call, starter choice (Poochyena / Spheal / Shroomish), no Route 101 battle
- Sailor check-in; the girl's and ninja boy's clue lines change after check-in

Ranger Base (door between the Pokemon Center and the Mart)
- Door animates, 1F loads, stairs both ways, exit returns you to the door
- All six staff talk; Medic heals; Quartermaster gives 3 POTIONs once; Hale shows 1/100/1 needed and 0/0/0 record

Rescue
- Boy on the south landing only asks for help before the sailor check-in
- After check-in: calm POOCHYENA, fade to the ferry quay, boarding scene, +1 mission / +100 XP once
- Walk back: pair gone from the landing; return to the quay: no second scene; Hale shows 1 mission / 100 XP
- Reach the landing both by the south stairs and by the east-terrace walkway

World and safety
- West stairs don't let you walk onto the sea; the flooded shelf is walkable; waterfront connects both ways
- Save and reload in Mossdeep, in the Ranger Base and on the quay; blackout returns to Mossdeep

Report: what you did, what happened, what you expected; mGBA screenshots help.

Run the map collision smoke check before changing geometry (Mossdeep; waterfront connectivity should also be checked in-game):

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
