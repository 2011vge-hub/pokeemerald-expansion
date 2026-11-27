# Chapter 3 closing dispatch and regional campaign bridge — v1
Date: 2026-11-26. Narrative only. Integration reference ad8153e32659fb6ad92817ac72c9c6de9f8618e8; previous narrative 67ceb44bc5ff018b8e680ffa3627d0e7bf35a14a. This package does not implement or test anything.

## Reconciliation and authority
Sources: design/continuity_2026_11_26.md, current_canon_2026_11_23.md, chapters_1_to_3_design_bible_draft.md, chapter2_implementation_status.md, story_pillars.md, rustboro_university_v1.md, ranger_partner_training.md, historical CAMPAIGN_BLUEPRINT.md, previous campus quest package, integration scripts RustboroCity_Flat1_1F, RustboroCity, Route116 and RusturfTunnel. Latest continuity overrides historical level 5, fixed Gym order, ferry-first opening and premature May reveal. No independent environment handoff markdown found in integration tree; campus layout remains owned by art/development. Do not change their geometry.
Confirmed: 25 years later; Lv10 Poochyena/Fire Fang, Spheal/Ice Beam, Shroomish/Giga Drain; normal growth; Nessa/Vern are Hale's child with existing counter-starter logic; any one badge qualifies for Rank 2/Cutter; Roxanne Steel, Steven Devon president, Brendan Champion, Norman missing, Wally Petalburg leader. Neo Magma/Aqua seek Volcanion, rogue Rangers seek Arceus; neither target nor third faction identity disclosed in C1–3. Preserve approved custom Mega canon and eventual signature Gym Megas. User approved Ranger Field Examination and delegated Ranger development, but major lore and redesigns still require approval.
Scope: implementation-ready C3 closing dialogue and read-only board; later regional mission destinations and plot milestones are proposals, not authorized new maps or mandatory gates. Campus quest package remains separate.

## Scene 1 — Closing the Rusturf case
Map RustboroCity_Flat1_1F, existing Hale object, after relay copied. Actual source uses VAR_NEO_CH3_STEP 8 -> 9, calls NeoOffice_MissionCredit (+1 mission, +100 career XP, ordinary partner EXP), then NeoOffice_Log and NeoOffice_Board. Preserve order and one-time credit. No new state or reward needed. Do not assume numerical step ordering: tunnel sequence is 7 -> 11 -> 12 -> 8 -> 9.
Append to existing log before board, retaining technician home and original recording lines:
HALE: "The child in Mossdeep heard the siren too late."
"Then M-17 turned up in the woods and on the vessel's manifest."
"Now this. Three clues. Not three answers."
"We don't know who made that third call, or why."
"I'll ask Devon to compare the records. You keep helping the people in front of you."
Player choice optional, not mandatory: "Was it Magma?" / "Was it Aqua?" / "What comes next?"
Magma: "They wanted the relay. That doesn't prove they interrupted it."
Aqua: "They wanted the supplies. We still need evidence."
Next: "Rest, train, and check the dispatch board. The League and the field both need you."
All converge on existing board; no morality score or faction allegiance. If text menu is costly, use one shared response covering uncertainty. Hale's motivation is to protect his crew and prevent premature accusations.

## Scene 2 — Dispatch board
Existing NeoOffice_Board text after exact step 9; no new prop required (Hale can read it aloud). Replace terminal-only status with:
"RUSTURF: Both technicians safe."
"MOSSDEEP: Relief crews on duty."
"INVESTIGATION: Relay log under review."
"TRAINING: Continue the Gym circuit."
"Check with your commander for new assignments."
Before step 9 retain existing mission guidance, no board diversion. If later regional maps not ready, stop here; do not advertise a reachable destination or create a warp to unfinished content. Existing accessible travel and Gyms remain unchanged. Board is informational, not a new quest engine.

## Scene 3 — Rival response, optional
RustboroCity existing rival contact, only if visible and step 9; preserve greeting and earlier instructions. Both variants share plot, counter-starter and flags. Use same script text with existing name/gender selection:
NESSA / VERN: "I wanted to beat you to the next badge."
"Then I heard those technicians had been trapped."
"I still want to win. But I want us both to make it home."
If player has more than one badge: "You've been busy with the League. Don't think I'm giving up!"
Otherwise: "Next time we battle, I'm not holding back."
No new battle or teleport, no duplicate rival object. If absent, skip. Motivation: competitive ambition matures into concern without abandoning rivalry.

## Scene 4 — Campus public response
Use existing 3F climate archive scholar or engineer dialogue menu, only after C3 completion. Do not replace campus quest menu or consume quest rewards.
Engineer: "The commander sent us a copy. A signal can be genuine and still be misunderstood."
Scholar: "We keep the old records because a new reading needs something to compare against."
If Devon Internship complete, optional line: "Remember the practice readings? Same rule: check the instrument first."
No new evidence flag; optional environmental detail: existing notice board reads "Relay maintenance: crews accounted for." No new sprites or map edits.

