.name "sclolus' champ"
.comment "Ca fork"

	ld %12632256, r2
	ld %12632256, r3
	ld %12632256, r4
	ld %12632256, r5
	ld %12632256, r6
	ld %12632256, r7
	ld %12632256, r8
	ld %12632256, r9
	ld %12632256, r10
	ld %12632256, r11
	ld %12632256, r12
	ld %12632256, r13
	ld %12632256, r14
	ld %12632256, r15
	ld %12632256, r16
begin:	st r1, 6
	live %-1
	fork %-10
	st r1, 6
	live %-1
	fork %-10
	st r1, 6
	live %-1
	fork %-10
	st r1, 6
	live %-1
	fork %-10
	st r1, 6
	live %-1
	fork %-10
	ld %0, r16
	zjmp %:begin