.name "di"
.comment "ff"

bombe:
	aff		r1
	st		r1, 6
	live	%42
	ld		%1, r3
	ld		%0, r2
	zjmp	%:bombe
	