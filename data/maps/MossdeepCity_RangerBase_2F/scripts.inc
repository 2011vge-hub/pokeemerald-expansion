@ Neo Emerald: Mossdeep Ranger Base command floor.
@ Ranger rank and promotion requirements: include/constants/neo_ranger.h

MossdeepCity_RangerBase_2F_MapScripts::
	.byte 0

MossdeepCity_RangerBase_2F_EventScript_Commander::
	lock
	faceplayer
	goto_if_eq VAR_NEO_FERRY_DISPATCH, 5, NeoHale_Depart
	goto_if_ge VAR_NEO_RANGER_RANK, RANGER_RANK_MAX, MossdeepCity_RangerBase_2F_EventScript_CommanderTopRank
	msgbox MossdeepCity_RangerBase_2F_Text_CommanderIntro, MSGBOX_DEFAULT
	call MossdeepCity_RangerBase_2F_EventScript_CountBadges
	switch VAR_NEO_RANGER_RANK
	case RANGER_RANK_ROOKIE, MossdeepCity_RangerBase_2F_EventScript_ReqRanger
	case RANGER_RANK_RANGER, MossdeepCity_RangerBase_2F_EventScript_ReqSenior
	case RANGER_RANK_SENIOR, MossdeepCity_RangerBase_2F_EventScript_ReqArea
	goto MossdeepCity_RangerBase_2F_EventScript_ReqTop

MossdeepCity_RangerBase_2F_EventScript_ReqRanger:
	setvar VAR_0x8005, RANGER_REQ_RANGER_MISSIONS
	setvar VAR_0x8006, RANGER_REQ_RANGER_XP
	setvar VAR_0x8007, RANGER_REQ_RANGER_BADGES
	goto MossdeepCity_RangerBase_2F_EventScript_EvaluatePromotion

MossdeepCity_RangerBase_2F_EventScript_ReqSenior:
	setvar VAR_0x8005, RANGER_REQ_SENIOR_MISSIONS
	setvar VAR_0x8006, RANGER_REQ_SENIOR_XP
	setvar VAR_0x8007, RANGER_REQ_SENIOR_BADGES
	goto MossdeepCity_RangerBase_2F_EventScript_EvaluatePromotion

MossdeepCity_RangerBase_2F_EventScript_ReqArea:
	setvar VAR_0x8005, RANGER_REQ_AREA_MISSIONS
	setvar VAR_0x8006, RANGER_REQ_AREA_XP
	setvar VAR_0x8007, RANGER_REQ_AREA_BADGES
	goto MossdeepCity_RangerBase_2F_EventScript_EvaluatePromotion

MossdeepCity_RangerBase_2F_EventScript_ReqTop:
	setvar VAR_0x8005, RANGER_REQ_TOP_MISSIONS
	setvar VAR_0x8006, RANGER_REQ_TOP_XP
	setvar VAR_0x8007, RANGER_REQ_TOP_BADGES
	goto MossdeepCity_RangerBase_2F_EventScript_EvaluatePromotion

MossdeepCity_RangerBase_2F_EventScript_EvaluatePromotion:
	goto_if_lt VAR_NEO_RANGER_MISSIONS, VAR_0x8005, MossdeepCity_RangerBase_2F_EventScript_NotYet
	goto_if_lt VAR_NEO_RANGER_XP, VAR_0x8006, MossdeepCity_RangerBase_2F_EventScript_NotYet
	goto_if_lt VAR_0x8004, VAR_0x8007, MossdeepCity_RangerBase_2F_EventScript_NotYet
	addvar VAR_NEO_RANGER_RANK, 1
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	switch VAR_NEO_RANGER_RANK
	case RANGER_RANK_RANGER, MossdeepCity_RangerBase_2F_EventScript_PromotedRanger
	case RANGER_RANK_SENIOR, MossdeepCity_RangerBase_2F_EventScript_PromotedSenior
	case RANGER_RANK_AREA, MossdeepCity_RangerBase_2F_EventScript_PromotedArea
	msgbox MossdeepCity_RangerBase_2F_Text_PromotedTop, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_PromotedRanger:
	msgbox MossdeepCity_RangerBase_2F_Text_PromotedRanger, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_PromotedSenior:
	msgbox MossdeepCity_RangerBase_2F_Text_PromotedSenior, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_PromotedArea:
	msgbox MossdeepCity_RangerBase_2F_Text_PromotedArea, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_NotYet:
	buffernumberstring STR_VAR_1, VAR_0x8005
	buffernumberstring STR_VAR_2, VAR_0x8006
	buffernumberstring STR_VAR_3, VAR_0x8007
	msgbox MossdeepCity_RangerBase_2F_Text_NextRankNeeds, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_NEO_RANGER_MISSIONS
	buffernumberstring STR_VAR_2, VAR_NEO_RANGER_XP
	buffernumberstring STR_VAR_3, VAR_0x8004
	msgbox MossdeepCity_RangerBase_2F_Text_YouHave, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_CommanderTopRank:
	msgbox MossdeepCity_RangerBase_2F_Text_CommanderTopRank, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_CountBadges:
	setvar VAR_0x8004, 0
	call_if_set FLAG_BADGE01_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE02_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE03_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE04_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE05_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE06_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE07_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	call_if_set FLAG_BADGE08_GET, MossdeepCity_RangerBase_2F_EventScript_AddBadge
	return

