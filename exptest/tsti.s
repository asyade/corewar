load:
    ld %10, r2
    ld %100, r3
    ld %200, r4
    ld %-100, r5
set:
    sti r2, %:load, %100
    sti r3, %:load, %200
    sti r4, %10, %300
    sti r5, %10, %300
    sti r5, r4, %400
setlive:
    sti r1, %:live, %1
    sti r1, %:live2, %1
live:
    live %999
live2:
    live %666