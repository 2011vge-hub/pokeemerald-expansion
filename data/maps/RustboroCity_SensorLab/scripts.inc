RustboroCity_SensorLab_MapScripts::
	.byte 0

NeoLabGauge::
	msgbox NeoLabGaugeText, MSGBOX_SIGN
	end
NeoLabGaugeText:
	.string "DEVON STUDENT ENGINEERING LAB\p"
	.string "Our pressure gauge lost power when\n"
	.string "the old quay went under.$"

NeoLabRecord::
	msgbox NeoLabRecordText, MSGBOX_SIGN
	end
NeoLabRecordText:
	.string "This prototype has two clocks.\n"
	.string "One runs even if the siren fails.$"

NeoLabSample::
	msgbox NeoLabSampleText, MSGBOX_SIGN
	end
NeoLabSampleText:
	.string "An intern has written in pencil:\n"
	.string "Test the housing in salt water.$"

NeoLabStaff::
	msgbox NeoLabStaffText, MSGBOX_NPC
	end
NeoLabStaffText:
	.string "Midnight lab again! At least the\n"
	.string "commons saved us some soup.$"
