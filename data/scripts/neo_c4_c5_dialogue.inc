@ Neo Emerald C4/C5 dialogue bank — source-ready, NOT assembled or wired.
@ Use the existing approved milestone v2; Rill/Sable are working names.
@ No flags, battle IDs, coordinates, map IDs, or rewards are allocated here.
@ Text labels are global only when this file is deliberately included.
@ Page breaks: at most 2 lines per page; target 32 characters per line.

@ C4.08 | after crew safe, before final evidence; face player, do not obstruct exit
NeoMilestone_Text_RillArrival::
	.string "RILL: Leave that gauge running.\p"
	.string "The pressure beneath these\nislands has changed.\p"
	.string "We need the readings to\nunderstand why.$"

@ C4.08 | player confronts interference; before battle
NeoMilestone_Text_RillChallenge::
	.string "RILL: Your people aren't our\nenemies, RANGER.\p"
	.string "But we're not leaving without a\ncopy.\p"
	.string "If you insist on stopping us,\nshow me you can.$"

@ C4.08 | trainer defeated text only
NeoMilestone_Text_RillDefeat::
	.string "RILL: So you can hold your\nground.$"

@ C4.08 | victory only; withdraw via validated route
@ WRITER ONLY: Rill points to Stern's logs, not a confirmed attack or future cargo event.
@ Hiker independently corroborates existence of ship logs. Stern checks timing.
@ Neither the admin nor public evidence identifies Null. Do not expose secret loyalties.
NeoMilestone_Text_RillWithdrawal::
	.string "RILL: Fine. Keep the records.\p"
	.string "You won here, RANGER. But the\ntide won't wait for you.\p"
	.string "Ask STERN about the readings\nfrom SLATEPORT's ships.\p"
	.string "You're not the only one\nfollowing this trail.$"

@ C4.08 | pre-rescue contact; no battle
NeoMilestone_Text_RillWait::
	.string "The passage is unsafe. Account\nfor the residents first.$"

@ C4.08 | inspect recovered data after Rill
NeoMilestone_Text_CaveRecordDiscrepancy::
	.string "A sealed copy of the reading is\nstill in the relay.\p"
	.string "Its access format resembles the\nthird signal at RUSTURF.\p"
	.string "The origin is still unknown. You\nsave the discrepancy.$"

@ C4.08 | recovery hint after blackout; no completion
NeoMilestone_Text_CaveAfterLoss::
	.string "WARDEN: You're back. Take your\ntime.\p"
	.string "The residents are safe. The\nsurvey station still needs you.$"

@ C4.09 | all three and faction resolved, readings copied
NeoMilestone_Text_CaveCrewReport::
	.string "HIKER: Three names, three people\nsafe. Good work.\p"
	.string "That AQUA officer mentioned\nSTERN. He does keep ship logs.\p"
	.string "Take our report to SLATEPORT.\nLet STERN check their timing.$"

@ C4.09 | return visits
NeoMilestone_Text_CaveCompleteRepeat::
	.string "HIKER: The shelter is stable for\nnow.\p"
	.string "BRINEY is at the dock. STERN\nneeds that report.$"

@ C5.01 | north exit pre-dispatch
NeoMilestone_Text_SlateportMarshalBefore::
	.string "RANGER: Check in at STERN's\nshipyard first.\p"
	.string "We need the commander's\nclearance before the inland\p"
	.string "trip.$"

@ C5.01 | authorized route, no cargo quest
NeoMilestone_Text_SlateportMarshalAfter::
	.string "RANGER: Your orders are logged.\p"
	.string "Follow ROUTE 110 north to\nMAUVILLE.\p"
	.string "The transit officer will direct\nyou to CAYTON's survey post.$"

@ C5.02 | existing transit contact, after dispatch
NeoMilestone_Text_MauvilleTransit::
	.string "Welcome to MAUVILLE, RANGER.\p"
	.string "CAYTON has marked a safe\napproach into the desert.\p"
	.string "Restock here. The medical team\nis ready if you need it.\p"
	.string "Head north onto ROUTE 111 and\nspeak to the survey officer.$"

