RustboroCity_University_2F_MapScripts::
	.byte 0

RustboroCity_University_2F_EventScript_Student::
	msgbox RustboroCity_University_2F_Text_Student, MSGBOX_NPC
	end

RustboroCity_University_2F_EventScript_Instructor::
	lockall
	msgbox RustboroCity_University_2F_Text_Instructor, MSGBOX_DEFAULT
	msgbox RustboroCity_University_2F_Text_InstructorLift, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_University_2F_EventScript_ReturnPrompt
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_UNIVERSITY_3F, 3, 7
	waitstate
	end
RustboroCity_University_2F_EventScript_ReturnPrompt:
	msgbox RustboroCity_University_2F_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_University_2F_EventScript_InstructorDecline
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_POKEMON_SCHOOL, 3, 7
	waitstate
	end

RustboroCity_University_2F_Text_ReturnPrompt:
	.string "Return to the reception lobby?$"

RustboroCity_University_2F_EventScript_InstructorDecline:
	releaseall
	end
RustboroCity_University_2F_Text_InstructorLift:
	.string "Take the lift to the Climate Archive?$"

RustboroCity_University_2F_Text_Student:
	.string "FIELD STUDIES II:\n"
	.string "Rescue routes, weather and\n"
	.string "training are our classes.\p"
	.string "The stairs lead to the lab.$"

RustboroCity_University_2F_Text_Instructor:
	.string "Our RANGER curriculum is\n"
	.string "open to every badge level.\p"
	.string "Prepare for storms, not\n"
	.string "just POKéMON battles.$"