MossdeepCity_RangerBase_2F_EventScript_AddBadge:
	addvar VAR_0x8004, 1
	return

MossdeepCity_RangerBase_2F_Text_CommanderIntro:
	.string "CMDR. HALE: Rank in this service is\n"
	.string "earned three ways.\p"
	.string "Missions completed. Experience in\n"
	.string "the field. And GYM BADGES, because\l"
	.string "a Ranger must handle strong POKéMON.$"

MossdeepCity_RangerBase_2F_Text_NextRankNeeds:
	.string "Next rank needs {STR_VAR_1} missions,\n"
	.string "{STR_VAR_2} XP and {STR_VAR_3} BADGES.$"

MossdeepCity_RangerBase_2F_Text_YouHave:
	.string "Your record: {STR_VAR_1} missions,\n"
	.string "{STR_VAR_2} XP, {STR_VAR_3} BADGES.\p"
	.string "Now get back out there. Mossdeep\n"
	.string "needs every Ranger tonight.$"

MossdeepCity_RangerBase_2F_Text_PromotedRanger:
	.string "CMDR. HALE: Rookie no longer.\n"
	.string "You're a full RANGER now.$"

MossdeepCity_RangerBase_2F_Text_PromotedSenior:
	.string "CMDR. HALE: Promoted to SENIOR\n"
	.string "RANGER. Equipment upgrades are\l"
	.string "open to you. See TECH REMY.$"

MossdeepCity_RangerBase_2F_Text_PromotedArea:
	.string "CMDR. HALE: AREA RANGER. Hoenn's\n"
	.string "coast is yours to protect now.$"

MossdeepCity_RangerBase_2F_Text_PromotedTop:
	.string "CMDR. HALE: TOP RANGER.\n"
	.string "The highest rank I can give.$"

MossdeepCity_RangerBase_2F_Text_CommanderTopRank:
	.string "CMDR. HALE: TOP RANGER. There's\n"
	.string "nothing left for me to teach you.$"

MossdeepCity_RangerBase_2F_EventScript_Technician::
	lock
	faceplayer
	goto_if_ge VAR_NEO_RANGER_RANK, RANGER_RANK_SENIOR, MossdeepCity_RangerBase_2F_EventScript_TechnicianCleared
	msgbox MossdeepCity_RangerBase_2F_Text_Technician, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_EventScript_TechnicianCleared:
	msgbox MossdeepCity_RangerBase_2F_Text_TechnicianCleared, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_2F_Text_Technician:
	.string "TECH REMY: Saltwater eats our gear\n"
	.string "alive. Bring me anything that\l"
	.string "sparks and I'll patch it.\p"
	.string "Reel, tether, transmitter upgrades?\n"
	.string "COMMAND clears those at SENIOR rank.$"

MossdeepCity_RangerBase_2F_Text_TechnicianCleared:
	.string "TECH REMY: SENIOR clearance, nice.\p"
	.string "The upgrade parts are still on the\n"
	.string "mainland. Once the ferries run,\l"
	.string "I'll fit them myself.$"

MossdeepCity_RangerBase_2F_EventScript_StormMonitor::
	msgbox MossdeepCity_RangerBase_2F_Text_StormMonitor, MSGBOX_SIGN
	end

MossdeepCity_RangerBase_2F_EventScript_Comms::
	msgbox MossdeepCity_RangerBase_2F_Text_Comms, MSGBOX_SIGN
	end

MossdeepCity_RangerBase_2F_Text_StormMonitor:
	.string "REGIONAL STORM MONITOR\p"
	.string "Pressure falling. Surge at MOSSDEEP\n"
	.string "is climbing past the seawall.\p"
	.string "ALERT LOG: surge detected 03:12.\n"
	.string "Public siren: PENDING.$"

MossdeepCity_RangerBase_2F_Text_Comms:
	.string "COMMS DESK\p"
	.string "Relay open: SOOTOPOLIS, LILYCOVE,\n"
	.string "EVER GRANDE.\p"
	.string "SLATEPORT band: static only.$"

NeoHale_Depart:
	msgbox NeoHale_Debrief, MSGBOX_DEFAULT
	msgbox NeoHale_Call, MSGBOX_DEFAULT
	goto_if_ne VAR_NEO_ASSIGNMENT, 0, NeoHale_Flight
	setvar VAR_NEO_ASSIGNMENT, 1
NeoHale_Flight:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	closemessage
	warp MAP_RUSTBORO_CITY_FLAT1_1F, 6, 6
	waitstate
	release
	end
NeoHale_Debrief:
	.string "HALE: Both passengers are safe.\p"
	.string "The siren log says the alarm rang\n"
	.string "after the stairs gave way. Why?$"
NeoHale_Call:
	.string "RADIO: Emergency landing! We are\n"
	.string "off Briney's cottage on Route 104!\p"
	.string "HALE: My aircraft is ready. Meet\n"
	.string "my kid at the Rustboro field office.$"
