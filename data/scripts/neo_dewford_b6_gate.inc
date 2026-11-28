@ Dewford Underground B5F descent interaction.
@ Bind to an accessible sign/coord event before the blocked B6F stair.
@ No B6F warp may be active until the later story unlock is approved.
DewfordUnderground_EventScript_B6DescentBlocked::
	lockall
	msgbox DewfordUnderground_Text_B6DescentBlocked, MSGBOX_DEFAULT
	releaseall
	end

DewfordUnderground_Text_B6DescentBlocked:
	.string "a mysterious force blocks your\n"
	.string "descent, we can't go down yet.$"
