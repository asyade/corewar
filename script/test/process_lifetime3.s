.name "faux live"
.comment "ff"

	fork	%:bombe
bombe:
	aff		r1
	live	%42
	ld		%1, r3
	ld		%0, r2
	zjmp	%:bombe
