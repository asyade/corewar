.name "test"
.comment "oulou"


ld	%10, r2
ld	%10, r3
ld	%50, r4
ld	%-0, r5
sub r1, r2, r6
sub r1, r3, r7
sub r5, r1, r8
sub r7, r8, r9
sub r1, r9, r10
st	r6, 100
st	r7, 108
st	r8, 116
st	r9, 132
st	r10, 164
