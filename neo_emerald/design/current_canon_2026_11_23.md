# Pokemon: Neo Emerald — Current Story Canon
**As of 2026-11-23.** Source of truth for future integration. This design sheet is not evidence a ROM feature is playable.

## Timeline and premise
Hoenn is approximately 25 years beyond the original Emerald/ORAS-era adventure. The player begins as a rookie Ranger amid the Mossdeep City flood. Rangers protect people and Pokemon, progress through field missions, and earn Gym badges to qualify for advanced rank and gear.

## Chapters 1–3
1. Preserve Birch's prerecorded Ranger orientation, Ari/June, the flooded Mossdeep terrain, the broken rescue rig, the missing child and Poochyena, the collapsing stairs, upstairs evacuation, late-siren mystery, and Hale's debrief. These are not to be rewritten into a new ferry-first opening.
2. Three Ranger starters: Poochyena (level 5, Fire Fang), Spheal (level 5, Ice Beam), Shroomish (level 5, Giga Drain). Level 5 is initial only. Normal EXP and evolution continue; Ranger mission bonuses begin around 250 EXP at Rank 1, 300 at Rank 2, with larger major-mission awards.
3. Only after the complete rescue and Commander Hale debrief, Hale receives a call: the evacuation vessel made an emergency landing near Mr. Briney's old cottage on Route 104. Hale flies the player to Rustboro to meet a contact. **There is no forced ferry journey through Petalburg Woods before meeting the rival.**
4. Gender-swapped rival: male player gets **Nessa** (purple hair); female player gets **Vern** (blue hair). Both are Commander Hale's child. They use the authentic Gen 3 male/female Ranger visual foundation, one shared story/dialogue/mission/battle framework, and the starter that is strategically favorable against the player's chosen line: Poochyena→Spheal; Spheal→Shroomish; Shroomish→Poochyena.
5. Chapter 2: Rustboro University/Ranger headquarters introduction; Petalburg Woods Neo Magma investigation; rival demonstrates Ranger Cutter through a permanently cleared obstruction; Briney cottage/Route 104 Neo Aqua supply incident; Briney jokes about being 104 and Peeko **remains a Wingull**; return to Hale to receive a one-badge promotion requirement.
6. Chapter 3: After **any** one Gym badge, Hale certifies Rank 2 and installs Cutter once. Mission then follows Route 116 to Rusturf Tunnel for a rescue, a Magma encounter and evidence of an unidentified third signal. Team Null's objective is not revealed here. Ranger rewards and obstruction clear flags must survive save/load and never duplicate.

## Systems and access controls
- Any of the accessible low-level Gym badges qualifies for Rank 2. Rustboro/Roxanne is convenient, **never mandatory**. Gym rosters and dialogue scale according to progression; the circuit is open-order. An older fixed-order campaign blueprint is superseded by this decision.
- Ranger Cutter uses gear, not a Pokemon HM moveslot. The rival's one-time demonstration cannot later trap the player.
- Mossdeep Gym offers context-sensitive "now's not the time" hints before its story challenge.
- Mossdeep Space Center is inaccessible on the first visit and stays locked until a **specific scripted Steven encounter outside Mossdeep**, not any incidental Steven dialogue. Dynamic hints point to the sailor, Hale, missing child and current Ranger objective.

## Factions and legendary motives
- Ordinary enemies are only **Neo Magma Grunt**, **Neo Aqua Grunt**, or **Team Null Grunt**. Grunts have no individual names; named admins/leaders are separate NPC classes.
- Neo Magma: existing Magma Gen 3 silhouette, BLACK uniform and RED M.
- Neo Aqua: existing Aqua Gen 3 silhouette, WHITE uniform and BLUE A.
- Neo Magma and Neo Aqua compete for **Volcanion** as a power source relevant to land, sea, pressure and climate. Team Null pursues **Arceus** for a separate purpose. No faction is solely responsible for every natural disaster. Preserve larger historical mysteries including Birch, Norman and May without early exposition.
- Kyogre, Groudon and Rayquaza belong to planned Elite Four/Champion rosters, not Chapter 1–3 captures.

## Returnees, Pokédex and Megas
- Steven Stone is president of **Devon Enterprises**, partner to Rustboro University and Ranger gear programs.
- Roxanne is an aged veteran teacher and Steel-specialist Gym Leader; adapt a period-appropriate older educator sprite with her recognizable hairstyle/color. Her Gym supports scaled teams and a signature Mega ace; current source battles do not yet implement this redesign.
- Add full habitat-appropriate families, not species in random grass: Riolu/Lucario, Yamper/Boltund, Snorunt/Glalie/Froslass, Nosepass/Probopass, Wimpod/Golisopod, Jangmo-o/Hakamo-o/Kommo-o. Other candidate families cover storms, erosion, geothermal faults, cave safety and flood response.
- Planned custom Mega Breloom (Chaos Spores), Mega Walrein (Permafrost: weather and +1 SpA/+1 SpD per weather turn), Mega Grimyena (Dark/Fire) and Mega Milotic remain significant. A new evolution **after Breloom** is a separate idea, not a replacement for Mega Breloom.

## Rustboro University district
Rustboro is an academic town, not an unchanged Trainers' School village. Its campus district incorporates the former school, research connections with Devon, students from other regions, Ranger Field Studies, student housing, public safety projects, labs, a quad and transport to rescues. See rustboro_university_v1.md for coordinates and build phases.

## Source/build reality
- The earlier Neo Emerald source branches from Claude/Codespaces exist, including mossdeep-city-v3-streets. That branch contains ongoing terrain and earlier source work but has outstanding compile/QA problems.
- Separately produced Build 10 and Build 11 .gba files are NOT automatically reproducible from this repo branch. Build 11 was a limited faction palette/class patch; it does not contain fully implemented Chapters 2–3.
- Current Rustboro university branch changes only signage, campus NPCs, classroom and neighborhood dialogue (phase 1). Do not present new building art, fly-in, rival, gear, routes, Gym teams or newer Pokemon as already playable.
- Keep master unchanged; finish source reconciliation, compile with ARM tools, boot-test in mGBA, and verify Delta before claiming a new playable release.
