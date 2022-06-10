#include "trap.h"

__attribute__ ((interrupt ("machine"), aligned (4))) void trap_entry() 
{
    /*uart_print_str("trap!\r\nmcause: ");
    uart_print_u64_hex_nl(riscv_read_mcause());
    uart_print_str("a7: ");
    uart_print_u64_hex_nl(riscv_read_a7());*/
    riscv_write_mepc(riscv_read_mepc() + 4);
}

void trap_init()
{
    riscv_write_mtvec(((uint64_t) &trap_entry));
}