#ifndef __ARCH_H__
#define __ARCH_H__

#include "types.h"

// Thanks to xv6 project for PMP code.
#define PMP_R (1L << 0)
#define PMP_W (1L << 1)
#define PMP_X (1L << 2)
#define PMP_MATCH_NAPOT (3L << 3)

__attribute__((always_inline)) static inline void riscv_write_pmpcfg0(uint64_t value)
{
    __asm__ volatile("csrw pmpcfg0, %0" : : "r" (value));
}

__attribute__((always_inline)) static inline void riscv_write_pmpaddr0(uint64_t value)
{
    __asm__ volatile("csrw pmpaddr0, %0" : : "r" (value));
}

__attribute__((always_inline)) static inline void riscv_basic_pmp()
{
    riscv_write_pmpaddr0((~0L) >> 10);
    riscv_write_pmpcfg0(PMP_R | PMP_W | PMP_X | PMP_MATCH_NAPOT);
}

__attribute__((always_inline)) inline void riscv_write_satp(uint64_t value)
{
    __asm__ volatile ("csrrw x0, satp, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_mstatus(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mstatus, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_sstatus(uint64_t value)
{
    __asm__ volatile ("csrrw x0, sstatus, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_mepc(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mepc, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_sepc(uint64_t value)
{
    __asm__ volatile ("csrrw x0, sepc, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_mtvec(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mtvec, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_mret()
{
    __asm__ volatile ("mret");
}

__attribute__((always_inline)) inline void riscv_sret()
{
    __asm__ volatile ("sret");
}


__attribute__((always_inline)) inline uint64_t riscv_read_mstatus()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mstatus" : "=r"(value)); 
    return value;
}

__attribute__((always_inline)) inline uint64_t riscv_read_mepc()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mepc" : "=r"(value)); 
    return value;
}

__attribute__((always_inline)) inline uint64_t riscv_read_mcause()
{
    uint64_t value;
    __asm__ volatile ("csrr %0, mcause" : "=r"(value)); 
    return value;
}

__attribute__((always_inline)) inline uint64_t riscv_read_a7()
{
    uint64_t value;
    __asm__ volatile ("addi %0, a7, 0" : "=r"(value)); 
    return value;
}

#endif