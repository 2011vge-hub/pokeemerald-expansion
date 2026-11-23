# Pokémon: Neo Emerald — development workspace

**Status: first game-source change committed (Grimyena + provisional Lv38 evolution). Prototype compiled and boot-tested through Birch’s introduction in mGBA; the in-game evolution test is pending.** This subfolder keeps Neo Emerald design data separate from the upstream `pokeemerald-expansion` source.

## Design decisions

- Hoenn, 25 years later, significantly changed by climate and geological events.
- The player is a rookie Mossdeep Ranger. Their field rig breaks during the evacuation; dispatch calls and equipment upgrades replace HM traversal. May leads Team Null, a breakaway group of Rangers.
- New playable line: Poochyena → Mightyena → **Grimyena** (Dark/Fire) → **Mega Grimyena** (Dark/Fire, Cerberus-style).
- Custom Megas: Breloom (Grass/Fighting), Walrein (Water/Ice), Milotic (Water), and Grimyena.
- **Chaos Spores:** Mega Breloom's contact-hit status attempt (20%; burn/sleep/poison/paralysis).
- **Permafrost:** Mega Walrein brings hail/snow upon Mega Evolution, then gains +1 Sp. Atk and +1 Sp. Def at turn end while weather persists.
- All eight Gyms use a signature Mega ace in a fixed story order. See [the campaign blueprint](CAMPAIGN_BLUEPRINT.md) for the chapter route, proposed encounters and ending.
- Story mysteries: Professor Birch missing, Norman missing for ~15 years, Team Null led by May.
- The precise fates of Norman/Birch, Milotic's ability, Grimyena's evolution method, and individual Gym teams are **not locked**.

## Files

- `data/species.json`: proposed new species/form base stats, typings, and art direction.
- `data/abilities.json`: agreed vs proposed custom ability behavior.
- `data/world.json`: evolving Hoenn, characters, geography, and Gym roster.
- `tools/validate_design.py`: standard-library checks; run `python3 neo_emerald/tools/validate_design.py`.

## Ranger opening and terrain (development branch)

- In-game Ranger starter selection: **Poochyena / Spheal / Shroomish** on `neo-emerald/phase-1-ranger-starters` (code committed, ROM not yet built or playtested).
- Mossdeep dispatch now opens the three-ball chooser and returns to the map instead of the old Route 101 first battle; sailor and local NPCs provide first rescue clues.
- Terrain plan and source coordinates: [Mossdeep opening and terrain specification](design/mossdeep_opening_terrain.md).
- Original Mossdeep map collision and visuals have **not** yet been rebuilt.
- This branch now initializes the Mossdeep respawn point on New Game. It also registers `LAYOUT_MOSSDEEP_CITY_STORM`, a byte-identical and independently editable copy of original Mossdeep terrain. Compile and emulator verification are still outstanding.
- Shroomish still evolves into Breloom normally; a future third-stage evolution after Breloom is a design idea, not implemented.

## Implementation milestones

1. **First build** of the Neo Emerald working branch, using a supported ARM toolchain. Do not assume GitHub Actions quota is available.
2. **Grimyena prototype data added:** species ID, Dark/Fire stats, temporary Mightyena artwork and cry, and provisional level-38 evolution. Build/playtest this before replacing the placeholders with original battle/overworld sprites, learnset, cry and unique Pokédex registration. The placeholder National Dex number is NONE; the Pokédex integration is not finished.
3. Build/playtest Grimyena before integrating **Mega Grimyena**, Grimyenite, and a chosen Twin Fang specification.
4. Implement **Mega Breloom** + Chaos Spores and **Mega Walrein** + Permafrost (and battle tests).
5. Implement Mega Milotic after ability and stats are confirmed. Its current sprite artwork is a **concept image**, not verified GBA-ready sprite data.
6. Add fixed chapter-specific Gym teams, then redesign Hoenn maps and implement Mossdeep evacuation events.

## Verified source entry points (expansion fork)

- `include/constants/species.h` (species IDs)
- `src/data/pokemon/species_info/gen_3_families.h` (Gen III species families)
- `src/data/pokemon/form_change_tables.h` (Mega evolution form changes)
- `include/constants/abilities.h` (ability IDs)
- `src/data/pokemon/species_info.h` (includes family data)

Custom species require **additional coordinated changes**: graphics/palettes, evolution, form connections, item, texts, and maybe dex/learnsets. This is a work plan, **not an implemented ROM**.

## Safety

Do not commit retail ROMs, proprietary game assets, credentials, or private data. Distribute a patch rather than the source ROM. Leave `master` stable and make code changes on working branches. Credit the RHH expansion contributors as their README requests.

## First build (Codespaces or Ubuntu/WSL)

Open this branch in a configured development environment. The repository includes a `.devcontainer` for GitHub Codespaces; using Codespaces can consume your account's monthly quota or incur charges. From the terminal:

```bash
bash neo_emerald/tools/build.sh
```

If successful, the **prototype** ROM is `neo_emerald/out/NeoEmerald_Prototype.gba`. The build script does not upload the ROM. It still uses original Emerald maps and story, and Grimyena currently looks/sounds like Mightyena until our graphics pipeline is ready.

The simple design/source checks run separately with `python3 neo_emerald/tools/check_source.py`; they do not replace a compiler or emulator test.
