.option norvc               # no compressed instructions
.global entry

.extern init
.extern stack_top

entry:
    csrr    t0, mhartid
    bnez    t0, loop        # if not hart 0, loop forever
    la      sp, stack_top   # set up stack pointer (see link.ld)
    jal     init

loop:
    wfi
    j       loop