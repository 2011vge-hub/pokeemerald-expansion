# Chapter 6 — The Lost Expedition (v1)
2026-11-27 | Narrative proposal / conditional implementation handoff. No ROM implementation or testing.
Integration reference ad8153e32659fb6ad92817ac72c9c6de9f8618e8; narrative parent c93bc9f8e1dcd8e7bb544d27e3aa81dac2a2d913.
Reviewed latest continuity, current canon, opening design bible, C2 status, story pillars, partner training, C3–5 dispatch packages and relevant map definitions/scripts. No separate environment branch identified in returned branch list. C1–3 completion remains the implementation priority.

## Canon boundaries
Hoenn 25 years later. Birch missing; his expanded lab is in Mauville, former Littleroot lab abandoned and overgrown. Norman missing approximately 15 years; Wally leads Petalburg, Wattson retired, Steven leads Devon, Brendan Champion. Preserve Lv10 Poochyena/Fire Fang, Spheal/Ice Beam, Shroomish/Giga Drain, normal growth, approved Ranger assets and Mega canon. Nessa/Vern are Hale's child, opposite gender and existing counter-starter selection. Neo Magma/Aqua pursue Volcanion; rogue Rangers pursue Arceus. Do not reveal targets, Null leadership, May's role, Birch/Norman fate or a definitive cause here. Weather trio remain reserved for League roster roles. All new historical records below are proposed clues, not confirmed historical facts.

## Beats and access
Proposed four-badge dispatch after C5 reported, not a specific Gym order. Existing rank names Rookie/Ranger/Senior/Area/Top; do not create a new rank or promotion threshold. Require safe round-trip routes before enabling dispatch. Mauville connections Route110/111/117/118; no dedicated Birch lab warp in inspected map. Littleroot connects Route101 to Oldale; old lab door (7,16), interior exits (6,12)/(7,12). Old lab still contains vanilla Birch/rival/starter objects; Route101 contains Birch bag and Pokédex scripts. Mauville still has young Wally and Wattson legacy events; Petalburg Gym contains Wally tutorial scripts and placeholder Wally object. These are blockers, not scenes to reuse blindly. Art/development own replacement maps, collision, reciprocal warps and legacy event retirement. If unavailable, leave dispatch on hold; no forced warp or old starter event. Do not move existing NPCs or claim redesigned locations playable.

## 1. Dispatch — Hale office
Hale: "Devon compared the harbor and inland records. They want the original research index."
"Birch moved his work to Mauville years ago. Start with the people who kept his records."
Accept / Later. Later: "The assignment can wait. Finish your current work first."
Accept sets ACTIVE only. Motivation: independent corroboration, not blame. No mandatory rival battle.

## 2. Mauville — research reception
Future Birch lab public reception; fallback approved public research liaison only after travel and NPC audit. Stock scientist sprite, no impersonation of Birch. Liaison: "We have copies of Professor Birch's field reports, but the old index is incomplete."
"Some of the references point back to Littleroot. We need to know which records survived the move."
Choice: "When did he leave?" / "What should I look for?"
First: "The move and his disappearance are different events. I can't tell you where he is now."
Second: "Look for the index, not the equipment. Leave anything unsafe alone."
Both grant MAUVILLE_BRIEF once, no key item. Optional retired Wattson dialogue only after retirement redesign: "A city can replace its machines. Replacing what people remember is harder." No legacy Gym reward.

## 3. Route101 — field survey
Stage on safe public side tile after collision audit; never reuse Birch bag, starter encounter or old rescue flags. Minor survey Ranger: "A Pokémon has been guarding the path to the old lab. We can go around, but I'd rather know why."
Inspect tracks via menu: "Tracks lead away from the building." Inspect nearby shelter: "A sheltered spot, clear of the path." Either order. Choice: "Chase it away" / "Leave a clear escape route" / "Enter the shelter".
Correct: "Good. Give it room, then we'll check the public path." Other: "We don't need to corner it. Try leaving it a way out." Retry without penalty. Set SURVEY_SAFE once; no capture or forced wild battle.
Optional supervised trainer practice after survey, distinct from story battle: Ranger trainee with Manectric Lv30 (Volt Switch, Bite, Thunder Wave, Quick Attack), Breloom Lv31 (Mach Punch, Seed Bomb, Stun Spore, Rock Tomb), Pelipper Lv32 (Water Pulse, Air Slash, Roost, Protect; Sitrus Berry). Proposed four-badge band, battle track validates legality, AI, weather and counterplay. Decline/loss never blocks archive. Standard recovery; victory flag once. No Mega.

## 4. Littleroot — abandoned lab
After MAUVILLE_BRIEF and SURVEY_SAFE, inspect old lab only after geometry/legacy scripts cleared. Use entrance-side archive desk on verified walkable tile; if interior unsafe, approved exterior archive handover by survey Ranger is fallback, not a magical teleport. No active Birch, rival or starter balls.
Environmental text: "A faded sign: FIELD RECORDS — RETURN TO INDEX." / "The shelves are empty. A paper label remains."
Index text: "Reference: regional field observations. Original pages transferred. Cross-reference: patrol archive."
Player: "The index points to another archive. It doesn't say where Birch went."
Set INDEX_COPIED once; no invented date, culprit, secret facility or proof Norman worked with Birch. The reference is a proposed minor clue requiring continuity review before integration.
Optional Nessa: "I thought we'd find a note that explained everything. It's strange how much an empty room can tell you."
Optional Vern: "I kept looking for a complete report. Maybe the missing pages are the reason we need to keep looking."
Shared: "Let's check the patrol records before we decide what it means." One shared optional flag, no altered rival starter or battle logic.

