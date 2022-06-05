#include "uart.h"
#include "memory.h"
#include "paging.h"

void init()
{
    uart_init();
    memory_init();
    paging_init();

    for (;;);
}

void kmain()
{
    *((uint16_t *)0xC0000000) = 0xbeef;
    
    for (int i = 0; i < 20; i++) {
        uint16_t *ptr = 0xC0000000 + i * 0x1000;
        uart_print_u64_hex_nl((uint64_t) *ptr);
    }

    uart_print_newline();
    uart_print_str("hello, world!\r\n");
}