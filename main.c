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

void kmain()
{
    uart_print_str("before!\r\n");
    __asm__ volatile ("ecall");
    uart_print_str("after!\r\n");

    for (;;);
}