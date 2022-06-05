#ifndef __ARCH_H__
#define __ARCH_H__

#include "types.h"

__attribute__((always_inline)) inline void riscv_write_satp(uint64_t value)
{
    __asm__ volatile ("csrrw x0, satp, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_mstatus(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mstatus, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_write_mepc(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mepc, %0" : "=r"(value));
}


__attribute__((always_inline)) inline void riscv_write_mtvec(uint64_t value)
{
    __asm__ volatile ("csrrw x0, mtvec, %0" : "=r"(value));
}

__attribute__((always_inline)) inline void riscv_mret()
{
    __asm__ volatile ("mret");
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

#endif