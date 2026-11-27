GraniteCave_ResidentialAnnex_MapScripts::
	.byte 0

GraniteCave_AnnexResident::
	msgbox GraniteCave_AnnexResidentText, MSGBOX_NPC
	end
GraniteCave_AnnexCook::
	msgbox GraniteCave_AnnexCookText, MSGBOX_NPC
	end
GraniteCave_AnnexChild::
	msgbox GraniteCave_AnnexChildText, MSGBOX_NPC
	end
GraniteCave_AnnexRepair::
	msgbox GraniteCave_AnnexRepairText, MSGBOX_NPC
	end
GraniteCave_AnnexRoster::
	msgbox GraniteCave_AnnexRosterText, MSGBOX_SIGN
	end

GraniteCave_AnnexResidentText:
	.string "I used to sleep above the sea.\n"
	.string "Now I sleep beneath the stone.\p"
	.string "At least we have dry blankets\n"
	.string "and neighbors to look after.$"
GraniteCave_AnnexCookText:
	.string "We share our supplies by family.\p"
	.string "If a boat cannot reach the dock,\n"
	.string "we can still feed everyone here.$"
GraniteCave_AnnexChildText:
	.string "See all those lanterns?\n"
	.string "I count them when I cannot sleep.\p"
	.string "One day I want to be a RANGER\n"
	.string "and help people find their way.$"
GraniteCave_AnnexRepairText:
	.string "We check these supports daily.\p"
	.string "The survey crew keeps records\n"
	.string "of changes deeper in the cave.$"
GraniteCave_AnnexRosterText:
	.string "RESIDENTIAL ANNEX\p"
	.string "Keep the central aisle clear.\n"
	.string "Emergency supplies: west wall.\l"
	.string "Refuge hall: central ladder.$"