@ C5.02 | early arrival, recovery
NeoMilestone_Text_MauvilleBeforeOrders::
	.string "Our northbound relief crew is\nawaiting orders.\p"
	.string "Check with HALE at the SLATEPORT\nshipyard.$"

@ C5.02 | optional worldbuilding
NeoMilestone_Text_MauvilleResident::
	.string "We used to worry about the power\ngoing out.\p"
	.string "Now the grid keeps shelters and\nresearch stations running.\p"
	.string "WATTSON says every connection\nmatters.$"

@ C5.02 | no fifth-badge/grid mission unlock
NeoMilestone_Text_MauvilleEngineer::
	.string "We're logging tremors across the\ngrid.\p"
	.string "CAYTON's crews are working north\nof here.\p"
	.string "Our own inspection can wait\nuntil you're ready.$"

@ C5.03 | no dispatch; block access, retain return path
NeoMilestone_Text_DesertCheckpointBefore::
	.string "SURVEY OFFICER: The desert is\nunstable.\p"
	.string "Only authorized relief crews may\nuse this approach.\p"
	.string "Speak to HALE in SLATEPORT for\nyour assignment.$"

@ C5.03 | validated temporary access after dispatch
NeoMilestone_Text_DesertCheckpointPermit::
	.string "SURVEY OFFICER: Your orders\ncheck out.\p"
	.string "The marked approach is safe for\nnow.\p"
	.string "Stay on the marked route.\nRELICREST lies ahead.\p"
	.string "The survey office is your first\nstop.$"

@ C5.03 | authorized revisit
NeoMilestone_Text_DesertCheckpointRepeat::
	.string "The approach is still open,\nRANGER.\p"
	.string "Follow the markers to RELICREST.$"

@ C5.04 | town arrival or reception guide
NeoMilestone_Text_RelicrestArrival::
	.string "Welcome to RELICREST, RANGER.\p"
	.string "The excavation has been closed\nsince the last tremor.\p"
	.string "PROF. CAYTON is waiting at the\nsurvey office.$"

@ C5.04 | first survey-office conversation
NeoMilestone_Text_CaytonWelcome::
	.string "CAYTON: HALE said you were\ncoming.\p"
	.string "We've restored fossils here for\nyears. I've never seen the\p"
	.string "ground shift like this.\p"
	.string "A chamber collapsed. Some of my\nsurvey crew are still inside.\p"
	.string "Check the surface gauge at the\nexcavation gate. Then find my\p"
	.string "team.$"

@ C5.04 | repeat until surface gauge checked
NeoMilestone_Text_CaytonBeforeGauge::
	.string "CAYTON: Start with the surface\ngauge at the excavation gate.\p"
	.string "We need a safe route before you\ngo below.$"

@ C5.05 | gauge checked; rescue incomplete
NeoMilestone_Text_CaytonCrewPending::
	.string "CAYTON: The gauge is logged.\nGood.\p"
	.string "Find the survey crew in the\nexcavation. Their safety comes\p"
	.string "first.$"

@ C5.05 | interact and record reading
NeoMilestone_Text_SurfaceGauge::
	.string "SURFACE GAUGE: A sharp pressure\nchange precedes the tremor.\p"
	.string "You save the reading and check\nthe marked safe route.$"

@ C5.05 | directs to valid rescue approach
NeoMilestone_Text_ExcavationMarshal::
	.string "The main support failed. The\nmarked passage is our way in.\p"
	.string "Keep clear of the scaffolding\nuntil the crew is out.$"

@ C5.05 | player completes actual route clearing
NeoMilestone_Text_ExcavationWorker::
	.string "WORKER: You opened the passage!\p"
	.string "I can make it to the surface\nnow. Thank you, RANGER.$"

