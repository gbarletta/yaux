.section .usermode

usermode_test:
    li  a6, 0xcafebabe
usermode_test_loop:
    j   usermode_test_loop