## 5. Petalburg — Wally's recollection
Wally as adult Gym Leader, optional public staff consultation or approved Wally interaction outside battle arena. Existing Gym entrance staff at (4,107) and (3,109) are candidate menu hosts only after script audit; Wally placeholder at (4,111) overlaps exit row and must not be used as staging coordinate. Do not require defeating Wally or trigger vanilla catching tutorial. If Wally not ready, defer dispatch rather than substitute Norman.
Wally: "Norman taught me that being strong meant showing up when someone needed you."
"He disappeared about fifteen years ago. I still don't have an answer."
"The old patrol archive might help you follow that reference. I'll ask for a copy."
Choice: "Do you think he's alive?" / "Did he know Birch?" / "Can I help?"
Responses: "I hope so. Hope isn't evidence." / "They both worked in Hoenn. That doesn't tell us what happened." / "Keep the records intact. Don't promise answers you don't have."
Set PATROL_REQUESTED. Staff provides a public archive receipt: "Request received. Historical record search pending." Set RECEIPT_COPIED. No fabricated last sighting or classified file. Wally's motivation: protect his community and preserve Norman's legacy without pretending certainty.
Gym encounter separate: Wally's scaled team should reward coverage, switching and tempo control; retain signature Mega requirement, no new type/ace lock. Pre/post badge dialogue remains valid. Proposed staff hint: "Our leader studies how partners adapt under pressure. Bring a balanced team." Battle team and adult asset owned by respective tracks.

## 6. Report — Hale
Require all four evidence/safety milestones plus receipt. Hale: "You found a reference, not a missing person. That's still progress."
"Devon can compare the research index with the relay records. Petalburg will search its own archive."
"We won't call two disappearances the same case until the evidence says so."
If player asks about third signal: "Still unidentified. Keep it separate from the historical records for now."
Normal career mission credit once using established helper; ordinary rank-scaled partner EXP (300/350/400/450 as applicable), no automatic rank, no extra major bonus. If pending queue cannot accept credit, leave report pending without duplicate career credit. Board: "Historical archive request pending. Continue the Gym circuit."
Foreshadow next proposed regional case: independent records from Fortree/Dewford/Pacifidlog; no new mandatory route or villain reveal.

## Optional quest — A Label for the Shelf
Mauville liaison after brief: "We're sorting the public copies. Could you bring the old shelf label's wording back?"
After INDEX_COPIED: player recites label, no item consumption. Liaison: "That's enough to put the reference in the right place. Thank you."
Reward 2 Super Repels, once; if bag full, pending until retry. No career mission credit, no main progression requirement. Environmental details: relocated research notice in Mauville, overgrown public path in Littleroot, Petalburg notice thanking volunteer patrols. No new historical facts.

## Implementation contract
Symbolic names only, allocate unused IDs after source audit: VAR_NEO_C6_STATE (0 unavailable, 1 active, 2 report pending, 3 reported); FLAG_NEO_C6_MAUVILLE_BRIEF, TRACKS, SHELTER, SURVEY_SAFE, INDEX_COPIED, PATROL_REQUESTED, RECEIPT_COPIED, RIVAL_SEEN, PRACTICE_WON, CAREER_PAID, PARTNER_PAID, SIDE_ACCEPTED, SIDE_PAID. Separate flags or atomic helper for reward retries. State 2 only when brief/safety/index/patrol/receipt complete. All interactions explicitly initiated; no proximity-triggered battle or random event. Map load derives visibility from state, never resets evidence. Do not alter C1–5 flags or legacy badge ownership. Required assets: Mauville lab public reception, abandoned Littleroot exterior/interior, archive desk/sign, existing scientist and Ranger assets, approved adult Wally, existing rival variants. Art owns placement and collision; development owns constants, scripts and compile. No new original Pokémon.
Acceptance: C1–3 remain unchanged; no dispatch before C5 and four badges; any badge combination qualifies; safe travel both directions; no vanilla Birch starter or Wally tutorial; decline/retry/save/load at each stage; both rival variants and all three starters; practice loss/decline does not block; Wally consultation independent of badge; no duplicate EXP/items, bag-full and queue-full retries; no claim of missing persons' fate; source checks and compilation before integration, comprehensive playtest deferred until C1–3 complete.

## Approval boundary and next package
Minor dialogue, practice team, side reward and four-badge dispatch selected under delegated authority. Proposed archive cross-reference must not be treated as confirmed connection between disappearances; approve before locking historical clue. Major decisions still reserved: Norman/Birch fates, May/Null leadership and motives, cause of disturbances, final legendary confrontation. Next: coastal/forest convergence and first credible evidence of a third organization, with identity reveal gated by approval. Preserve eight badges, regional climax, Victory Road, Elite Four, Brendan and postgame.
