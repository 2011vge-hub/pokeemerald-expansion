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
	lockall
	msgbox RustboroCity_University_4F_Text_FacultyAide, MSGBOX_DEFAULT
	msgbox RustboroCity_University_4F_Text_FacultyAideLift, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_University_4F_EventScript_FacultyAideDecline
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_POKEMON_SCHOOL, 3, 7
	waitstate
	end
RustboroCity_University_4F_EventScript_FacultyAideDecline:
	releaseall
	end
RustboroCity_University_4F_Text_FacultyAideLift:
	.string "Return to the ground-floor lobby?$"

RustboroCity_University_4F_Text_RoxanneGreeting:
	.string "ROXANNE: Welcome to my\n"
	.string "office, young RANGER.\p"
	.string "I lead this university and\n"
	.string "the RUSTBORO GYM.\p"
	.string "Our researchers study changes\n"
	.string "in HOENN's land and climate.\p"
	.string "Finish your field assignment.\n"
	.string "Then meet me at the GYM.$"

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
