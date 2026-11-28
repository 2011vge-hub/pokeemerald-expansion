@ Optional Relicrest resident. Include from the Relicrest map's scripts.inc
@ when registered; reserve FLAG_NEO_RELICREST_SKULL_FOSSIL in flags.h
@ using a verified unused persistent flag. Do not use a daily/temp flag.
Relicrest_EventScript_FossilPhilosopher::
	lock
	faceplayer
	goto_if_set FLAG_NEO_RELICREST_SKULL_FOSSIL, Relicrest_EventScript_FossilPhilosopherDone
	msgbox Relicrest_Text_FossilPhilosopher, MSGBOX_DEFAULT
	giveitem ITEM_SKULL_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_NEO_RELICREST_SKULL_FOSSIL
	release
	end

Relicrest_EventScript_FossilPhilosopherDone:
	msgbox Relicrest_Text_FossilPhilosopherDone, MSGBOX_DEFAULT
	release
	end

Relicrest_Text_FossilPhilosopher:
	.string "Do you think fossil pokemon\n"
	.string "became fossils because they\l"
	.string "are rock types, or did they\p"
	.string "become rock types because\n"
	.string "they were fossils?\p"
	.string "Anyways here take this.$"

Relicrest_Text_FossilPhilosopherDone:
	.string "he seems really deep in thought\n"
	.string "about what he just said,\l"
	.string "best to leave him alone$"
