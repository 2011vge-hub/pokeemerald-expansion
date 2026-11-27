# Chapter 5 — Pressure Beneath the Sand (v1)
2026-11-26 | Narrative proposal / conditional implementation handoff, not implemented or tested.
Integration baseline ad8153e32659fb6ad92817ac72c9c6de9f8618e8; narrative parent 499b49162c0eb89faf11cf300880e9a1d18fbc23.
Reviewed continuity_2026_11_26, current canon, historical C1–3 bible, C2 status, story pillars, partner training, campus package, C3 dispatch and C4 manifest. Inspected Route111, Route112, FieryPath, LavaridgeTown, Gym 1F and rest stop map definitions. No independent environment branch or handoff found in returned inventory. C1–3 completion remains implementation priority. Do not merge this later chapter ahead of it.

## Canon and boundaries
25 years later; Lv10 Poochyena/Fire Fang, Spheal/Ice Beam, Shroomish/Giga Drain, normal growth; Nessa/Vern are Hale's child, opposite-gender selection and counter-starter unchanged. Any one badge qualifies for Rank 2/Cutter after C2. Preserve existing rank names Rookie/Ranger/Senior/Area/Top, custom Megas, weather trio late League roles. Neo Magma and Aqua seek Volcanion; rogue Rangers seek Arceus. No legendary target or third faction identity disclosed here. May's role is a historical design thread, not a new reveal or final fate decision. Norman and Birch mysteries remain open. Flannery is a veteran Fire leader in resort Lavaridge; Relicrest fossil Gym remains planned. No specific badge order.

## Chapter beats and access
Proposed 2–4 badge regional story band, not a fixed Gym itinerary. Require C4 reported and at least two badges for dispatch; already earned badges count. If C4 is not implemented, stage only. Existing Route111 connects Mauville south, Route112 west, Route113 west; Route112 connects Lavaridge west and FieryPath through two warps. Relicrest map not present in inspected tree. Do not require desert entry, Go-Goggles, Strength, cable car or legacy Mt Chimney battle. Existing Rock Smash obstacles on Route111 and ledges on Route112 require actual access audit, including return travel. If no safe route, keep dispatch unavailable; do not add forced warp or bypass gear. Relicrest future city can host survey office after art approval; fallback is existing accessible public route edge, not a fabricated city.

## Scene 1 — Dispatch
Hale: "Slateport gave us two records of the same shipment. Now an inland crew has asked for help."
"Their readings disagree, and the crew has stopped work. Find out whether the site is safe."
Accept / Later. Later: "No need to rush into a bad situation. Check the board when you're ready."
Accept sets active only. Hale wants independent evidence and safe workers, not a suspect. No teleport.

## Scene 2 — Survey station
Route111 public safe edge; exact free tile allocated after collision audit. Existing rest stop entrance (26,18) and interior exits (3,7)/(4,7) are candidate shelter only if reachable; existing Old Lady at (6,3) retains healing behavior. Use new minor survey technician with stock scientist sprite, not a trainer object or legacy fossil flag.
Technician: "The gauge says the ground is cooling. The spring crew says the opposite."
"We stopped the survey. Can you check the two readings before we go back?"
Inspect local gauge via technician menu: "Surface reading: falling." Inspect second reading via Lavaridge contact: "Spring reading: rising." Different measurements, not proof of sabotage; no new numerical data. Either order once accepted. No physical key item.
Choice: "Restart the survey" / "Keep the crew clear" / "Blame the gauge".
Correct: "Agreed. We can compare the records from a safe place."
Other: "We don't know enough to do that safely. Let's keep everyone clear first." Retry with no penalty. Safety flag after both readings; crew stays at safe staging point, no escort AI or timed rescue.

## Scene 3 — Lavaridge public contact
Use existing town ExpertF at (8,7) or new attendant if dialogue conflict; retain original functions. Town Gym warp (5,15), Center (9,6), Herb Shop (12,15) untouched. Flannery need not leave Gym.
Attendant: "Visitors come for the springs. We close a pool when the temperature changes too quickly."
"Today's reading is from a different place than the survey gauge. Take both back to your crew."
If first reading absent: "The survey crew has the other record." If already inspected: "You've got our copy. Don't lose track of which reading came from where."
Environmental text: "Pool inspection today. Ask staff before entering." Only if art supports signage; otherwise attendant line. No real-world technical simulation.

