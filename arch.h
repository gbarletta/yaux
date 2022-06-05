#ifndef __ARCH_H__
#define __ARCH_H__

#include "types.h"

__attribute__((always_inline)) inline void write_satp(uint64_t value)
{
    __asm__ volatile ("csrrw x0, satp, %0" : "=r"(value));
}

#endif