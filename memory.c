#include "memory.h"

uint8_t memory_pages[MEMORY_NUM_PAGES];
uint16_t alloced_pages;

void memory_init() 
{
    alloced_pages = 0;
    
    for (int i = 0; i < MEMORY_NUM_PAGES; i++) {
        memory_pages[i] = 0;
    }
}

uint64_t *memory_page_zalloc(int pages) 
{
    uint64_t *ptr = memory_page_alloc(pages);

    for (int i = 0; i < pages * MEMORY_PAGE_SIZE; i++) {
        ptr[i] = 0;
    }

    return ptr;
}

uint64_t *memory_page_alloc(int pages) 
{
    for (int i = 0; i < MEMORY_NUM_PAGES; i++) {
        if (memory_pages[i] == MEMORY_PAGE_USED) {
            continue;
        }

        if (memory_pages[i] == MEMORY_PAGE_UNUSED) {
            for (int j = 0; j < pages; j++) {
                if (memory_pages[i + j] != MEMORY_PAGE_UNUSED) {
                    return NULL;
                }
            }

            for (int j = 0; j < pages; j++) {
                memory_pages[i + j] = MEMORY_PAGE_USED;
                alloced_pages++;
            }

            memory_pages[i + (pages - 1)] = MEMORY_PAGE_LAST;
            return (void *) ((uint64_t) kernel_heap_start + (i * MEMORY_PAGE_SIZE));
        }
    }

    return NULL;
}

int memory_page_free(void *addr)
{
    int index = ((uint64_t) addr - (uint64_t) kernel_heap_start) / MEMORY_PAGE_SIZE;

    while (index < MEMORY_NUM_PAGES) {
        if (memory_pages[index] == MEMORY_PAGE_LAST) {
            memory_pages[index] = MEMORY_PAGE_UNUSED;
            alloced_pages--;
            return 1;
        } else {
            memory_pages[index] = MEMORY_PAGE_UNUSED;
            alloced_pages--;
        }

        index++;
    }

    return 0;
}