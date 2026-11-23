RustboroCity_House3_MapScripts::
	.byte 0

RustboroCity_House3_EventScript_OldMan::
	lock
	faceplayer
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_DEFAULT
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	release
	end

RustboroCity_House3_EventScript_OldWoman::
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames:
	.string "STUDENT COMMONS - NIGHT CAFÉ\p"
	.string "Soup for you, warm towels for your\n"
	.string "team. Sit here a minute.$"
RustboroCity_House3_Text_NamingPikachuPekachu:
	.string "Before finals we pull the tables\n"
	.string "together for a midnight breakfast.$"
RustboroCity_House3_Text_Pekachu:
	.string "PEKACHU: Peka!$"
