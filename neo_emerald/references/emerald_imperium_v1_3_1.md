# Reference study: Pokémon Emerald Imperium v1.3.1

**Role:** complementary combat, boss-design, and quality-of-life reference for Pokémon: Neo Emerald. The user reported greatly enjoying this hack, but did not specify their favorite individual features. Do not infer that maximum difficulty is automatically desirable.

## Verified uploaded archive (2026-11-22)

- Archive: `Imperium (World) (v1.3.1).zip`
- Contains one 33,554,432-byte GBA ROM: `Imperium (World) (v1.3.1).gba`.
- GBA title: `POKEMON EMER`, game code `BPEE`, revision `0` (Emerald lineage).
- ROM SHA-1: `1d20091c4d936f5eb122db8780554dd0829ffb63`.
- ZIP integrity verified; ROM header examined. No gameplay emulation or functionality test performed.
- Neither the ROM nor extracted assets are committed to the Neo Emerald repository.

## Verified publicly available source/reference

- Developer's public source fork: https://github.com/iriv24/pokeemerald-expansion
- Source branch inspected: https://github.com/iriv24/pokeemerald-expansion/tree/release
- Creator's feature overview: https://emeraldimperium.info/game-info.html
- Public changelog: https://pokemonemeraldimperium.com/changelog/
- Public source README documents features such as Nature/EV/IV editing, DexNav, Minimal Grinding Mode, portable PC, PokeVial, flexible evolutions, custom Megas, following Pokémon, differentiated trainer teams and difficulty options.
- The *release* branch contains readable species and trainer source files. This is extremely relevant because our own engine also derives from `pokeemerald-expansion`, although versions differ.

**Provenance:** A public repository does not automatically grant permission to copy its unique artwork, dialogue, maps, code, or mechanics implementation wholesale. Check notices and author permissions before reusing any code. Study functionality and implement original, compatible solutions in our fork.

## Lessons for Neo Emerald

| Imperium feature | Neo Emerald design response |
|---|---|
| Strategic trainer design | Build bosses with actual synergies, counterplay, visible environmental themes and Mega aces |
| Difficulty range | Support an approachable story-first mode plus challenging optional modes; do not punish exploratory players |
| Large Pokémon roster and flexible evolutions | Curate encounter diversity by geography, not a giant random pile of species |
| New Mega forms | Prioritize Grimyena, Breloom, Walrein and Milotic with original sprites, coherent abilities and battle tests |
| Portable QoL utilities | Reduce menu friction, HM roadblocks and unnecessary grinding without erasing exploration |
| Ability and move transparency | Let players understand surprising custom effects in UI/Pokédex rather than requiring a wiki |
| Scaling and rebalanced battles | **Distinct Neo Emerald requirement:** all eight Gyms can be challenged in *any* order, using badge-based team variants |
| Modern AI | Avoid invisible cheating; adjust per difficulty, with stable predictable rule behavior and clear testing |

## Priority after user preference clarification

**Unbound: story/new-game feeling first. Imperium: battle depth, choice and convenience second.** Our target is NOT merely "Emerald but harder". Technical compatibility of the source is valuable, but artistic and narrative originality is non-negotiable.

## Source investigation shortlist

1. Compare Imperium's trainer data structures to our current master branch, *without changing anything yet*.
2. Examine difficulty and Minimal Grinding Mode configuration; choose functionality to implement with our current expansion engine.
3. Survey DexNav/menu systems against upstream expansion: avoid duplicating features already built in.
4. Design badge-scaled Gym team data in our own structure.
5. After we get a clean baseline build, prototype one original boss battle and test it on the chosen difficulty presets.

Do not cherry-pick entire code directories or merge Imperium's release branch into Neo Emerald.
