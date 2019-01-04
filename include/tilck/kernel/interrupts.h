/* SPDX-License-Identifier: BSD-2-Clause */

#pragma once
#include <tilck/kernel/hal.h>

#define MAX_NESTED_INTERRUPTS 32

void set_fault_handler(int fault, void *ptr);

#if KERNEL_TRACK_NESTED_INTERRUPTS
void check_not_in_irq_handler(void);
void check_in_irq_handler(void);
void push_nested_interrupt(int int_num);
void pop_nested_interrupt(void);
void nested_interrupts_drop_top_syscall(void);
void panic_dump_nested_interrupts(void);
void check_in_no_other_irq_than_timer(void);

/* the following funcs are not defined when !KERNEL_TRACK_NESTED_INTERRUPTS */
bool in_syscall(void);
bool in_nested_irq0(void);
int get_nested_interrupts_count(void);

#else
static inline void check_not_in_irq_handler(void) { }
static inline void check_in_irq_handler(void) { }
static inline void push_nested_interrupt(int int_num) { }
static inline void pop_nested_interrupt(void) { }
static inline void nested_interrupts_drop_top_syscall(void) { }
static inline void panic_dump_nested_interrupts(void) { }
static inline void check_in_no_other_irq_than_timer(void) { }
#endif


// NOTE: this function is x86-dependent
static ALWAYS_INLINE bool is_irq(int int_num)
{
   return int_num >= 32 && int_num != SYSCALL_SOFT_INTERRUPT;
}

// NOTE: this function is x86-dependent
static ALWAYS_INLINE bool is_timer_irq(int int_num)
{
   return int_num == 32;
}

// NOTE: this function is x86-dependent
static ALWAYS_INLINE bool is_fault(int int_num)
{
   return 0 <= int_num && int_num < 32;
}
