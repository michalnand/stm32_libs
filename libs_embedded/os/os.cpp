#include "os.h"

volatile int32_t g_current_task_ptr, g_task_count;

struct sTCB
{
    uint32_t sp;
};

volatile sTCB tcb[OS_MAX_TASK_COUNT];


#ifdef __cplusplus
extern "C" {
#endif

__attribute__((naked)) void PendSV_Handler(void) 
{
    volatile uint32_t sp;

    // store context
    __asm volatile( "push {r4-r7}\n\t"
        "mov r4, r8\n\t"
        "mov r5, r9\n\t"
        "mov r6, r10\n\t"
        "mov r7, r11\n\t"
        "push {r4-r7}\n\t"
        "mrs %0, msp \n\t" :  "=r" (sp)
    );

     // normal mode, store stack pointer and schdule next task
    if (g_current_task_ptr != -1)
    {
        // store stack pointer
        tcb[g_current_task_ptr].sp = sp;

        // next task scheduling, round robin
        g_current_task_ptr = (g_current_task_ptr+1)%g_task_count;
    }
    // system is in init mode, skip saving SP
    else
    {
        g_current_task_ptr = 0;
    }


    // next task stack pointer
    sp = tcb[g_current_task_ptr].sp;   

    // thread mode return, with MSP 
    // restore context
    __asm volatile( "mov lr, %0\n\t"  
        "msr msp, %1\n\t"
        "pop {r4-r7}\n\t"
        "mov r8, r4\n\t"
        "mov r9, r5\n\t"
        "mov r10, r6\n\t"
        "mov r11, r7\n\t"
        "pop {r4-r7}\n\t"
        "bx lr\n\t" : : "r" (0xfffffff9), "r" (sp)
    );
}

void SysTick_Handler(void) 
{
    // trigger PendSV interrupt for context switch
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


#ifdef __cplusplus
}
#endif


void os_init()
{
    g_task_count       = 0;

    for (unsigned int i = 0; i < OS_MAX_TASK_COUNT; i++)
    {
        tcb[i].sp = 0;
    }
}

void os_add_task(void (*task_func)(void), uint32_t *sp, uint32_t sp_size)
{    
    for (unsigned int i = 0; i < sp_size; i++)
    {
        sp[i] = 0;
    }       

    // XPSR : Default value (0x01000000)
    // PC   : Point to the handler function
	sp[sp_size - 1] = 0x21000000;           // xPSR
	sp[sp_size - 2] = (uint32_t)task_func;  // PC
    sp[sp_size - 3] = (uint32_t)task_func;  // LR (EXC_RETURN)
    sp[sp_size - 4] = 0;                    // R12
    sp[sp_size - 5] = 0;                    // R3
    sp[sp_size - 6] = 0;                    // R2
    sp[sp_size - 7] = 0;                    // R1
    sp[sp_size - 8] = 0;                    // R0

    sp[sp_size - 9]  = 0;                   // R7
    sp[sp_size - 10] = 0;                   // R6
    sp[sp_size - 11] = 0;                   // R5
    sp[sp_size - 12] = 0;                   // R4
    sp[sp_size - 13] = 0;                   // R11
    sp[sp_size - 14] = 0;                   // R10
    sp[sp_size - 15] = 0;                   // R9
    sp[sp_size - 16] = 0;                   // R8   

    uint32_t sp_curr = (uint32_t)(&sp[sp_size - OS_CONTEXT_REGS_COUNT]);


    tcb[g_task_count].sp = sp_curr;
    g_task_count++;
}

void os_start()
{   
    g_current_task_ptr = -1;

    // enable PendSV and SysTick interrupt
    // init with low priority
    NVIC_SetPriority(PendSV_IRQn, 0xff);
	NVIC_SetPriority(SysTick_IRQn, 0xfe);

    // 1ms scheduling  time
    SysTick_Config(SystemCoreClock / OS_FREQUENCY);

    // trigger PendSV, start with first task
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    while (1)
    {
        __asm("wfi");
    }
}


void os_yield()
{
    // trigger context switch
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __asm volatile ("wfi"); 
}