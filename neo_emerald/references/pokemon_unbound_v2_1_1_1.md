# Reference study: Pokémon Unbound v2.1.1.1

**Role:** design and feature reference for Pokémon: Neo Emerald. **Do not treat Unbound's compiled ROM as source code, copy its sprites/maps/story/music, or commit retail ROM bytes.**

## Directly inspected user-provided archive (2026-11-22)

- Archive: `Pokemon Unbound (v2.1.1.1).zip`
- Members: `Pokemon Unbound (v2.1.1.1).gba`, `readme.txt`
- ROM size: 33,554,432 bytes (32 MiB)
- GBA title header: `POKEMON FIRE`; game code: `BPRE` (FireRed-based).
- ROM SHA-1: `b4776b82a4c7915d0fadeaa27e013523f99dfd94`.
- ZIP readme consists only of third-party website references; it does **not** contain source code or a feature manifest.
- The ROM was inspected as a binary for structure and metadata, **not launched in an emulator**.

## Public reference context (not established from the binary alone)

Unbound is a FireRed-based hack by Skeli featuring an original Borrius region, updated mechanics, difficulty options, mission log, Mega Evolution, extensive postgame, and customized interfaces. See:

- https://www.gamebrew.org/wiki/Pokemon_Unbound_GBA
- https://romhackguides.com/hacks/unbound/
- https://github.com/Skeli789/Dynamic-Pokemon-Expansion/tree/Unbound/src (a related public engine-data source; not a full editable Unbound game project)

**Architecture caveat:** Unbound's FireRed-based systems are not directly interchangeable with our `pokeemerald-expansion` engine. Reimplement ideas using compatible Emerald source. Inspect licenses and provenance before adapting public code or assets.

## Feature reference → original Neo Emerald implementation

| Reference system | Neo Emerald approach | Priority |
|---|---|---|
| Mission/quest log | Original Ranger missions: Mossdeep evacuees, runaway desert expeditions, missing-person case of Birch and Norman; persistent progress, rewards, journal | High |
| Multiple difficulties | Accessible / Standard / Expert trainer teams and battle AI; avoid artificial stat inflation | High |
| Modern Pokémon and Megas | Use expansion battle framework; add Grimyena, Mega Grimyena, Mega Breloom, Mega Walrein, Mega Milotic with original assets | In progress |
| Diverse geography and distinct towns | New maps for sinking Mossdeep, Relicrest archaeological city, ten-level Granite Cave, overgrown Fortree | High |
| Strong boss mechanics | Give every Gym a Mega ace, clear telegraphs, and distinct environmental or team-building themes | High |
| Level-scaling bosses | **Neo Emerald differs:** design genuinely order-independent eight Gyms based on badge count; separate story milestones at 0/2/4/6/8 badges | Core mechanic |
| Quality of life | Regional transit, less HM friction, searchable Pokédex, encounter information, respectful fast battle settings | Medium |
| Postgame | Champion rematches, legendary-themed investigations, environmental restoration quests | Later |

## Acceptance criteria for engineering

1. Prove **baseline ARM compilation** of our fork before applying additional engine-level changes.
2. Compile and playtest Grimyena's level-38 evolution and Dark/Fire typing; presently data committed with temporary Mightyena art, not validated by compilation.
3. Define each Mega ability with deterministic triggers and unit-level battle tests.
4. Prototype one 3-variant Gym trainer with 0, 4, 8 badge teams. Confirm badge-independent battle access.
5. Implement a minimal, **original** mission journal, before broad content production.
6. Draft each new location as maps + encounter tables + required sprite/tileset assets; integrate one location at a time.

## Open design question

Which particular Unbound elements does the player value most (mission structure, gym battles/difficulty, progression, geography, menus, Pokédex, postgame)? Prioritize those without equating every Unbound feature to an implementation request.
