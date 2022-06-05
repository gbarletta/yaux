#include "uart.h"
#include "memory.h"

void init()
{
    uart_init();
    memory_init();
    paging_init();

    for (;;);
}

int kmain()
{
    *((unsigned char *)0x10000000) = 'A';
    *((unsigned char *)0x40000000) = 'B';

    uart_print_newline();
    uart_print_str("hello, world!");
}