@ C5.05 | second rescue or data contact, after path safe
NeoMilestone_Text_ExcavationSurveyor::
	.string "SURVEYOR: The lower gauge was\nstill recording when the chamber\p"
	.string "fell.\p"
	.string "I'll take the safe passage out.\nThe reading is stored at the\p"
	.string "terminal.$"

@ C5.05 | all required contacts accounted for
NeoMilestone_Text_ExcavationCrewSafe::
	.string "MARSHAL: Everyone is out. I'll\nseal the damaged passage.\p"
	.string "Check the deep survey terminal\nbefore you return.$"

@ C5.05 | inspect terminal after required rescue
NeoMilestone_Text_DeepReading::
	.string "DEEP SURVEY: The tremor matches\nthe surface gauge.\p"
	.string "You save a copy of the reading\nfor CAYTON.$"

@ C5.06 | after crew safe; stop unauthorized collection
NeoMilestone_Text_SableArrival::
	.string "SABLE: The land is changing\nfaster than anyone predicted.\p"
	.string "CAYTON has records that could\nhelp us understand it.\p"
	.string "Surely a RANGER understands that\nwaiting costs lives.$"

@ C5.06 | battle introduction
NeoMilestone_Text_SableChallenge::
	.string "SABLE: We're taking the survey\ndata.\p"
	.string "If you want to stand in our way,\nthen prove you can.$"

@ C5.06 | trainer defeated text only
NeoMilestone_Text_SableDefeat::
	.string "SABLE: That was... unexpected.$"

@ C5.06 | victory only; leave data, safe exit
@ WRITER ONLY: Sable hints at springs; Cayton independently confirms the report.
@ This is a clue, not a new emergency or premature unlock. Badge 2 precedes Route112.
@ Keep Vesta/Caspian's goal and embedded-admin loyalties out of public dialogue.
NeoMilestone_Text_SableWithdrawal::
	.string "SABLE: Fine. Keep the records.\p"
	.string "You think this is where our\nsearch ends?\p"
	.string "Ask the people at LAVARIDGE\nwhat happened to their springs.\p"
	.string "Perhaps then you'll understand\nwhy we're in such a hurry.$"

@ C5.06 | recovery hint at safe entrance
NeoMilestone_Text_SableAfterLoss::
	.string "MARSHAL: The workers are safe.\p"
	.string "NEO MAGMA is still near the\nsurvey equipment.\p"
	.string "Rest your team, then return when\nyou're ready.$"

@ C5.07 | surface/deep readings and encounter resolved
NeoMilestone_Text_CaytonLabReport::
	.string "CAYTON: These fossils survived\nmillions of years.\p"
	.string "The ground above them is\nchanging in months.\p"
	.string "Your DEWFORD and desert records\nagree on the timing.\p"
	.string "The shifts occur near rock\nbearing meteorite fragments.\p"
	.string "SABLE mentioned LAVARIDGE?\nTheir spring crew sent a report.\p"
	.string "A similar shift. We should\ncompare their actual readings.\p"
	.string "I'll send our results to HALE.\nYou've done good work.$"

@ C5.07 | after safety closure lifted
NeoMilestone_Text_CaytonGymOpen::
	.string "CAYTON: The GYM can reopen now\nthat the crew is safe.\p"
	.string "You've shown good judgment in\nthe field.\p"
	.string "Let's see how you think in\nbattle. Meet me at the fossil\p"
	.string "GYM.$"

@ C5.08 | pre-report/early challenge
NeoMilestone_Text_CaytonGymClosed::
	.string "GYM GUIDE: CAYTON is directing\nthe rescue.\p"
	.string "Help the survey crew first. The\nGYM can wait.$"

@ C5.08 | puzzle intro
NeoMilestone_Text_FossilGuide::
	.string "GYM GUIDE: Each station\nrepresents a layer of rock.\p"
	.string "Read the fossil labels and use\nthe marked lift controls.\p"
	.string "You can return to the entrance\nat any time.$"

@ C5.08 | accessible puzzle sign
NeoMilestone_Text_FossilLayerClue::
	.string "Sediment settles in layers.\p"
	.string "Compare the marked specimens\nbefore choosing the lift.$"

