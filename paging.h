#ifndef __PAGING_H__
#define __PAGING_H__

#include "types.h"
#include "memory.h"
#include "arch.h"
#include "uart.h"

#define PAGING_PTE_SIZE    8
#define PAGING_PTE_ENTRIES MEMORY_PAGE_SIZE / PAGING_PTE_SIZE
#define PAGING_PTE_VALID   1
#define PAGING_PTE_READ    (1 << 1)
#define PAGING_PTE_WRITE   (1 << 2)
#define PAGING_PTE_EXEC    (1 << 3)
#define PAGING_PTE_USER    (1 << 4)

#define PTE_IS_VALID(x)    (x & 0x1)
#define PPN(x)             (((x >> 28) & 0x3ffffff) | ((x >> 19) & 0x1ff) | ((x >> 10) & 0x1ff)) >> 12
#define VPN0(x)            (x >> 12) & 0x1ff
#define VPN1(x)            (x >> 21) & 0x1ff
#define VPN2(x)            (x >> 30) & 0x1ff

void paging_init();
uint64_t paging_map(uint64_t *page_table, uint64_t virt, uint64_t phys, int write, int exec, int user);

#endif