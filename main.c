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

uint64_t *user_page;

void kmain()
{
    user_page = memory_page_zalloc(1);
    uart_print_u64_hex_nl((uint64_t) user_page);

    for (int i = 0; i < 16; i++) {
        uint64_t ptr = (uint64_t) memory_page_zalloc(1);
        paging_map(user_page, 0x40000000 + i * 0x1000, ptr, 1, 1, 1);
    }

    uint32_t *ptr = (uint32_t *)0x80106000;

    *(ptr + 0) = 0x000332b7;
    *(ptr + 1) = 0xbfb2829b;
    *(ptr + 2) = 0x00e29293;
    *(ptr + 3) = 0xabe28293;
    *(ptr + 4) = 0x10500073;

    riscv_write_satp((uint64_t) (0x8L << 60 | ((uint64_t) user_page) >> 12));
    riscv_write_sstatus((1 << 1));
    riscv_write_sepc((uint64_t) 0x40000000);
    riscv_sret();

    for (;;);
}