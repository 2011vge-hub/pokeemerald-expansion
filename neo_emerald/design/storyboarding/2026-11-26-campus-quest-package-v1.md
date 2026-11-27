# Rustboro campus quest package v1 — 2026-11-26
Status: implementation-ready narrative specification, not implemented or tested. Based on integration ad8153e32659fb6ad92817ac72c9c6de9f8618e8. New dialogue, rewards and minor NPCs are delegated design choices. Field Examination approved by user; five other quest titles approved in continuity. No major lore decisions made.

## Sources and precedence
Read continuity_2026_11_26.md, current_canon_2026_11_23.md, chapter2_implementation_status.md, chapters_1_to_3_design_bible_draft.md, rustboro_university_v1.md, story_pillars.md, ranger_partner_training.md, four campus floor scripts and flag/var definitions. Latest continuity wins: starters Lv10 with Fire Fang/Ice Beam/Giga Drain, any one badge qualifies, third signal unidentified. Historical story pillars naming May as Null leader is not authorization to reveal or lock identity. Previous standalone campus and examination drafts were not committed; this package consolidates their useful ideas under approved quest titles. Existing source floor transport is NPC-assisted; preserve it until art/development teams provide reciprocal stairs. Do not overwrite approved art or use unverified coordinates.

## Campaign continuity
C1 rescue remains player-controlled, child/Poochyena and late siren, Hale prioritizes lives. C2 rival, Woods M-17, Cutter demonstration, Briney evacuation manifest, Hale any-badge requirement. C3 rank 2/Cutter, west flats, Route116, Rusturf technicians, unidentified third signal, report. Optional quests are parallel to these beats. No early Volcanion/Arceus names or Null identification. Long-term approved targets: Neo Magma/Aqua pursue Volcanion; rogue Rangers pursue Arceus; Birch and Norman mysteries remain unresolved. Brendan reigning Champion; eight badges, Victory Road, Elite Four and Champion remain full campaign goals. Later acts and rank names beyond current engine are proposals only. Keep existing Rookie/Ranger/Senior/Area/Top rank system rather than silently replacing it.

## Scene staging and state contract
Use existing maps RustboroCity_PokemonSchool (1F), RustboroCity_University_2F, _3F, _4F. Place new interaction points on verified free floor tiles, never on warps, NPC movement paths or lift landing tiles. Prefer existing student, scientist, school kid, teacher graphics; reuse existing text boxes and item icons. No new portrait required. Each quest uses one proposed persistent variable VAR_NEO_CAMPUS_Q1 through Q6: 0 not accepted, 1 active, 2 objective done, 3 rewarded. Allocate only after auditing vars.h and save storage; names are symbolic, no numeric IDs reserved. Optional stage-specific flags below are symbolic. Existing flags FLAG_NEO_C1_FLIGHT_RUSTBORO, FLAG_NEO_C2_RIVAL_MET, FLAG_NEO_C2_BRINEY_REPORTED, FLAG_NEO_C2_DEBRIEF_DONE and VAR_NEO_CH3_STEP are read-only prerequisites; confirm exact final C3 step in integration before wiring. Do not repurpose existing flags or Riolu egg/Quick Claw rewards. Each reward uses existing item grant success check; full bag leaves state 2, no duplicate payout. No item consumed for evidence. Declining leaves state 0. Quest board lists available/active/completed and objective in plain text; no new journal UI required. NPCs never block lifts. Dialogue lines below are draft text, split into native text widths at integration.

## Q1 Missing Field Notes
Available after C2 rival met. 2F student wants a missing notebook, not a new mandatory route. 1F commons bench has an interactable notebook marker; use existing furniture. Return to 2F. State 1->2 on inspection, 2->3 on 3 Great Balls successfully granted.
Offer: "My field notes! I left them downstairs. Could you check the commons?"
Decline: "No worries. I'll look after class."
Active: "Try the bench in the commons. Blue cover."
Inspect: "A notebook: Wingull avoid the low quay when the wind changes. Return it to the student."
Return: "That's it! Observing a Pokemon can save more time than battling one."
Repeat: "I've started making copies of my notes."
Motivation: student learns practical field discipline; environmental clue is ordinary behavior, not proof of conspiracy.

## Q2 Letters from Mossdeep
1F relief volunteer after C2 Briney reported. Deliver a message to Briney at existing cottage, then return. No additional rescuee relocation or new ferry warp. State 1->2 via optional Briney dialogue after main evidence conversation; reward 2 Super Potions.
Offer: "A family in Mossdeep wants to thank the mainland crew. Could you carry their letter to Briney?"
Decline: "I'll keep it safe until someone heads south."
Briney: "A letter for me? At my age, it's nice to know I'm still useful! Peeko, we're famous!"
Return: "I'll tell the family their message arrived. Thank you, Ranger."
Repeat: "The relief crew sends its regards."
Do not assert the rescued child wrote it; later reunion remains possible.

## Q3 The Devon Internship
3F sensor engineer after C2 debrief. Compare two public sample readings on 3F desks, A and B, using proposed flags FLAG_NEO_CAMPUS_SAMPLE_A/B. No actual M-17 evidence duplicated. State 2 only when both inspected; reward 2 Repels.
Offer: "These are practice readings. Can you compare the pressure records?"
A: "Sample A: steady pressure. Recorded during calm weather."
B: "Sample B: a sudden spike. Instrument status uncertain."
Return: "Good. A spike is evidence, not an explanation. Always check the instrument."
Repeat: "Devon is checking its equipment. We won't guess at the cause."
No claims Steven caused anomalies or direct access to Space Center. Preserve engineer's existing investigation line.

