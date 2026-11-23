@ New game: a quiet Ranger Base orientation room.
@ Professor Birch's introduction has already played during character creation.
@ This is the last recorded segment, not a second in-person conversation.
MossdeepCity_RangerBriefingRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_RangerBriefingRoom_OnFrame
	.byte 0

MossdeepCity_RangerBriefingRoom_OnFrame:
	map_script_2 VAR_NEO_FERRY_DISPATCH, 1, MossdeepCity_RangerBriefingRoom_EventScript_PlayRecord
	.2byte 0

MossdeepCity_RangerBriefingRoom_EventScript_PlayRecord:
	lockall
	applymovement LOCALID_PLAYER, MossdeepCity_RangerBriefingRoom_Movement_FaceMonitor
	waitmovement 0
	msgbox MossdeepCity_RangerBriefingRoom_Text_BirchRecord, MSGBOX_DEFAULT
	playse SE_SELECT
	msgbox MossdeepCity_RangerBriefingRoom_Text_EndRecording, MSGBOX_DEFAULT
	@ The player has finished orientation; Ari and June greet them in person next.
	warp MAP_MOSSDEEP_CITY_RANGER_BASE_1F, 7, 8
	waitstate
	end

MossdeepCity_RangerBriefingRoom_Movement_FaceMonitor:
	face_up
	step_end

MossdeepCity_RangerBriefingRoom_EventScript_Terminal::
	msgbox MossdeepCity_RangerBriefingRoom_Text_Terminal, MSGBOX_SIGN
	end

MossdeepCity_RangerBriefingRoom_Text_BirchRecord:
	.string "RANGER ORIENTATION - RECORDING\p"
	.string "PROF. BIRCH: Hoenn has changed\n"
	.string "a great deal in 25 years.\p"
	.string "A RANGER's duty is to protect\n"
	.string "people AND their POKéMON.\p"
	.string "Challenge the GYM LEADERS, too.\n"
	.string "BADGES help you earn promotions.\p"
	.string "Keep your gear intact and\n"
	.string "your wits about you, RANGER.$"

MossdeepCity_RangerBriefingRoom_Text_EndRecording:
	.string "PROF. BIRCH: Have fun out there.\n"
	.string "And return safely.\p"
	.string "End recording.\p"
	.string "...The display goes dark.$"

MossdeepCity_RangerBriefingRoom_Text_Terminal:
	.string "BIRCH RANGER ORIENTATION\n"
	.string "Last playback: complete.$"
