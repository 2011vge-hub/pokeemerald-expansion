RustboroCity_ClimateArchive_MapScripts::
	.byte 0

NeoArchiveHallGauge::
	msgbox NeoArchiveHallGaugeText, MSGBOX_SIGN
	end
NeoArchiveHallGaugeText:
	.string "TIDE GAUGE, OLD MOSSDEEP QUAY\p"
	.string "The brass ring marks high water\n"
	.string "from twenty-five years ago.$"

NeoArchiveHallRecord::
	msgbox NeoArchiveHallRecordText, MSGBOX_SIGN
	end
NeoArchiveHallRecordText:
	.string "ARCHIVE - COASTAL EVACUATIONS\p"
	.string "The oldest map lists three exits.\n"
	.string "Only the upper road is still dry.$"

NeoArchiveHallSample::
	msgbox NeoArchiveHallSampleText, MSGBOX_SIGN
	end
NeoArchiveHallSampleText:
	.string "The display holds a salt-crusted\n"
	.string "warning bell and a new field radio.$"

NeoArchiveHallStaff::
	msgbox NeoArchiveHallStaffText, MSGBOX_NPC
	end
NeoArchiveHallStaffText:
	.string "Welcome to the climate archive!\n"
	.string "Upstairs, Devon interns build the\l"
	.string "sensors that fill our ledgers.$"
