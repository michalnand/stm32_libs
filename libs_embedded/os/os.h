#ifndef _OS_H_
#define _OS_H_

/*

    sources how context switch works
    https://interrupt.memfault.com/blog/cortex-m-rtos-context-switching
    https://www.adamh.cz/blog/2016/07/context-switch-on-the-arm-cortex-m0/
*/

#include "drivers.h"

#define OS_MAX_TASK_COUNT       ((uint32_t)4)
#define OS_CONTEXT_REGS_COUNT   ((uint32_t)16)
#define OS_FREQUENCY            ((uint32_t)1000)


void os_init();
void os_add_task(void (*task_func)(void), uint32_t *sp, uint32_t sp_size);
void os_start();
void os_yield();
void os_delay_ms(uint32_t time_ms);


#endif