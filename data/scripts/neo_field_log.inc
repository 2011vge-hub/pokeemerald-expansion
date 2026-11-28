NeoRanger_FieldLog::
	lockall
	goto_if_set FLAG_NEO_C4_REPORTED, NeoLog_Filed
	goto_if_set FLAG_NEO_C4_SURVEY, NeoLog_ReturnReport
	goto_if_set FLAG_NEO_C4_BRIEF, NeoLog_RefugeTravel
	goto_if_eq VAR_NEO_CH3_STEP, 9, NeoLog_Dewford
	goto_if_eq VAR_NEO_CH3_STEP, 8, NeoLog_RelayReport
	goto_if_eq VAR_NEO_CH3_STEP, 12, NeoLog_Copy
	goto_if_eq VAR_NEO_CH3_STEP, 11, NeoLog_Guard
	goto_if_eq VAR_NEO_CH3_STEP, 7, NeoLog_Crew
	goto_if_eq VAR_NEO_CH3_STEP, 6, NeoLog_Cutter
	goto_if_set FLAG_NEO_C2_DEBRIEF_DONE, NeoLog_Badge
	goto_if_set FLAG_NEO_C2_BRINEY_REPORTED, NeoLog_Liaison
	goto_if_set FLAG_NEO_C2_AQUA_DONE, NeoLog_Briney
	goto_if_set FLAG_NEO_C2_CUTTER_DEMO, NeoLog_Cargo
	goto_if_set FLAG_NEO_C2_MAGMA_DONE, NeoLog_Demo
	goto_if_set FLAG_NEO_C2_RIVAL_MET, NeoLog_Woods
	goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, NeoLog_Rival
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, NeoLog_Hale
	goto_if_eq VAR_NEO_FERRY_DISPATCH, 4, NeoLog_Dock
	goto_if_eq VAR_NEO_FERRY_DISPATCH, 3, NeoLog_Rescue
	goto_if_eq VAR_NEO_FERRY_DISPATCH, 2, NeoLog_Sailor
	msgbox NeoLog_OrientationText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Filed:
	msgbox NeoLog_FiledText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_ReturnReport:
	goto_if_eq VAR_BOARD_BRINEY_BOAT_STATE, 2, NeoLog_HaleReport
NeoLog_SailHome:
	msgbox NeoLog_SailHomeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_HaleReport:
	msgbox NeoLog_HaleReportText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_RefugeTravel:
	goto_if_eq VAR_BOARD_BRINEY_BOAT_STATE, 2, NeoLog_Dewford
NeoLog_RefugeProgress:
	goto_if_set FLAG_NEO_C4_CREW_CHECKED, NeoLog_CrewChecked
	goto_if_set FLAG_NEO_C4_READING_CHECKED, NeoLog_Bunks
	msgbox NeoLog_RefugeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_CrewChecked:
	goto_if_set FLAG_NEO_C4_READING_CHECKED, NeoLog_CaveReport
	msgbox NeoLog_GaugeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Bunks:
	msgbox NeoLog_BunksText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_CaveReport:
	msgbox NeoLog_CaveReportText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Dewford:
	goto_if_eq VAR_BOARD_BRINEY_BOAT_STATE, 2, NeoLog_DewfordPassage
	goto_if_set FLAG_VISITED_DEWFORD_TOWN, NeoLog_DewfordBrief
NeoLog_DewfordPassage:
	msgbox NeoLog_DewfordText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_DewfordBrief:
	msgbox NeoLog_DewfordBriefText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_RelayReport:
	msgbox NeoLog_RelayReportText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Copy:
	msgbox NeoLog_CopyText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Guard:
	msgbox NeoLog_GuardText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Crew:
	msgbox NeoLog_CrewText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Cutter:
	msgbox NeoLog_CutterText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Badge:
	goto_if_set FLAG_BADGE01_GET, NeoLog_Certification
	msgbox NeoLog_BadgeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Certification:
	msgbox NeoLog_CertificationText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Liaison:
	msgbox NeoLog_LiaisonText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Briney:
	msgbox NeoLog_BrineyText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Cargo:
	msgbox NeoLog_CargoText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Demo:
	msgbox NeoLog_DemoText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Woods:
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, NeoLog_WoodsReady
	msgbox NeoLog_SparText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_WoodsReady:
	msgbox NeoLog_WoodsText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Rival:
	msgbox NeoLog_RivalText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Hale:
	msgbox NeoLog_HaleText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Dock:
	msgbox NeoLog_DockText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Rescue:
	msgbox NeoLog_RescueText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Sailor:
	msgbox NeoLog_SailorText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Close:
	releaseall
	end
