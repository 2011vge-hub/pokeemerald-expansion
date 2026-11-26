# Build 22 Delta playtest — 2026-11-26

Build 22 source: 79f5cac25a9b540a01db56f27501f21f3d68b582; GitHub Actions run 45877835126 succeeded.

Player screenshots confirm both approved trainer fronts, male overworld front/back/side poses, and Nessa intro dialogue. Preserve these approved Ranger assets. Female overworld animations, running and battle backs are not verified.

## Blockers and source audit
- Petalburg Gym still has OBJ_EVENT_GFX_NORMAN and young Wally; PetalburgCity_Gym_EventScript_Norman falls through to BeginWallyTutorial and OnFrame triggers ReturnFromWallyTutorial. PetalburgCity map still contains original Scott and gym guide coord triggers and its OnFrame contains Wally tutorial. Adult Wally must lead the gym; Norman is missing.
- PetalburgWoods/scripts.inc is the original Devon researcher / Team Aqua event on the tested branch, not the approved Chapter 2 Neo Magma mission.
- Hale's flight is a provisional fade/warp to Rustboro (27,35). The emergency landing belongs to the evacuation vessel near Mr. Briney's old cottage on Route 104, not Hale's aircraft; the player later investigates it via Rustboro.
- Rustboro campus town and university visual design/reachability remain unresolved, as do previously reported Mossdeep gym door, ferry staging, child/Poochyena facing and encounter/whiteout regressions. Do not treat static checks as playtest proof.
- Nessa dialogue is observed; rival graphics, facing and approach animation need attention.

## Root cause and integration direction
Build 22 descends from rustboro-university-four-floors, not the Chapter 2 development line. neo-emerald/ch2-woods-cutter-briney is diverged (2 commits ahead, 12 behind at audit), with changes in Woods, Route104, cottage, Rustboro, flags and trainers. neo-emerald/ranger-ch3-rusturf and neo-emerald/chapter-1-3-playtest also diverge. Reconcile against the exact tested Build 22 baseline; no blind merge or cherry-pick of conflicts in flags, vars, trainer IDs, layouts or scripts. Do not change master or overwrite the approved art.

## Build 23 release gate
- [ ] Preserve exact approved Ranger portrait and overworld hashes.
- [ ] Fresh game through Mossdeep rescue: physically blocked gym, child and Poochyena facing player, coherent ferry staging, no unexplained teleport.
- [ ] Hale call about emergency landing near Briney's old cottage; transfer to Rustboro, correct respawn.
- [ ] Proper opposite-gender rival introduction, unique hair, choreography and accessible four-floor university; inspect city metatile overlays.
- [ ] Rustboro to Route 104 north, Petalburg Woods Neo Magma investigation, rival Cutter demo, Route 104 south and Briney's cottage Neo Aqua supply recovery, report to Hale in Rustboro, one-badge promotion requirement. Preserve M-17 evidence continuity.
- [ ] Remove reachable vanilla Norman/young Wally tutorial, Scott forced event and other legacy story conflicts; adult Wally leader when gym is implemented, not a fake completion.
- [ ] Verify encounter entry, defeat/return path, no repeated events/softlocks.
- [ ] Compile GitHub Actions; run input-driven emulator tests and capture screenshots of each gate before distributing another story playtest. No Chapter 3 expansion or imported ROM graphics until stable.

This is a triage record, not a fix or claim of completion. Build 22 remains the known-good portrait/overworld visual baseline. GitHub Issues is disabled; record kept on asset registry branch to avoid triggering another compile.
