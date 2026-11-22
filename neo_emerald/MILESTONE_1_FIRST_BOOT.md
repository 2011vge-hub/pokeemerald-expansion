# Milestone 1 — First bootable Neo Emerald prototype

> **Current status (2026-11-22):** Initial Grimyena source code and Docker-based devcontainer are committed, but no successful compile or emulator boot has yet been verified. Do not claim this milestone is complete until all checks pass.

## Goal

Compile the **first playable test ROM** from the Neo Emerald branch. It currently contains the original Emerald world/story plus a **prototype Grimyena species**. Neo Emerald's new Hoenn maps and Megas are not yet implemented.

## Prerequisites

- GitHub repo: `2011vge-hub/pokeemerald-expansion`
- Branch: `neo-emerald/phase-1-grimyena`
- Browser-based GitHub Codespaces (may use an independent Codespaces quota; verify availability/charges) OR Windows WSL2 / Linux.
- Do **not** push the retail Emerald ROM or extracted assets to this public repository.
- No GitHub Actions runs are required; avoid spending Actions minutes while the unrelated quota/billing issue is unresolved.

## Browser / iPhone / Surface Pro setup

1. Open the repository branch on GitHub: https://github.com/2011vge-hub/pokeemerald-expansion/tree/neo-emerald/phase-1-grimyena
2. In the branch selector, ensure `neo-emerald/phase-1-grimyena` is selected; select **Code → Codespaces → Create codespace on [selected branch]**.
3. The checked-in `.devcontainer` installs `gcc-arm-none-eabi`, binutils, Newlib, Git, libpng, make and Python on Ubuntu 24.04.
4. Open the VS Code integrated terminal in Codespaces.
5. Run:

   ```bash
   git branch --show-current
   python3 neo_emerald/tools/validate_design.py
   python3 neo_emerald/tools/check_source.py
   bash neo_emerald/tools/build.sh
   ```

6. Expect a test ROM at `neo_emerald/out/NeoEmerald_Prototype.gba`. The output folder is ignored by Git.
7. Download that test ROM for **personal testing** to iOS Files and open it in Delta, or test in mGBA on your computer.
8. Record any terminal errors **verbatim**; they guide specific compiler fixes. An error log is more useful than a screenshot cut off midway.

## Acceptance checklist

- [ ] Codespace/container starts and terminal uses correct branch.
- [ ] Both Python static checks pass.
- [ ] Compiler completes and produces a nonempty .gba file.
- [ ] ROM boots past title screen into a new game in Delta/mGBA.
- [ ] Grimyena's typing and base stats show as Dark/Fire with 530 BST.
- [ ] A Mightyena evolving at provisional Lv38 becomes Grimyena.
- [ ] Evolution, battling, party UI, saving and reloading all work.
- [ ] No original commercial ROM files or copied Unbound/Imperium assets are committed.

## Known placeholder content

- Grimyena temporarily reuses Mightyena sprites, icon, overworld data, cry and level-up learnset.
- Evolution level 38 is provisional.
- New species Pokédex entry/number is not final (placeholder `NATIONAL_DEX_NONE`).
- Mega Grimyena and the other three custom Megas are still design specifications.
- Mossdeep evacuation and the rebuilt Hoenn map are not yet implemented.

## Troubleshooting

**`arm-none-eabi-gcc: command not found`** — the container build did not install the Linux ARM toolchain; verify the VS Code environment is reopened in container. For Windows local build use WSL2 and `docs/install/windows/WSL.md`.

**`make` fails with a C/assembly linker error** — capture the first actual error and the surrounding 20–30 lines. Fix on `neo-emerald/phase-1-grimyena`; do not change `master`.

**Codespaces creation is unavailable or shows billing warnings** — stop and use the Surface Pro WSL2 build route instead. Codespaces and GitHub Actions have distinct usage accounting.

**Phone browser is awkward** — Codespaces is easier to configure and debug from Surface Pro; after successful compilation the produced GBA file can be downloaded and tested on iPhone.

## Next after the first boot

1. Replace Grimyena temporary art with original front/back/shiny/icon graphics.
2. Complete unique dex entry and learnset.
3. Implement and test Mega Grimyena + Grimyenite.
4. Prepare a **small playable Mossdeep evacuation vertical slice** (one redesigned outdoor map, one interior, one quest, one meaningful battle).
5. Add expansion quests and dynamic Gym scaling incrementally.

**Story priority:** Unbound's *new adventure/story* feeling first; Imperium's battles/QoL as secondary design reference. Distinctive original content, not copied assets.