NeoLog_FiledText:
	.string "Dewford survey filed with Hale.\nNo further field orders issued.$"
NeoLog_SailHomeText:
	.string "Take Briney back to Route 104.\nReport to Hale in west Rustboro.$"
NeoLog_HaleReportText:
	.string "Report the DEWFORD survey to\n"
	.string "HALE in west RUSTBORO.$"
NeoLog_RefugeText:
	.string "Route 106: enter GRANITE CAVE.\p"
	.string "Take the ladder by the crates.\n"
	.string "Check the bunk warden, then\l"
	.string "the gauge keeper to the east.$"
NeoLog_BunksText:
	.string "Gauge readings copied.\p"
	.string "Return to the refuge bunks.\n"
	.string "Check the bunk warden.$"
NeoLog_GaugeText:
	.string "Refuge crew accounted for.\p"
	.string "Head east from the bunks.\n"
	.string "Speak to the gauge keeper.$"
NeoLog_CaveReportText:
	.string "Both checks are complete.\p"
	.string "Return up the refuge ladder.\n"
	.string "Report to the Hiker near the\l"
	.string "cave entrance.$"
NeoLog_DewfordText:
	.string "Ask Briney at his Route 104\ncottage for passage to Dewford.\lFind BRAWLY at or in the GYM.$"
NeoLog_DewfordBriefText:
	.string "DEWFORD: Find BRAWLY at or in\n"
	.string "the GYM for your cave briefing.$"
NeoLog_RelayReportText:
	.string "Take the relay copy to Hale.\nHis office is in west Rustboro.$"
NeoLog_CopyText:
	.string "Rusturf Tunnel: copy the log\nfrom the relay near the guard.$"
NeoLog_GuardText:
	.string "The technicians are safe.\nConfront the Rusturf relay guard.$"
NeoLog_CrewText:
	.string "Enter Rusturf from Route 116.\nFind the stranded technicians.$"
NeoLog_CutterText:
	.string "Route 116, east of Rustboro.\nUse your Cutter near the berries.$"
NeoLog_BadgeText:
	.string "Earn Roxanne's Stone Badge.\nSee Hale in the west field office\lfor your Cutter certification.$"
NeoLog_CertificationText:
	.string "STONE BADGE earned!\p"
	.string "See HALE in the west RUSTBORO\n"
	.string "field office for your CUTTER.$"
NeoLog_LiaisonText:
	.string "Return to RUSTBORO UNIVERSITY.\p"
	.string "Find the field student outside\n"
	.string "the university entrance. Give\l"
	.string "BRINEY's manifest number.$"
NeoLog_BrineyText:
	.string "The cargo is safe. Find Briney\nin his cottage on Route 104.$"
NeoLog_CargoText:
	.string "Follow Route 104 south.\nCheck on the relief crew and\ltheir cargo near the cottage.$"
NeoLog_DemoText:
	.string "Find your partner by the fallen\ntrees in Petalburg Woods.$"
NeoLog_SparText:
	.string "Meet your partner on ROUTE 104\n"
	.string "outside the WOODS for a spar.$"
NeoLog_WoodsText:
	.string "Follow Route 104 into the Woods.\nFind the Devon researcher and\lspeak to the Neo Magma grunt.$"
NeoLog_RivalText:
	.string "Meet your Ranger contact by\nthe Rustboro University steps.$"
NeoLog_HaleText:
	.string "All passengers accounted for.\nReport to Hale at waterfront HQ.$"
NeoLog_DockText:
	.string "Take the child and Poochyena\nto the waterfront ferry crew.$"
NeoLog_RescueText:
	.string "A child is missing. Search near\nthe Mart and the lower stairs.$"
NeoLog_SailorText:
	.string "Check in with the ferry crew\nat the waterfront Ranger HQ.$"
NeoLog_OrientationText:
	.string "Meet the dispatch team and\nchoose your Ranger partner.$"
