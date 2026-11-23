@ Neo Emerald: Mossdeep Ranger Base, ground floor.
@ Reception (Rookie Ari), dispatch operations (Dispatcher June), mission board,
@ healing station (Medic Tala), supplies and equipment storage (Quartermaster Brant).
@ Dialogue follows VAR_NEO_FERRY_DISPATCH: 2 = partner chosen, 3 = checked in.

MossdeepCity_RangerBase_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_RangerBase_1F_OnFrame
	.byte 0

@ The first scripted event starts at the reception mat on a NEW GAME only.
@ Dispatch state 1 is initialized by src/new_game.c. Set state 2 before
@ opening the existing starter selection, so map reloads never repeat it.
MossdeepCity_RangerBase_1F_OnFrame:
	map_script_2 VAR_NEO_FERRY_DISPATCH, 1, MossdeepCity_RangerBase_1F_EventScript_NewRecruit
	.2byte 0

MossdeepCity_RangerBase_1F_EventScript_NewRecruit:
	lockall
	msgbox MossdeepCity_RangerBase_1F_Text_AriGreeting, MSGBOX_DEFAULT
	msgbox MossdeepCity_RangerBase_1F_Text_JuneAssignment, MSGBOX_DEFAULT
	setvar VAR_NEO_FERRY_DISPATCH, 2
	setflag FLAG_SYS_POKEMON_GET
	special ChooseStarter
	msgbox MossdeepCity_RangerBase_1F_Text_PartnerRegistered, MSGBOX_DEFAULT
	msgbox MossdeepCity_RangerBase_1F_Text_StormEmergency, MSGBOX_DEFAULT
	msgbox MossdeepCity_RangerBase_1F_Text_AriFarewell, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_RangerBase_1F_Text_AriGreeting:
	.string "ROOKIE ARI: You're the new recruit!\p"
	.string "Welcome to MOSSDEEP RANGER BASE.\n"
	.string "I'm ARI. Reception duty, for now.\p"
	.string "DISPATCHER JUNE is waiting for you.$"

MossdeepCity_RangerBase_1F_Text_JuneAssignment:
	.string "JUNE: Welcome aboard, {PLAYER}.\p"
	.string "Your field registration is still\n"
	.string "missing one important thing.\p"
	.string "No RANGER operates alone.\n"
	.string "Choose your POKéMON partner.$"

MossdeepCity_RangerBase_1F_Text_PartnerRegistered:
	.string "JUNE: Partner officially registered.\p"
	.string "That POKéMON is yours to train.\n"
	.string "Keep each other safe out there.$"

MossdeepCity_RangerBase_1F_Text_StormEmergency:
	.string "BEEP! BEEP! BEEP!\p"
	.string "HALE: ALL RANGERS, REPORT IN!\p"
	.string "Floodwaters have reached the\n"
	.string "lower streets of MOSSDEEP!\p"
	.string "JUNE: The ferry by the GYM needs\n"
	.string "a passenger head count. Go now!\p"
	.string "MEDIC and QUARTERMASTER are here\n"
	.string "if you need supplies first.$"

MossdeepCity_RangerBase_1F_Text_AriFarewell:
	.string "ARI: First day and already on call?\p"
	.string "Those people need a RANGER.\n"
	.string "Go show them one!$"

MossdeepCity_RangerBase_1F_EventScript_Dispatch::
	lock
	faceplayer
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_RangerBase_1F_EventScript_DispatchDone
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerBase_1F_EventScript_DispatchSearch
	msgbox MossdeepCity_RangerBase_1F_Text_DispatchCheckIn, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_DispatchSearch:
	msgbox MossdeepCity_RangerBase_1F_Text_DispatchSearch, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_DispatchDone:
	msgbox MossdeepCity_RangerBase_1F_Text_DispatchDone, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_Text_DispatchDone:
	.string "DISPATCHER JUNE: Evacuation logged.\n"
	.string "Your first mission is on record.\p"
	.string "CMDR. HALE is upstairs. He'll want\n"
	.string "to see it.$"

MossdeepCity_RangerBase_1F_Text_DispatchCheckIn:
	.string "DISPATCHER JUNE: Rookie, you're on\n"
	.string "the evacuation detail.\p"
	.string "The ferry is loading now. Report\n"
	.string "to the sailor by the GYM for the\l"
	.string "passenger head count.\p"
	.string "Don't stay inside long. The surge\n"
	.string "won't wait for us.$"

MossdeepCity_RangerBase_1F_Text_DispatchSearch:
	.string "DISPATCHER JUNE: Two passengers\n"
	.string "unaccounted for: a boy and his\l"
	.string "POOCHYENA.\p"
	.string "Last seen near the MART. The stairs\n"
	.string "south of it are failing.\p"
	.string "If they go, take the new walkway\n"
	.string "from the east terrace. Go!$"

MossdeepCity_RangerBase_1F_EventScript_Rookie::
	lock
	faceplayer
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_RangerBase_1F_EventScript_RookieDone
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerBase_1F_EventScript_RookieSearch
	msgbox MossdeepCity_RangerBase_1F_Text_RookieWelcome, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_RookieSearch:
	msgbox MossdeepCity_RangerBase_1F_Text_RookieSearch, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_RookieDone:
	msgbox MossdeepCity_RangerBase_1F_Text_RookieDone, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_Text_RookieDone:
	.string "ROOKIE ARI: You got the kid AND his\n"
	.string "POOCHYENA aboard? On day one?\p"
	.string "Okay. I'm officially jealous.$"

