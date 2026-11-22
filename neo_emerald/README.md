# Pokémon: Neo Emerald — development workspace

**Status: planning data committed; playable engine changes NOT yet installed.** This subfolder keeps Neo Emerald design data separate from the upstream `pokeemerald-expansion` source.

## Design decisions

- Hoenn, 25 years later, significantly changed by climate and geological events.
- Opening: Mossdeep evacuation; its tech metropolis is sinking into the sea.
- New playable line: Poochyena → Mightyena → **Grimyena** (Dark/Fire) → **Mega Grimyena** (Dark/Fire, Cerberus-style).
- Custom Megas: Breloom (Grass/Fighting), Walrein (Water/Ice), Milotic (Water), and Grimyena.
- **Chaos Spores:** Mega Breloom's contact-hit status attempt (20%; burn/sleep/poison/paralysis).
- **Permafrost:** Mega Walrein brings hail/snow upon Mega Evolution, then gains +1 Sp. Atk and +1 Sp. Def at turn end while weather persists.
- All eight Gyms use a signature Mega ace and scale their teams by number of badges, regardless of challenge order.
- Story mysteries: Professor Birch missing, Norman missing for ~15 years, Team Null led by May.
- The precise fates of Norman/Birch, Milotic's ability, Grimyena's evolution method, and individual Gym teams are **not locked**.

## Files

- `data/species.json`: proposed new species/form base stats, typings, and art direction.
- `data/abilities.json`: agreed vs proposed custom ability behavior.
- `data/world.json`: evolving Hoenn, characters, geography, and Gym roster.
- `tools/validate_design.py`: standard-library checks; run `python3 neo_emerald/tools/validate_design.py`.

## Implementation milestones

1. **Baseline build** of unmodified expansion, using a supported ARM toolchain. Do not assume GitHub Actions quota is available.
2. Implement **Grimyena** as a proper new species (Mightyena evolution) with temporary **distinct and appropriately licensed** battle sprite, learnsets, evolution, encounters and Pokédex registration.
3. Build/playtest Grimyena before integrating **Mega Grimyena**, Grimyenite, and a chosen Twin Fang specification.
4. Implement **Mega Breloom** + Chaos Spores and **Mega Walrein** + Permafrost (and battle tests).
5. Implement Mega Milotic after ability and stats are confirmed. Its current sprite artwork is a **concept image**, not verified GBA-ready sprite data.
6. Add badge-count Gym teams, then redesign Hoenn maps and implement Mossdeep evacuation events.

## Verified source entry points (expansion fork)

- `include/constants/species.h` (species IDs)
- `src/data/pokemon/species_info/gen_3_families.h` (Gen III species families)
- `src/data/pokemon/form_change_tables.h` (Mega evolution form changes)
- `include/constants/abilities.h` (ability IDs)
- `src/data/pokemon/species_info.h` (includes family data)

Custom species require **additional coordinated changes**: graphics/palettes, evolution, form connections, item, texts, and maybe dex/learnsets. This is a work plan, **not an implemented ROM**.

## Safety

Do not commit retail ROMs, proprietary game assets, credentials, or private data. Distribute a patch rather than the source ROM. Leave `master` stable and make code changes on working branches. Credit the RHH expansion contributors as their README requests.
