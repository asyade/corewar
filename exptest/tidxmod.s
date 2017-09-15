.name "test idx mod"
.comment "polop"

negtest:
	st r1, -255
	st r1, -510
	st r1, -1020
	st r1, -2048
	st r1, -4096
	st r1, -8000
	st r1, -16000
	st r1, -30000
	st r1, -64000
postest:
	st r1, 255
	st r1, 510
	st r1, 1020
	st r1, 2048
	st r1, 4096
	st r1, 8000
	st r1, 16000
	st r1, 30000
	st r1, 64000