## Q4 A Professor's Challenge
4F Roxanne after C2 rival met. Optional training match against a faculty student on 2F, not Roxanne herself and not a badge battle. Proposed team for zero badges: Magnemite Lv12 (Thunder Shock, Thunder Wave, Sonic Boom), Rookidee Lv12 (Peck, Hone Claws, Power Trip). For one or more badges during C3: Lv15 and 16, respectively, with Oran Berry on Rookidee. Verify species, moves and AI in actual source; no new species. Use dedicated trainer ID, not Gym trainer IDs. Defeat uses normal recoverable loss; state stays 1. Win sets state 2; return to Roxanne for 2 Sitrus Berries.
Offer: "A student is practicing speed control. Would you help with a demonstration?"
Student: "A faster opponent isn't always the one that moves first!"
Loss/retry: "Try a different lead. I'll be here when you're ready."
Win: "You adapted! That's what our lessons are for."
Roxanne: "Good. A strong team needs a plan, not just power."
Repeat: "Keep studying your opponents."
No mandatory battle, no badge, no Gym roster or difficulty overhaul changes.

## Q5 The Unfinished Map
3F archive scholar after C2 debrief. Inspect old route map and modern survey on 3F; flags FLAG_NEO_CAMPUS_MAP_OLD/NEW. State 2 after both; reward 1 Escape Rope.
Offer: "These maps disagree. Can you find the differences?"
Old: "An older survey shows a coastal footpath that no longer exists."
New: "The modern survey marks the same area as unsafe."
Return: "The land changes faster than our records. Never trust an old route without checking."
Repeat: "Some surveys remain incomplete."
Optional later callback: a familiar survey notation in a midgame investigation; no named author, Norman fate, hidden location or new legendary clue locked here. Archive scholar lift remains a separate menu option.

## Q6 Ranger Field Examination
2F instructor after C2 debrief, available with zero badges or later. No requirement to finish Q1–Q5. One contained practical exercise in 2F with a training student and existing dummy/supply crate prop. Three stages: choose response, win training battle, inspect simulated rescue point. Proposed FLAG_NEO_CAMPUS_EXAM_SAFETY, _BATTLE, _RESCUE; flags persist and state 2 after all three. No timed challenge or live danger.
Instructor: "A Trainer measures success by victory. A Ranger must also measure what they managed to protect. Today we'll examine both."
Question: "A Pokemon is trapped near unstable stairs. What comes first?"
Choices: "Secure the area" / "Retrieve equipment" / "Rush inside".
Correct: "Right. Protect the people and Pokemon before the equipment."
Incorrect: "An unsafe approach creates another rescue. Try again." No punishment, repeat menu or leave.
Training student: "Show me how you'd handle an opponent while keeping your partner safe."
Proposed battle: Lotad Lv12, Machop Lv13 before first badge; Lv15/16 afterward, basic AI and sensible moves (Water Gun, Absorb, Astonish; Low Kick, Karate Chop, Focus Energy). Verify move compatibility. Loss leaves safety stage complete; retry. Win sets battle flag.
Crate interaction after battle: "Training marker: the route is clear. The simulated rescue is complete."
Before battle: "Complete the supervised battle before approaching the marker."
Instructor completion: "You assessed the risk, adapted in battle and finished the rescue. That's fieldwork."
Reward: queue one ordinary rank-scaled partner EXP award using existing special (250 Rookie, 300 Ranger, etc.); no 1000 major reward, no new rank or career XP, no automatic promotion. Mark rewarded once and use existing queue saturation behavior; confirm queue can accept full award before marking paid or explain retry. If partner boxed, existing queue persists.
Repeat: "Your examination is complete. The field is your next classroom."
Optional rival reaction on next safe campus conversation, not a new mandatory cutscene. Nessa/Vern same shared line: "I thought the battle would be the hard part. Guess there's more to this job than winning." After Woods use: "After what we saw in the woods, I understand why they teach this." Select existing rival gender/name/counter-starter logic, no new asset or battle. If rival not present, omit reaction; never respawn into a warp.

## Implementation acceptance
1. All six quest state transitions survive save/load; decline and full bag recover; rewards once; Q6 partner queue credited once with correct rank.
2. Any badge or none: all four floors remain reachable, Q4/Q6 optional, no altered Gym flags or rank gates. Existing Quick Claw and Riolu egg remain independent.
3. Q2 cannot preempt main Briney evidence; Q3/Q5 do not write story evidence; no early faction/legendary reveal.
4. Both genders retain rival name and approved graphics; no new mandatory cutscene or transport.
5. Source checks: unique allocated flags/vars/trainer IDs, existing graphics, script labels, text width, reciprocal exits, collision/warp review; compile before release. Comprehensive emulator playtesting deferred until C1–3 content complete; these are acceptance criteria, not test results.
6. Art handoff: existing props and NPC sprites only; if no free tiles, integrate via existing NPC menu rather than change floor geometry. Main development owns scripts and trainers; narrative branch owns this document only.

## Next package
C3 post-report transition and regional mission board: establish a concrete causal route into later Hoenn while preserving open-order badges. Later major reveals (May identity, Birch/Norman fates, precise cause of anomalies, final legendary confrontation) need explicit approval. No additional approval required for these minor campus dialogues and reasonable rewards.
