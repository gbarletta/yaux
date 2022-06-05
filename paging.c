#include "paging.h"

extern int kmain();

uint64_t *kernel_page_table;

void paging_init()
{
    kernel_page_table = (uint64_t *) memory_page_zalloc(1);

    paging_map(kernel_page_table, 0x10000000, 0x10000000, 1, 0, 0);

    for (uint64_t addr = 0x80000000; addr < 0x80100000; addr += 0x1000) {
        paging_map(kernel_page_table, addr, addr, 1, 1, 0);
    }

    paging_map(kernel_page_table, 0x40000000, 0x10000000, 1, 1, 0);
    paging_map(kernel_page_table, 0xC0000000, 0x801f0000, 1, 0, 0);
    paging_map(kernel_page_table, 0xC0001000, 0x801f0000, 1, 0, 0);

    for (int i = 0; i < 20; i++) {
        uint64_t addr = 0xC0000000 + i * 0x1000;
        paging_map(kernel_page_table, addr, 0x801f0000, 1, 1, 0);
    }

    riscv_write_satp((uint64_t) (0x8L << 60 | ((uint64_t) kernel_page_table) >> 12));
    riscv_write_mstatus((1 << 11) | (1 << 5) | (1 << 3));
    riscv_write_mepc((uint64_t) &kmain);
    riscv_mret();
}

uint64_t paging_map(uint64_t *page_table, uint64_t virt, uint64_t phys, int write, int exec, int user)
{
    uint64_t vpn[3];
    uint64_t *pte;
    uint64_t *alloced_page;

    vpn[2] = VPN2(virt);
    vpn[1] = VPN1(virt);
    vpn[0] = VPN0(virt);

    pte = page_table;

    if (!PTE_IS_VALID(pte[vpn[2]])) {
        alloced_page = memory_page_zalloc(1);
        pte[vpn[2]] = (((uint64_t) alloced_page) >> 2) | PAGING_PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[1]])) {
        alloced_page = memory_page_zalloc(1);
        pte[vpn[1]] = (((uint64_t) alloced_page) >> 2) | PAGING_PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[0]])) {
        pte[vpn[0]] = (phys >> 2) | PAGING_PTE_READ | PAGING_PTE_VALID;

        if (write) pte[vpn[0]] |= PAGING_PTE_WRITE;
        if (exec)  pte[vpn[0]] |= PAGING_PTE_EXEC;
        if (user)  pte[vpn[0]] |= PAGING_PTE_USER;

        // uart_print_u64_hex(virt);
        // uart_print_str(" -> ");
        // uart_print_u64_hex(phys);
        // uart_print_newline();
        
        return pte[vpn[0]];
    }

    return 0;
}