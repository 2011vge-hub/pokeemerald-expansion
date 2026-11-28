RustboroCity_University_3F_MapScripts::
	.byte 0

RustboroCity_University_3F_EventScript_SensorEngineer::
	lock
	faceplayer
	goto_if_set FLAG_NEO_C4_STERN_REVIEWED, RustboroCity_University_3F_NeoCoastalMatch
	goto_if_set FLAG_NEO_C2_DEBRIEF_DONE, RustboroCity_University_3F_NeoGaugeMatch
	msgbox RustboroCity_University_3F_Text_SensorEngineer, MSGBOX_DEFAULT
	release
	end
RustboroCity_University_3F_NeoGaugeMatch:
	msgbox RustboroCity_University_3F_Text_NeoGaugeMatch, MSGBOX_DEFAULT
	release
	end
RustboroCity_University_3F_NeoCoastalMatch:
	msgbox RustboroCity_University_3F_Text_NeoCoastalMatch, MSGBOX_DEFAULT
	release
	end

RustboroCity_University_3F_EventScript_ArchiveScholar::
	lockall
	msgbox RustboroCity_University_3F_Text_ArchiveScholar, MSGBOX_DEFAULT
	msgbox RustboroCity_University_3F_Text_ArchiveScholarLift, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_University_3F_EventScript_ReturnPrompt
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_UNIVERSITY_4F, 3, 7
	waitstate
	end
RustboroCity_University_3F_EventScript_ReturnPrompt:
	msgbox RustboroCity_University_3F_Text_ReturnPrompt, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, RustboroCity_University_3F_EventScript_ArchiveScholarDecline
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_RUSTBORO_CITY_UNIVERSITY_2F, 3, 7
	waitstate
	end

RustboroCity_University_3F_Text_ReturnPrompt:
	.string "Return to Field Sciences on 2F?$"

RustboroCity_University_3F_EventScript_ArchiveScholarDecline:
	releaseall
	end
RustboroCity_University_3F_Text_ArchiveScholarLift:
	.string "Take the lift to the dean's floor?$"

RustboroCity_University_3F_Text_SensorEngineer:
	.string "DEVON flood sensors read\n"
	.string "pressure deep below HOENN.\p"
	.string "Some data from MOSSDEEP's\n"
	.string "storm makes no sense.$"

RustboroCity_University_3F_Text_ArchiveScholar:
	.string "The Climate Archive keeps\n"
	.string "every storm siren record.\p"
	.string "The latest MOSSDEEP entry\n"
	.string "is under investigation.$"

RustboroCity_University_3F_Text_NeoGaugeMatch:
	.string "M-17 was on both of your reports.\p"
	.string "We're checking when the pressure\n"
	.string "rose and when the siren sounded.\p"
	.string "We won't assume a cause yet.$"
RustboroCity_University_3F_Text_NeoCoastalMatch:
	.string "STERN sent the DEWFORD readings.\p"
	.string "The timing matches the inland\n"
	.string "tremors, but we need more data.\p"
	.string "CAYTON's team may help us.$"
