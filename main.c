#include "uart.h"
#include "memory.h"

int kmain()
{
    uart_init();
    memory_init();

    

    return 0;
}