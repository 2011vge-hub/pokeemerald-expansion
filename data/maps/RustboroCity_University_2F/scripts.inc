RustboroCity_University_2F_MapScripts::
	.byte 0

RustboroCity_University_2F_EventScript_Student::
	msgbox RustboroCity_University_2F_Text_Student, MSGBOX_NPC
	end

RustboroCity_University_2F_EventScript_Instructor::
	msgbox RustboroCity_University_2F_Text_Instructor, MSGBOX_NPC
	end

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
