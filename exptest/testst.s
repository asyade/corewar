.name "plop"
.comment "poop"

    ld  %666, r14
def:
    st r14, r2
    st r14, 156
    st r2, 256
    live %1
    ld %0, r13
    zjmp %:def
