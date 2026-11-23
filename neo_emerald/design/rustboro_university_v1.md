# Rustboro University — City Retrofit (25 Years Later)
**Status:** Stage A ambient overhaul committed on neo-emerald/rustboro-university-v1; Stage B physical campus expansion is a proposal until designed, compiled and checked in emulator.

## Art direction
Rustboro has developed into Hoenn's lively university city. Keep the recognizable Devon headquarters, Rustboro Gym, Pokemon Center, main north/south road, and connecting routes, while adding evidence of a larger student population, university housing, small businesses, research facilities and hands-on disaster recovery. The tone is hopeful and bustling despite the changing weather, not a permanently evacuated ghost town.

**Palette:** warm sandstone and campus brick, aged gray limestone, deep blue university banners, green quad grass and fountain/planter accents, with teal Ranger research indicators. Tile shading and sprite proportions must remain native to GBA Emerald. Light post-storm damage can appear at construction sites, but maintain clear paths.

## Existing 40×60 map anchors (current source)
- University campus entrance is the old Pokemon School warp at (27,34). Keep this warp intact.
- Gym at (27,19), Devon HQ at (11–12,15), faculty-adjacent house at (30,28).
- Pokemon Center at (16,38), Mart at (16,45), south approach around y=51–53.
- The existing city must retain all 12 warps, vanilla event triggers, map connections, quest state variables, and reciprocal exits until scripted replacements have been compiled and tested.
- The existing map has 16 ordinary object events before this change. Stage A adds four static campus-facing NPCs, at (28,36), (32,36), (23,39), (33,37), with no trainer battles or new event flags.

## Stage A — Committed source changes
1. Rename the school sign to RUSTBORO UNIVERSITY, Trainer Sciences and Ranger Field Studies Campus.
2. Reframe the city sign as Hoenn's research/university capital and Devon HQ as DEVON ENTERPRISES, President Steven Stone.
3. Rewrite select existing Rustboro pedestrians to discuss university life, ecology, Ranger crews and Professor Roxanne's teaching.
4. Add four new local student voices: fieldwork participant, Devon intern, Galar exchange student, and an overworked student paying rent through a Poké Mart job.
5. The classroom continues to teach status conditions and give the existing Quick Claw exactly once. Its dialogue now discusses Ranger safety, field observations, university coursework and travel to other regions.
6. The nearby household identifies as a university-adjacent faculty neighborhood; Roxanne remains a teacher and Gym leader.

All Stage A edits are in RustboroCity/map.json, RustboroCity/scripts.inc, RustboroCity_PokemonSchool/scripts.inc, and RustboroCity_House2/scripts.inc. No object graphics, tile data, sprites, or physical building exterior have yet been changed.

## Stage B — Required to genuinely finish the city redesign
**Campus Quad (existing school frontage, roughly x22–35/y32–40):** repave a central walkway, add university banners/notice board, seating, bike stand, new trees, wayfinding, and one field course demonstration area. Keep (27,34) school door, sign coordinates, all old walkable roads, and the southern path open. Build from gTileset_Rustboro / GBA-compatible custom metatiles only after producing a screenshot mock and running collision tests.

**University buildings:**
- Upgrade the former Trainer School interior into **Trainer Sciences Lecture Hall** (the existing warp) with student notes, quizzes, status-effect lecture and optional tutorials.
- **University Library / Hoenn Climate Archive:** second campus interior for dated weather and seismograph records; optional tutorials/clues and later mission logs. New warp; no secret mandatory Gym prerequisite.
- **Student Commons + Café:** warm safe hub with heal/rest access, student club chatter and a rotating board of harmless campus events.
- **Dormitory / Faculty Housing:** a residential building that shows actual campus life, including students working shifts and people who moved after coastal flooding.
- **Ranger Field Office / Relief Shelter:** the player's first Rustboro destination after Hale's flight. Mission board, Ranger certification, supplies and future gear kiosk.
- **Devon Sensor and Engineering Annex:** accessible research quarters connecting Steven's company, Ranger equipment upgrades and the abnormal-weather mystery.

**Street logic:** students need visible walking paths between housing, lecture hall, commons, Devon internships, Center/Mart and the Ranger outpost. NPC schedules can vary by story chapter; do not rely on RTC for story-critical access.

## Chapter 2–3 event staging
1. Arrive by Hale's personal air transport at a safe Rustboro clearing. Greet the opposite-gender rival outside the Ranger Field Office / campus. The rival speaks the same dialogue, using Nessa or Vern name and correct sprite.
2. First campus NPC explains university faculty support the displaced Mossdeep residents. A Ranger coordinator guides the player to a field assignment in Petalburg Woods.
3. Neo Magma grunts are investigating pressure/heat anomalies there; no named ordinary grunts.
4. Fallen tree exit: rival demonstrates Ranger Cutter; obstacle stays permanently cleared.
5. Route 104 / Briney rescue cargo problem features Neo Aqua; Briney is ~104, Peeko remains a Wingull.
6. Report back at the outpost; Hale requires one badge, not Roxanne specifically. University faculty teach optional type-matchup lessons and do NOT gate Roxanne or the mission.
7. Chapter 3: badge recognized, Rank 2 Cutter issued; Route 116/Rusturf Tunnel rescue, hidden third-signal clue, final report and board unlock.
8. These are planned scripts and map layout dependencies, not Stage A implemented gameplay.

## Updated Roxanne and Steven
- Roxanne is 25 years older, a practiced professor. Her final NPC/gym visuals will use original Emerald/appropriate teacher base palette and Roxanne hair, not a hand-drawn out-of-style portrait. Steel-specialist teams scale with player progression; first badge is optional.
- Steven now runs Devon Enterprises and has executive presence, while still connected to rocks/rare minerals. Technology is practical: flood sensors, field radios, climbing and Cutter modules. Steven's designated later Mossdeep encounter unlocks the Space Center.

## Environmental ecology hints
- Early campus posters can refer to university studies of migrating Yamper near Route 116, Riolu in rocky areas and Wimpod near flooded coasts. **Do not place species in wild encounters until the species' art, abilities and forms actually compile.**
- Researcher dialogue gently hints that multiple human factions are exploiting already unstable pressure systems; do not expose Volcanion or Team Null's Arceus plot during Chapter 2.

## QA acceptance checklist
- 20 object events on RustboroCity total; no coordinate overlaps between the four added NPCs and existing NPCs, trigger tiles or door warps.
- Every added object event references an existing event script and uses an existing object graphic ID.
- Rustboro, university classroom and faculty house scripts parse with no undefined labels.
- No Story/Ranger/vanilla event flags are newly set by ambiance NPCs.
- All 12 original warps still have correct destinations; Devon, Gym, Mart, Center and south route are accessible.
- Campus NPCs appear at boot in both player genders and cannot lock movement; they should remain after save/load.
- Existing university teacher gives Quick Claw once, including full-bag behavior.
- Repeat visits after badges and major story changes do not duplicate items or trap players.
- After later tile changes, run map-layout walkability checks in the university quad before compiling.
- ARM compile, mGBA test, then Delta import; do not call a source-only check a playable ROM.

## Implementation order
A. Source-only atmosphere, signage, dialogues, four NPCs (done; pending compile).
B. GBA-correct overworld visual facelift/quad and exterior building signs (not done).
C. New interiors and conditional NPC schedules (not done).
D. Hale flight, rival introduction, Ranger office and Woods/Briney event chain (not done).
E. Chapter 3 progression, Steel Roxanne scaling, Mega roster and expanded Pokédex (not done).
