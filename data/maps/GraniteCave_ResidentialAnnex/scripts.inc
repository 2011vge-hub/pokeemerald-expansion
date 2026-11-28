GraniteCave_ResidentialAnnex_MapScripts::
	.byte 0

GraniteCave_AnnexResident::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_AnnexResidentIdle
	goto_if_set FLAG_NEO_C4_COURIER_SAFE, GraniteCave_AnnexCourierRepeat
	msgbox GraniteCave_AnnexCourierCheckText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_COURIER_SAFE
GraniteCave_AnnexCourierRepeat:
	msgbox GraniteCave_AnnexCourierSafeText, MSGBOX_DEFAULT
	release
	end
GraniteCave_AnnexResidentIdle:
	msgbox GraniteCave_AnnexResidentText, MSGBOX_DEFAULT
	release
	end
GraniteCave_AnnexCook::
	msgbox GraniteCave_AnnexCookText, MSGBOX_NPC
	end
GraniteCave_AnnexChild::
	msgbox GraniteCave_AnnexChildText, MSGBOX_NPC
	end
GraniteCave_AnnexRepair::
	lock
	faceplayer
	goto_if_unset FLAG_NEO_C4_BRIEF, GraniteCave_AnnexRepairIdle
	goto_if_set FLAG_NEO_C4_WORKER_SAFE, GraniteCave_AnnexWorkerRepeat
	msgbox GraniteCave_AnnexWorkerCheckText, MSGBOX_DEFAULT
	setflag FLAG_NEO_C4_WORKER_SAFE
GraniteCave_AnnexWorkerRepeat:
	msgbox GraniteCave_AnnexWorkerSafeText, MSGBOX_DEFAULT
	release
	end
GraniteCave_AnnexRepairIdle:
	msgbox GraniteCave_AnnexRepairText, MSGBOX_DEFAULT
	release
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

GraniteCave_AnnexCourierCheckText:
	.string "COURIER: I'm on BRAWLY's list.\p"
	.string "The lower corridor is blocked.\n"
	.string "I came back here for shelter.\p"
	.string "I'll stay in the safe rooms.\n"
	.string "Tell the warden I'm accounted for.$"
GraniteCave_AnnexCourierSafeText:
	.string "COURIER: I'm safe, RANGER.\n"
	.string "The warden can mark me present.$"
GraniteCave_AnnexWorkerCheckText:
	.string "WORKER: The support cracked\n"
	.string "while I was checking the wall.\p"
	.string "I'm unhurt. I've closed off the\n"
	.string "damaged passage for now.$"
GraniteCave_AnnexWorkerSafeText:
	.string "WORKER: I'll stay in the annex.\n"
	.string "Tell the warden I'm safe.$"
