RustboroCity_University_3F_MapScripts::
	.byte 0

RustboroCity_University_3F_EventScript_SensorEngineer::
	msgbox RustboroCity_University_3F_Text_SensorEngineer, MSGBOX_NPC
	end

RustboroCity_University_3F_EventScript_ArchiveScholar::
	msgbox RustboroCity_University_3F_Text_ArchiveScholar, MSGBOX_NPC
	end

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
