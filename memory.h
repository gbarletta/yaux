#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "types.h"

#define MEMORY_PAGE_UNUSED    0
#define MEMORY_PAGE_USED      1
#define MEMORY_PAGE_LAST      2
#define MEMORY_NUM_PAGES   1024
#define MEMORY_PAGE_SIZE   4096

extern uint64_t kernel_heap_start[];

void memory_init();
uint64_t *memory_page_alloc(int pages);
int memory_page_free(void *addr);

#endif