## Scene 4 — Neo Magma encounter
Route112 safe public side area after both readings and safety. Existing cable car grunts at (26,30)/(27,30) use FLAG_HIDE_ROUTE_112_TEAM_MAGMA; do not repurpose or trigger legacy Mt Chimney events. Allocate separate interaction-only grunt with approved black/red silhouette. If legacy objects overlap, hold staging until development reconciles them. No blocking warp or return path.
Grunt: "The coast can move its docks. What do you expect people here to do with their homes?"
"We need a way to make the land dependable again. Give me those readings."
Player: "The survey crew needs them to stay safe."
Grunt: "Then we'll take them ourselves!"
Proposed two-badge team: Houndour Lv22 (Bite, Flame Charge, Smog, Howl); Baltoy Lv23 (Psybeam, Mud Shot, Reflect, Rock Tomb); Numel Lv24 (Flame Burst, Magnitude, Yawn, Rock Tomb; Sitrus Berry). Validate learnsets/availability, AI and counterplay; later badge tiers use existing system if available, not party-level scaling. No Mega for ordinary grunt. Loss retains records and active encounter, standard recovery; win hides grunt and sets victory. Retreat: "You can't ask a town to wait forever." No named grunt, no legendary target, no claim Magma caused anomaly.

## Scene 5 — Report and rival
Technician after win: "Everyone's accounted for. We'll keep the site closed until the readings can be checked."
Hale: "Good. Two instruments, two places. That isn't proof that either one is wrong."
"Devon can compare these with the harbor records. We have an inland lead now, not a verdict."
Choice: "Is Magma right?" / "Is Aqua right?" / "What about the relay?"
Responses: "People need safe homes. That doesn't justify taking evidence." / "People need safe coastlines too. We don't have to choose between them." / "The third signal is still unexplained. Keep the records separate until we can compare them."
Converge on one report. Normal career mission credit using established helper; ordinary partner EXP 300 at Ranger rank, 350 Senior, 400 Area, 450 Top (250 Rookie if applicable). No automatic promotion; preserve pending queue and original partner identity. Reward once; if capacity prevents credit, leave report pending with no partial duplicate.
Optional rival after report, use existing gender selection and one shared plot. Nessa: "I wanted to see the springs. I didn't expect to help close one." Vern: "I thought the two readings would settle it. Turns out we needed more context." Shared: "Still planning to beat you to the next badge." No forced battle, no duplicate legacy Lavaridge rival. If placement conflicts, deliver at later existing contact.

## Gym and optional quest
Flannery: "A good Fire Trainer knows when to turn up the heat, and when to hold it back." Optional after case, before/after badge variants; existing Gym mechanics and reward remain. Proposed sun, coverage and speed-control theme, signature Mega and roster owned by battle track. Fossil Gym in Relicrest remains separate, no badge forced by this mission. No new Gym map in this package.
Side quest — The Misplaced Marker: after report technician asks "One of our marker tags is missing. Could you check with the rest stop?" Rest stop Old Lady: "A worker left it here. Tell them it's safe." Return technician: "Thank you. Now we can account for the whole kit." Reward 2 Repels once; no new inventory item, no impact on main evidence. If rest stop inaccessible, stage quest until access confirmed. Preserve healing menu, decline/later and full-bag retry. No hidden mandatory collectible.

## State contract (symbolic, allocate after audit)
VAR_NEO_INLAND_CASE 0 unavailable/unaccepted, 1 active, 2 objective complete, 3 reported. Eligibility C4 == 3, >=2 badges, verified route. FLAG_NEO_INLAND_SURFACE, SPRING, SAFETY, WIN monotonic. Grunt visible iff active + both readings + safety + !WIN. Technician sets objective complete only after WIN. Report uses existing mission helper and one-time reward transaction; never use vanilla volcano/desert flags. Optional VAR_NEO_MARKER_CASE 0/1/2/3, reward once. All state persists on reload, release locks on every branch. No new coordinates until art/development verifies free tiles, no new map IDs or scripts in this document.

## Evidence and long-term payoff
Late Mossdeep siren = delayed warning; M-17 = disputed logistics; third signal = unexplained interruption; C5 = differing readings from separate inland sites. No causal link established. Proposed next case: Mauville comparison desk, compare record provenance rather than inventing a culprit; later Birch lab and Wally patrol archive at 4–6 badges. Keep Steven's specific outside-Mossdeep encounter as only Space Center unlock. Team Null identity/reveal timing, Volcanion/Arceus confrontation, Birch/Norman fates, and exact disaster mechanism require approval. League path remains eight badges, regional climax, Victory Road, Elite Four, Brendan, postgame restoration; no optional quest gates.

## Acceptance criteria (not executed)
- C1–3 and campus quests unchanged; C4 prerequisite and any two badges, no specific Gym gate.
- Verify reciprocal travel, gear requirements, no forced warp, no desert or cable-car dependency.
- Both records in either order; wrong answer retry; no battle before safety; loss/reload/retry preserve evidence; victory hides only new grunt.
- Report and optional reward idempotent including full bag and queued EXP cap; original partner identity preserved.
- Existing rest stop healing, Gym, fossil and legacy volcano flags untouched; no duplicate rival or blocked passage.
- No premature legendary or third-faction reveal. Basic source checks and compilation on implementation track; comprehensive playtesting deferred until C1–3 content complete.
- Assets: stock technician/attendant, approved Neo Magma and rival variants, existing signage/gauge menu; no new original Pokémon or major redesign. Art team owns geometry.
