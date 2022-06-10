#include "uart.h"
#include "memory.h"
#include "trap.h"
#include "paging.h"

void init()
{
    uart_init();
    memory_init();
    trap_init();
    paging_init();

    for (;;);
}

uint64_t *process_page_table;

void init_process()
{
    process_page_table = memory_page_zalloc(1);
    uart_print_u64_hex_nl(process_page_table);

    uart_print_str("hello!\r\n");
    
    for (int i = 0; i < 16; i++) {
        uint64_t ptr = (uint64_t) memory_page_alloc(1);
        paging_map(process_page_table, 0x10000000 + i * 0x1000, ptr, 1, 1, 1);
        uart_print_u64_hex(0x10000000 + i * 0x1000);
        uart_print_str(" -> ");
        uart_print_u64_hex_nl(ptr);
    }

    uart_print_str("BYEE!\r\n");
}

void kmain()
{
    uart_print_str("before!\r\n");
    __asm__ volatile ("li a7, 0xdeadbeef");
    __asm__ volatile ("ecall");
    uart_print_str("after!\r\n");

    init_process();

    riscv_write_satp((uint64_t) (0x8L << 60 | ((uint64_t) process_page_table) >> 12));
    //
    // riscv_write_mstatus(riscv_read_mstatus() & ~(uint64_t)(0b00 << 11));
    riscv_write_sstatus((0 << 11) | (1 << 5) | (1 << 3) | (1 << 1));
    riscv_write_sepc((uint64_t) 0x50000000);
    riscv_sret();
    __asm__ volatile ("sfence.vma");

    for (;;);
}