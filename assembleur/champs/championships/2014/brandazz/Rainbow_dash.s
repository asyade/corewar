;basic.s

.name		"basic"
.comment	"this is a basic stuff"

loop:
	ld %0, r2
	st r1, 6
	live %0
	ld %0, r2
	zjmp %:loop


0290 0000 0000 0203 7000 0006 0100
0000 0002 9000 0000 0002 09FF E800 0000