@ C5.08 | invalid switch, no trap
NeoMilestone_Text_FossilLiftLocked::
	.string "The lift is locked. Check the\nfossil station's labels.$"

@ C5.08 | valid switch after puzzle check
NeoMilestone_Text_FossilLiftReady::
	.string "The lift is ready. The return\nroute remains open.$"

@ C5.08 | after report + puzzle + badge absent
NeoMilestone_Text_CaytonChallenge::
	.string "CAYTON: Every fossil tells a\nstory of survival.\p"
	.string "Strength matters, but so does\nadapting to a changing world.\p"
	.string "Show me how you and your POKéMON\nadapt, RANGER.$"

@ C5.08 | trainer defeated text only
NeoMilestone_Text_CaytonDefeat::
	.string "CAYTON: Well fought! You found a\nway to adapt.$"

@ C5.08 | only after victory; badge award once
NeoMilestone_Text_CaytonBadge::
	.string "CAYTON: You have earned the\nRELIC BADGE.\p"
	.string "Take it as proof of what you've\nlearned here.$"

@ C5.08 | only after actual Ancient Power item success
NeoMilestone_Text_CaytonTM::
	.string "CAYTON: This TM contains ANCIENT\nPOWER.\p"
	.string "It may raise all five battle\nstats.\p"
	.string "Use it wisely. The past still\nhas lessons for us.$"

@ C5.08 | failed item insertion; preserve badge, retry TM
NeoMilestone_Text_CaytonTMBagFull::
	.string "CAYTON: Your BAG is full.\p"
	.string "Come back when you have room for\nyour TM.$"

@ C5.08 | after badge and reward
NeoMilestone_Text_CaytonRemind::
	.string "CAYTON: The spring records are\nour next clue.\p"
	.string "Speak to the liaison before\nleaving RELICREST.$"

@ C5.09 | no badge or report, no new route access
NeoMilestone_Text_RelicrestLiaisonBefore::
	.string "Your report and GYM\ncertification are still pending.\p"
	.string "Finish your assignment here\nbefore heading west.$"

@ C5.09 | report and badge; next stage not opened unless built
NeoMilestone_Text_RelicrestLiaisonAfter::
	.string "HALE received CAYTON's report.\nWell done.\p"
	.string "The next survey leads west by\nROUTE 112, toward LAVARIDGE.\p"
	.string "Meteorite records may also help\nus understand these tremors.\p"
	.string "Wait for the next route to be\ncleared.$"

@ C5 optional resident
NeoMilestone_Text_RelicrestMarket::
	.string "Our roofs keep the sun off the\nmarket.\p"
	.string "The old excavation brought\nresearchers. Now it brings\p"
	.string "visitors from all over.$"

@ C5 optional resident
NeoMilestone_Text_RelicrestLabVisitor::
	.string "A fossil isn't just a rare\nPOKéMON.\p"
	.string "It tells us which kinds of life\nsurvived when the world changed.$"

@ C5 optional resident
NeoMilestone_Text_RelicrestChild::
	.string "When I grow up, I want to find a\nfossil!\p"
	.string "CAYTON says the best discoveries\nbegin with a good question.$"

@ C5 optional after rescue
NeoMilestone_Text_RelicrestRecovery::
	.string "The crew came home. That's what\nmatters.\p"
	.string "We'll rebuild the supports\nbefore anyone goes below again.$"

@ C5 optional gym trainer intro
NeoMilestone_Text_RelicrestGymTrainer1::
	.string "A SHIELDON can stand its ground\nfor ages.\p"
	.string "Can your team keep up?$"

@ C5 optional gym trainer intro
NeoMilestone_Text_RelicrestGymTrainer2::
	.string "Fossil POKéMON aren't all alike.\p"
	.string "Watch how my team handles a new\nchallenge.$"

@ C5 optional gym trainer defeat
NeoMilestone_Text_RelicrestGymTrainerDefeat::
	.string "Looks like you learned something\nfrom that battle!$"

