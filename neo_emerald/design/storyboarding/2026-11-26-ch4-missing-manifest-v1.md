# Chapter 4 — The Missing Manifest (v1)
2026-11-26 | Narrative proposal and implementation handoff, not ROM implementation.
Integration baseline ad8153e32659fb6ad92817ac72c9c6de9f8618e8; narrative parent 22c1c90f4b96aabaaefd765e9b6e949fe6c55705.
Read continuity_2026_11_26, current_canon_2026_11_23, historical chapters_1_to_3 bible, chapter2 status, story_pillars, campus quest and regional dispatch packages. Inspected Slateport city, harbor and shipyard map JSON and harbor scripts. No separate environment branch was present in returned branch listing. Prioritize C1–3 completion before integrating this later case.

## Canon and scope
25 years later; Lv10 Poochyena/Fire Fang, Spheal/Ice Beam, Shroomish/Giga Drain; normal growth; opposite-gender rival Nessa/Vern, Hale's child, existing counter-starter selection. Rank 2/Cutter after any badge and C2 report. Roxanne Steel, Wally Petalburg, Steven Devon, Brendan Champion. Neo Magma/Aqua seek Volcanion; rogue Rangers seek Arceus; neither objective revealed in this case. Preserve all approved Megas and weather trio late League roles. No new major lore locked. This case is a proposed regional story milestone, not a fixed second Gym. Minor dialogue and NPCs under delegated authority; route and major plot approval still needed.

## Access and staging
Require exact VAR_NEO_CH3_STEP == 9, not >=9 (11/12 are incomplete). Existing Slateport has north Route110, south Route109, east Route134 connections; no Gym map in inspected Slateport map inventory. Do not claim a reachable route from Rustboro: transport/route audit and safe return are prerequisites. No forced warp, no ferry ticket bypass. If not ready, Hale retains C3 board. Proposed dispatch availability is independent of badge count beyond existing C3 prerequisite.
City entrance to shipyard at (26,38), harbor public entrance (28,12); preserve reciprocal exits. Shipyard 1F exit (2,14)/(3,14), existing Dock NPC (5,5), scientist (10,7). Use Dock and scientist interaction menus rather than new coordinates. Harbor has vanilla submarine escape scripts, overlapping attendant/Archie objects and hidden patrons. Do not reuse those flags or stage battle there. Proposed battle contact on city public quay, exact free tile after collision audit; fallback shipyard side aisle if art/development confirms safe placement. Never occupy warp or mandatory passage. No new map geometry in this package.

## Scene 1 — Dispatch
Hale: "Slateport has a shipment that doesn't match its records. Relief supplies are waiting on the quay."
"Find out what's missing. Get the supplies moving before you chase a suspect."
Choice: Accept / Later. Later: "The board will be here. Finish what you're doing first."
Accept sets case active only; no teleport. If player visits Slateport before accepting, Dock offers normal dialogue and points to Hale after C3.
Motivation: Hale prioritizes relief over investigation; Dock wants workers safe and shipments released.

## Scene 2 — Two records
Shipyard Dock: "The crates are here. The paperwork says they left yesterday."
"One copy came from the loading crew. The other came from the dispatch office."
Inspect Dock's copy: "M-17 listed as equipment. Departure entry marked pending."
Inspect scientist's copy: "M-17 listed as equipment. Departure entry marked complete."
These are copies of related logistics records, not a second physical gauge. No new exact timestamps or culprit. Flags COPY_A/B, either order. After both, Dock: "Same equipment number. Different status. That explains why the crew won't sign."
Choice: "Release everything" / "Check the relief crates" / "Accuse the crew".
Correct: "Right. Separate the confirmed supplies from the disputed equipment."
Other: "We need to know what's safe to move. Let's check the relief crates first." Retry, no penalty. Set SAFETY once. Existing crate graphic or Dock menu inspection; no item consumed.

## Scene 3 — Quay confrontation
After both copies and safety, reveal one Neo Aqua Grunt (white uniform, blue A, approved silhouette). Interaction starts battle, not a proximity trigger. Grunt: "People keep rebuilding where the sea will take everything again."
"We need those pressure records. Hand them over."
Player: "These supplies are for the relief crews."
Grunt: "Then stay out of our way!"
Proposed trainer team at one badge: Wingull Lv17 (Water Pulse, Wing Attack, Supersonic), Wimpod Lv17 (Aqua Jet, Struggle Bug, Sand Attack), Carvanha Lv19 (Bite, Aqua Jet, Ice Fang, Focus Energy; Oran Berry). At two or more badges use existing badge-tier system if available, otherwise battle track supplies capped regional tier; never silently scale to party level. Validate move/species availability, AI, items and counterplay for all three starters. No Mega at this early grunt. No mandatory second battle. Loss returns via normal recovery, case stays active and grunt remains; no rescue failure or lost evidence. Win sets BATTLE_WON and hides grunt permanently. Grunt retreat: "You think a few crates will change the tide? You'll see." No legendary name, no named grunt, no faction leader cameo.