## Regional dispatch proposals (not yet map-ready)
The following is an authored narrative spine with flexible badge order, not a fixed Gym itinerary. A chapter advances on completed story objectives plus badge eligibility where appropriate; never require a specific badge for generic rank. Existing rank names Rookie/Ranger/Senior/Area/Top remain; future thresholds require design and engine reconciliation. A player who already has enough badges should qualify without re-battling. Story-critical travel requires safe reciprocal routes and explicit access checks.
- First regional case (1–2 badges): Slateport harbor relief logistics. A dock worker reports mismatched shipment records; player checks two manifests, helps clear a safe supply route, confronts a Neo Aqua grunt seeking pressure readings. Reward ordinary rank-scaled partner EXP once. Proposed hook: one independent record corroborates a timing discrepancy, not its cause. Alternative first assignment if Slateport inaccessible: hold dispatch until route ready, never force a warp. Gym Water specialist optional; signature Mega and scaled team subject to battle track.
- Parallel inland case (2–4 badges): Relicrest/Route111 and Lavaridge resort. Survey crew observes unusual heat/pressure; player escorts crew and compares measurements. Neo Magma argues inland settlements need stable land; Neo Aqua argues coastal adaptation. Their rivalry becomes legible before Volcanion reveal. Fossil and Fire Gyms remain independent. Optional side quest: return a misplaced survey marker, 2 Repels, no story gate.
- Investigation (4–6 badges): Mauville, Birch's newer lab, abandoned Littleroot, Petalburg/Wally. Discover discrepancies in archived patrol and research records, not definitive fates. Steven's designated later encounter outside Mossdeep remains the only Space Center unlock. Team Null identity and rogue Ranger status can be revealed here only after approval of timing. Wally's motivation: protect his community while respecting Norman's memory. Rival investigates a separate lead, then shares it; no gender-specific plot split.
- Escalation (6–8 badges): Fortree, Dewford cavern, Pacifidlog and Mossdeep revisits. Rescue witnesses and recover independent records; combine inland and coastal evidence. Volcanion and Arceus motives become explicit only at approved reveal milestones. Do not decide precise cause, Null leader, Birch/Norman fate or legendary outcome. Reunite with rescued child/Poochyena if later placement approved; optional callback: "I know what to do when the siren sounds now."
- Finale and League (8 badges): resolve major regional crisis through Ranger operations and consequential battles; preserve lasting effects of disasters. Proposed League gate requires eight badges plus resolved crisis, not optional quests or rank grinding. Victory Road -> Elite Four -> Brendan, each with challenging, counterable teams. Weather trio planned late roster roles, not early captures. Postgame restoration and rematches acknowledge earlier missions.

## Evidence/payoff ledger
| Seed | Current meaning | Proposed later payoff | Do not lock |
|---|---|---|---|
| Late siren | Warning arrived after water | Compare independent dispatch records in Mauville | Who delayed it or why |
| M-17/manifest | Same identifier in two reports | Harbor logistics cross-check | Faction responsibility |
| Third signal | Precedes relay interruption | Independent signal comparison in midgame | Identity, intent, causation |
| Birch recording | Mentor's earlier orientation | Research archive context | Fate or guilt |
| Norman absence | Missing ~15 years | Wally/patrol record thread | Fate or guilt |
| Ranger rescue | Lives before equipment | Finale prioritizes evacuation | Exact final crisis mechanism |

## Handoff and acceptance
C3 changes limited to existing dialogue/menu labels in Flat1_1F, optional Rustboro rival and archive conversations. No numeric flags, vars, trainer IDs or assets allocated. Read exact step 9; do not use >=9 (11/12 are unfinished). Preserve C3 report credit and Cutter state, no extra EXP. No new mandatory cutscene. Verify native text widths, menu cancellation, labels, object presence, all four floors and reciprocal exits; source checks and compilation remain development responsibilities. Acceptance cases: step 8 report credits once and reaches 9; step 9 revisit only board; steps 7/11/12 retain rescue guidance; both rival genders and all three starters retain existing logic; no badge-specific gate; campus quests unaffected; no early faction reveal. Comprehensive playtesting deferred until C1–3 content complete. Future dispatch states symbolic VAR_NEO_REGIONAL_CASE and per-case completion flags only after map and save allocation audit; no implementation authorization for later plot proposals.
Approval queue: precise timing of Null reveal; identity of leadership; Birch/Norman fates; cause of disasters; legendary confrontation and resolution; final League gate and roster details. Next package: first regional case detailed scene script and access dependency plan, after checking C1–3 handoffs and any new approved decisions.
