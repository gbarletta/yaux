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

__attribute__((always_inline)) inline void riscv_mret()
{
    __asm__ volatile ("mret");
}

#endif