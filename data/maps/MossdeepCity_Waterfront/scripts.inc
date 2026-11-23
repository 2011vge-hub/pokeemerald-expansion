MossdeepCity_Waterfront_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_Waterfront_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_Waterfront_OnTransition
	.byte 0

@ Only show rescued passengers while boarding is pending.
MossdeepCity_Waterfront_OnTransition:
	setflag FLAG_NEO_HIDE_QUAY_RESCUEES
	goto_if_ne VAR_NEO_FERRY_DISPATCH, 4, MossdeepCity_Waterfront_OnTransitionDone
	clearflag FLAG_NEO_HIDE_QUAY_RESCUEES
MossdeepCity_Waterfront_OnTransitionDone:
	@ Show the docked ferry until the evacuation has departed (state 5).
	setflag FLAG_NEO_HIDE_DEPARTED_FERRY
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_Waterfront_FerryVisibilityDone
	clearflag FLAG_NEO_HIDE_DEPARTED_FERRY
MossdeepCity_Waterfront_FerryVisibilityDone:
	end

MossdeepCity_Waterfront_OnFrame:
	map_script_2 VAR_NEO_FERRY_DISPATCH, 4, MossdeepCity_Waterfront_EventScript_Boarding
	.2byte 0

@ On-frame boarding scene. State 5 is set before paying +1 mission and +100 XP.
MossdeepCity_Waterfront_EventScript_Boarding:
	lockall
	msgbox MossdeepCity_Waterfront_Text_CrewSpotsThem, MSGBOX_DEFAULT
	msgbox MossdeepCity_Waterfront_Text_BoyThanks, MSGBOX_DEFAULT
	msgbox MossdeepCity_Waterfront_Text_CrewDodges, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WATERFRONT_RESCUE_CHILD, MossdeepCity_Waterfront_Movement_Board
	applymovement LOCALID_WATERFRONT_RESCUE_POOCHYENA, MossdeepCity_Waterfront_Movement_Board
	waitmovement 0
	removeobject LOCALID_WATERFRONT_RESCUE_CHILD
	removeobject LOCALID_WATERFRONT_RESCUE_POOCHYENA
	setflag FLAG_NEO_HIDE_QUAY_RESCUEES
	msgbox MossdeepCity_Waterfront_Text_FerryDeparts, MSGBOX_DEFAULT
	closemessage
	@ Small fade masks the ship's departure without changing travel or rank logic.
	fadescreen FADE_TO_BLACK
	setflag FLAG_NEO_HIDE_DEPARTED_FERRY
	removeobject LOCALID_WATERFRONT_FERRY
	fadescreen FADE_FROM_BLACK
	setvar VAR_NEO_FERRY_DISPATCH, 5
	addvar VAR_NEO_RANGER_MISSIONS, 1
	addvar VAR_NEO_RANGER_XP, NEO_MISSION_FERRY_RESCUE_XP
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox MossdeepCity_Waterfront_Text_MissionComplete, MSGBOX_DEFAULT
	msgbox MossdeepCity_Waterfront_Text_DispatchDebrief, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Waterfront_Movement_Board:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Waterfront_EventScript_RescuedChild::
	msgbox MossdeepCity_Waterfront_Text_BoyWaiting, MSGBOX_NPC
	end

MossdeepCity_Waterfront_EventScript_FerryCrew::
	lock
	faceplayer
	goto_if_ge VAR_NEO_FERRY_DISPATCH, 5, MossdeepCity_Waterfront_EventScript_FerryCrewDone
	msgbox MossdeepCity_Waterfront_Text_CrewWaiting, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Waterfront_EventScript_FerryCrewDone:
	msgbox MossdeepCity_Waterfront_Text_CrewDone, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Waterfront_Text_CrewSpotsThem:
	.string "SAILOR: There he is! The last\n"
	.string "two passengers! Nice work, Ranger.$"

MossdeepCity_Waterfront_Text_BoyThanks:
	.string "BOY: Thank you, {PLAYER}!\p"
	.string "Hey... why did the siren only start\n"
	.string "after the water came in?$"

MossdeepCity_Waterfront_Text_CrewDodges:
	.string "SAILOR: ...Equipment fault. Storms\n"
	.string "do that. Come on, kid. Aboard.$"

MossdeepCity_Waterfront_Text_FerryDeparts:
	.string "The ferry's engines roar to life.\p"
	.string "The last evacuees are aboard!$"

MossdeepCity_Waterfront_Text_MissionComplete:
	.string "MISSION COMPLETE:\n"
	.string "MOSSDEEP EVACUATION\p"
	.string "+1 RANGER MISSION\n"
	.string "+100 RANGER XP$"

MossdeepCity_Waterfront_Text_DispatchDebrief:
	.string "DISPATCH: Every passenger accounted\n"
	.string "for. Outstanding, Ranger.\p"
	.string "Report to CMDR. HALE at RANGER BASE\n"
	.string "when you can.$"

MossdeepCity_Waterfront_Text_BoyWaiting:
	.string "BOY: POOCHYENA's not scared anymore.$"

MossdeepCity_Waterfront_Text_CrewWaiting:
	.string "SAILOR: We can't sail until the head\n"
	.string "count's complete. Two still missing.$"

MossdeepCity_Waterfront_Text_CrewDone:
	.string "SAILOR: Ferry's loaded and away.\p"
	.string "That siren, though... I've crewed\n"
	.string "this route ten years. It's never\l"
	.string "been late before.$"

@ Terminal facade only; no physical ferry sprite or terminal interior yet.
MossdeepCity_Waterfront_EventScript_TerminalSign::
	msgbox MossdeepCity_Waterfront_Text_TerminalSign, MSGBOX_SIGN
	end

MossdeepCity_Waterfront_Text_TerminalSign:
	.string "MOSSDEEP FERRY TERMINAL\p"
	.string "Evacuation boarding only.\n"
	.string "Follow RANGER instructions.$"
