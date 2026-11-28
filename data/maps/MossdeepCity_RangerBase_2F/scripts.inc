@ Neo Emerald: Mossdeep Ranger Base command floor.
@ Ranger rank and promotion requirements: include/constants/neo_ranger.h

MossdeepCity_RangerBase_2F_MapScripts::
	.byte 0

MossdeepCity_RangerBase_2F_EventScript_Commander::
	lock
	faceplayer
	@ Complete the rescue before receiving orders to leave Mossdeep.
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_RangerBase_2F_EventScript_Chapter1Debrief
MossdeepCity_RangerBase_2F_EventScript_RankCheck:
	goto_if_ge VAR_NEO_RANGER_RANK, RANGER_RANK_MAX, MossdeepCity_RangerBase_2F_EventScript_CommanderTopRank
	msgbox MossdeepCity_RangerBase_2F_Text_CommanderIntro, MSGBOX_DEFAULT
	call MossdeepCity_RangerBase_2F_EventScript_CountBadges
	switch VAR_NEO_RANGER_RANK
	case RANGER_RANK_ROOKIE, MossdeepCity_RangerBase_2F_EventScript_ReqRanger
	case RANGER_RANK_RANGER, MossdeepCity_RangerBase_2F_EventScript_ReqSenior
	case RANGER_RANK_SENIOR, MossdeepCity_RangerBase_2F_EventScript_ReqArea
	goto MossdeepCity_RangerBase_2F_EventScript_ReqTop

@ Chapter 1 bridge: players return to Hale after the once-only evacuation
@ credit. A save-persistent flag prevents replaying the debrief/flight.
@ The full upstairs evacuation staging and air-transport visuals are still TODO.
MossdeepCity_RangerBase_2F_EventScript_Chapter1Debrief:
	goto_if_set FLAG_NEO_C1_FLIGHT_RUSTBORO, MossdeepCity_RangerBase_2F_EventScript_RankCheck
	msgbox MossdeepCity_RangerBase_2F_Text_Chapter1RescueDebrief, MSGBOX_DEFAULT
	msgbox MossdeepCity_RangerBase_2F_Text_Chapter1LateSiren, MSGBOX_DEFAULT
	playse SE_PIN
	msgbox MossdeepCity_RangerBase_2F_Text_Chapter1EmergencyCall, MSGBOX_DEFAULT
	msgbox MossdeepCity_RangerBase_2F_Text_Chapter1FlightOrders, MSGBOX_DEFAULT
	closemessage
	@ Rustboro becomes the respawn destination before risking a Gym whiteout.
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	@ Simple fade and travel audio are provisional until Hale's flight animation exists.
	playse SE_WARP_OUT
	fadescreen FADE_TO_BLACK
	@ Commit the transfer before warping so revisiting Hale never repeats it.
	setflag FLAG_NEO_C1_FLIGHT_RUSTBORO
	warp MAP_RUSTBORO_CITY, 27, 35
	waitstate
	end

MossdeepCity_RangerBase_2F_Text_Chapter1RescueDebrief:
	.string "HALE: You found the missing child\n"
	.string "and brought his POOCHYENA back.\p"
	.string "Against that flood, you kept\n"
	.string "your head. Well done, Ranger.\p"
	.string "Our duty isn't winning battles.\n"
	.string "It's bringing everyone home.$"

MossdeepCity_RangerBase_2F_Text_Chapter1LateSiren:
	.string "One thing bothers me. The public\n"
	.string "siren sounded far too late.\p"
	.string "Keep that in your report.\n"
	.string "We will investigate.$"

MossdeepCity_RangerBase_2F_Text_Chapter1EmergencyCall:
	.string "BEEP! INCOMING EMERGENCY CALL!\p"
	.string "HALE: The evacuation vessel made\n"
	.string "an emergency landing? Route 104?\p"
	.string "Near MR. BRINEY's old cottage...\n"
	.string "Understood.$"

MossdeepCity_RangerBase_2F_Text_Chapter1FlightOrders:
	.string "HALE: I'll fly you to RUSTBORO.\n"
	.string "My field contact will meet you.\p"
	.string "Your first rescue is over, Ranger.\n"
	.string "The next assignment starts now.\p"
	.string "Hale's aircraft lifts into\n"
	.string "the clouds above MOSSDEEP...$"

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
