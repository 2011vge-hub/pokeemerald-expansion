RustboroCity_University_4F_MapScripts::
	.byte 0

RustboroCity_University_4F_EventScript_Roxanne::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, RustboroCity_University_4F_EventScript_RoxanneWithBadge
	msgbox RustboroCity_University_4F_Text_RoxanneGreeting, MSGBOX_DEFAULT
	release
	end

RustboroCity_University_4F_EventScript_RoxanneWithBadge:
	msgbox RustboroCity_University_4F_Text_RoxanneWithBadge, MSGBOX_DEFAULT
	release
	end

RustboroCity_University_4F_EventScript_FacultyAide::
	msgbox RustboroCity_University_4F_Text_FacultyAide, MSGBOX_NPC
	end

RustboroCity_University_4F_Text_RoxanneGreeting:
	.string "ROXANNE: Welcome to my\n"
	.string "office, young RANGER.\p"
	.string "I lead this university,\n"
	.string "but I still teach and\n"
	.string "challenge TRAINERS.\p"
	.string "There is more than one\n"
	.string "path to a strong HOENN.$"

RustboroCity_University_4F_Text_RoxanneWithBadge:
	.string "ROXANNE: You earned a\n"
	.string "badge and still came back\n"
	.string "to study. Good!\p"
	.string "That is the spirit this\n"
	.string "university needs.$"

RustboroCity_University_4F_Text_FacultyAide:
	.string "DEAN ROXANNE oversees\n"
	.string "the GYM and UNIVERSITY.\p"
	.string "Her office is open to\n"
	.string "RANGERS and students.$"
