NeoRanger_FieldLog::
	lockall
	goto_if_set FLAG_NEO_C4_REPORTED, NeoLog_Filed
	goto_if_set FLAG_NEO_C4_SURVEY, NeoLog_SailHome
	goto_if_set FLAG_NEO_C4_BRIEF, NeoLog_Refuge
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
NeoLog_SailHome:
	msgbox NeoLog_SailHomeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Refuge:
	msgbox NeoLog_RefugeText, MSGBOX_DEFAULT
	goto NeoLog_Close
NeoLog_Dewford:
	msgbox NeoLog_DewfordText, MSGBOX_DEFAULT
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
	msgbox NeoLog_BadgeText, MSGBOX_DEFAULT
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
NeoLog_RefugeText:
	.string "Granite Cave, north of Dewford.\nCheck the refuge crew and gauge.\lBring both readings to the Hiker.$"
NeoLog_DewfordText:
	.string "Ask Briney at his Route 104\ncottage for passage to Dewford.\lFind Brawly outside the Gym.$"
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
NeoLog_LiaisonText:
	.string "Return to Rustboro University.\nGive the campus field student\lBriney's manifest number.$"
NeoLog_BrineyText:
	.string "The cargo is safe. Find Briney\nin his cottage on Route 104.$"
NeoLog_CargoText:
	.string "Follow Route 104 south.\nCheck on the relief crew and\ltheir cargo near the cottage.$"
NeoLog_DemoText:
	.string "Find your partner by the fallen\ntrees in Petalburg Woods.$"
NeoLog_WoodsText:
	.string "Follow Route 104 into the Woods.\nFind the Devon researcher and\lspeak to the Neo Magma grunt.$"
NeoLog_RivalText:
	.string "Meet your Ranger contact by\nthe Rustboro University steps.$"
NeoLog_HaleText:
	.string "All passengers accounted for.\nReport to Hale upstairs at HQ.$"
NeoLog_DockText:
	.string "Take the child and Poochyena\nto the waterfront ferry crew.$"
NeoLog_RescueText:
	.string "A child is missing. Search near\nthe Mart and the lower stairs.$"
NeoLog_SailorText:
	.string "Mossdeep: check in with the\nsailor for the evacuation count.$"
NeoLog_OrientationText:
	.string "Meet the dispatch team and\nchoose your Ranger partner.$"