MossdeepCity_RangerBase_1F_Text_RookieWelcome:
	.string "ROOKIE ARI: Welcome to MOSSDEEP\n"
	.string "RANGER BASE! You're the new one?\p"
	.string "Me too. I'm stuck on the front desk\n"
	.string "until my gear is certified.\p"
	.string "Third once-a-century storm this\n"
	.string "decade. Funny how that works, huh?$"

MossdeepCity_RangerBase_1F_Text_RookieSearch:
	.string "ROOKIE ARI: A kid's still out there?\p"
	.string "I wish I could come with you. Once\n"
	.string "I'm cleared for the field, call me\l"
	.string "for backup. I mean it!$"

MossdeepCity_RangerBase_1F_EventScript_Medic::
	lock
	faceplayer
	msgbox MossdeepCity_RangerBase_1F_Text_MedicIntro, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox MossdeepCity_RangerBase_1F_Text_MedicDone, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_Text_MedicIntro:
	.string "MEDIC TALA: Every Ranger leaves this\n"
	.string "station fit for duty.\p"
	.string "Let me check your partner.$"

MossdeepCity_RangerBase_1F_Text_MedicDone:
	.string "MEDIC TALA: All patched up.\p"
	.string "Bring anyone you rescue straight\n"
	.string "here. We're triage until the\l"
	.string "POKéMON CENTER floods.$"

MossdeepCity_RangerBase_1F_EventScript_Quartermaster::
	lock
	faceplayer
	goto_if_set FLAG_NEO_RANGER_KIT_ISSUED, MossdeepCity_RangerBase_1F_EventScript_QuartermasterIssued
	msgbox MossdeepCity_RangerBase_1F_Text_QuartermasterKit, MSGBOX_DEFAULT
	giveitem ITEM_POTION, 3
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_RangerBase_1F_EventScript_QuartermasterBagFull
	setflag FLAG_NEO_RANGER_KIT_ISSUED
	msgbox MossdeepCity_RangerBase_1F_Text_QuartermasterUpgrades, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_QuartermasterIssued:
	msgbox MossdeepCity_RangerBase_1F_Text_QuartermasterUpgrades, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_EventScript_QuartermasterBagFull:
	msgbox MossdeepCity_RangerBase_1F_Text_QuartermasterBagFull, MSGBOX_DEFAULT
	release
	end

MossdeepCity_RangerBase_1F_Text_QuartermasterKit:
	.string "QUARTERMASTER BRANT: Rookie field\n"
	.string "kit. Sign here. And here.\p"
	.string "It's not much, but it'll keep your\n"
	.string "partner on its feet.$"

MossdeepCity_RangerBase_1F_Text_QuartermasterUpgrades:
	.string "QUARTERMASTER BRANT: Better gear is\n"
	.string "issued by rank.\p"
	.string "Earn it with CMDR. HALE upstairs,\n"
	.string "and TECH REMY will fit it.$"

MossdeepCity_RangerBase_1F_Text_QuartermasterBagFull:
	.string "QUARTERMASTER BRANT: Your pack's\n"
	.string "full. Make room and come back.$"

MossdeepCity_RangerBase_1F_EventScript_MissionBoard::
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_RangerBase_1F_EventScript_MissionBoardDone
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 3, MossdeepCity_RangerBase_1F_EventScript_MissionBoardSearch
	msgbox MossdeepCity_RangerBase_1F_Text_MissionBoardCheckIn, MSGBOX_SIGN
	end

MossdeepCity_RangerBase_1F_EventScript_MissionBoardSearch:
	msgbox MossdeepCity_RangerBase_1F_Text_MissionBoardSearch, MSGBOX_SIGN
	end

MossdeepCity_RangerBase_1F_EventScript_MissionBoardDone:
	msgbox MossdeepCity_RangerBase_1F_Text_MissionBoardDone, MSGBOX_SIGN
	end

MossdeepCity_RangerBase_1F_Text_MissionBoardDone:
	.string "MISSION BOARD\n"
	.string "MOSSDEEP EVACUATION - COMPLETE\p"
	.string "All passengers aboard.\n"
	.string "Next assignment: pending.$"

MossdeepCity_RangerBase_1F_Text_MissionBoardCheckIn:
	.string "MISSION BOARD - URGENT\n"
	.string "MOSSDEEP EVACUATION\p"
	.string "1. Head count at the ferry.\n"
	.string "   Report to sailor by the GYM.\p"
	.string "2. Account for all passengers.\n"
	.string "3. Escort stragglers aboard.$"

MossdeepCity_RangerBase_1F_Text_MissionBoardSearch:
	.string "MISSION BOARD - URGENT\n"
	.string "MOSSDEEP EVACUATION\p"
	.string "1. Head count at the ferry. DONE\n"
	.string "2. MISSING: boy + POOCHYENA,\l"
	.string "   near the MART.\p"
	.string "3. Escort stragglers aboard.$"
