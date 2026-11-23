MossdeepCity_Waterfront_MapScripts::
	.byte 0

@ Neo Emerald 2.0 ferry-terminal facade: no boat, warps or boarding yet.
MossdeepCity_Waterfront_EventScript_TerminalSign::
	msgbox MossdeepCity_Waterfront_Text_TerminalSign, MSGBOX_SIGN
	end

MossdeepCity_Waterfront_Text_TerminalSign:
	.string "MOSSDEEP FERRY TERMINAL\p"
	.string "Evacuation boarding only.\n"
	.string "Follow RANGER instructions.$"