## Scene 4 — Supplies first
Dock after win: "The relief crates are accounted for. We'll hold the disputed equipment until Devon checks the records."
"Tell your commander we have two copies, not an explanation."
Set objective complete. Return report to Hale or existing approved remote reporting system only if available; no new communication mechanic. Hale: "Good work. You kept the supplies moving and preserved the evidence."
"The forest record and the harbor record agree on M-17. They don't agree on what happened to it."
"Devon can compare them with the relay log. Until then, we keep our options open."
One ordinary Rank 2 partner award (300 EXP if still Rank 2) using existing rank-scaled mechanism, one normal career mission credit using established helper, no automatic promotion or extra badge. Reward atomic/idempotent; if queue cannot accept, leave report pending without duplicate career credit. Do not assume new rank thresholds. Evidence ledger gains independent paperwork discrepancy only.

## Scene 5 — Rival and city texture
Optional Nessa/Vern encounter at shipyard after report, same plot and shared flags, existing gender graphics. Nessa: "I was going to challenge you at the docks. Then I saw how many people were waiting for supplies." Vern: "I had a battle plan ready. Turns out the crew needed a different kind of help." Shared: "Next badge is still a race, though!" If absent, use later existing rival conversation; never spawn duplicate. No rival battle required.
Public NPC: "The market opens early now. Boats unload before the afternoon wind."
Sailor: "The old quay is for equipment. Relief cargo goes through the sheltered entrance." Only use if art confirms geography; fallback "Relief cargo gets checked twice now."
Optional quest — A Dry Delivery: after case report, market volunteer asks player to deliver a sealed note to Dock. Offer "Could you tell the loading crew their blankets are ready?" Dock "Good. We'll send someone for them." Return "That's one less thing to worry about." Reward 2 Super Potions once, no new item or evidence. Decline/retry/full bag supported. No connection to faction guilt.
Water Gym: future harbor captain concept remains separate. Existing map inventory has no Gym; no new badge or forced Gym order. Proposed tactical teaching theme rain, speed control and mixed coverage; signature Mega choice and roster owned by battle design, not locked here.

## State contract (symbolic, allocate after audit)
VAR_NEO_SLATEPORT_CASE 0 unavailable/not accepted, 1 active, 2 objective complete, 3 reported. Prerequisite exact C3 step 9 plus verified travel. FLAG_NEO_SLATEPORT_COPY_A/B, SAFETY, BATTLE_WON; monotonic. Optional VAR_NEO_DRY_DELIVERY 0/1/2/3. Proposed flags are not existing engine constants. Use existing report/partner queue helper; audit save allocation, avoid vanilla harbor state VAR_SLATEPORT_HARBOR_STATE and FLAG_MET_TEAM_AQUA_HARBOR, no old Archie submarine scene activation. Grunt visibility derived from active + safety + !win, not legacy Aqua visibility. On reload restore state and release locks. Before case active no new battle. After report no repeat rewards. If map access cannot be verified, keep package staged and do not expose dispatch.

## Acceptance criteria (not executed)
- C1–3 content and campus quests unchanged; exact C3 step 9, any first badge; no specific Gym gate.
- Both records inspect in either order, incorrect safety choices recover, player can leave and return at every state.
- Battle reachable by interaction, loss/retry works, win persists across save/load, no duplicate grunt or blocked warp.
- All three starters and both rival variants remain valid; no mandatory rival or optional quest.
- Report credits once even with boxed partner or full queue; optional full bag leaves reward pending.
- Vanilla harbor/submarine state untouched; no original-era Archie scene or ferry access accidentally triggered by this case. Audit inherited legacy triggers separately before release.
- Art handoff: existing Dock/scientist/sailor, approved Neo Aqua grunt palette, crate prop only if needed; no significant redesign or new species.
- Source checks for unique IDs, map links, text widths, trainer constants, save flags, and compilation before release. Comprehensive playtesting deferred until C1–3 complete; no testing claimed here.

## Payoff and next package
The two records independently corroborate M-17's logistical inconsistency; do not equate that with the late siren or third signal yet. Next case: inland survey at Relicrest/Lavaridge contrasts coastal adaptation with Neo Magma's land stability argument; compare pressure records without proving a common cause. Keep Birch/Norman fates, Null leadership/reveal timing, Volcanion/Arceus confrontation and final League gate open for approval. Maintain eight badges -> Victory Road -> Elite Four -> Brendan as the competitive endpoint, with regional crisis resolution proposed before League. No optional quest or rank grinding as League prerequisite.
