.name "di"
.comment "ff"

bombe:
	aff		r1
	st		r1, 100
	live	%42
	ld		%1, r3
	ld		%0, r2
	fork	%:bombe
while1:
	ld		%0, r3
	zjmp	%:while1
