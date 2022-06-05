.option norvc 
.global switch_supervisor

.extern kmain

switch_supervisor:
    li      t0, (1 << 11) | (1 << 5)
    csrw    mstatus, t0
    la      t1, kmain
    csrw    mepc, t1
    mret
