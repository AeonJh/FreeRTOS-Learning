/*
 * FreeRTOS Support Functions
 * Required static memory allocation and hook functions
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

// Static buffers for idle task
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

// Static buffers for timer task  
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

// Required function: provide memory for idle task
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, 
                                   StackType_t **ppxIdleTaskStackBuffer, 
                                   uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

// Required function: provide memory for timer task
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, 
                                    StackType_t **ppxTimerTaskStackBuffer, 
                                    uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

// Malloc failed hook (called when heap allocation fails)
void vApplicationMallocFailedHook(void)
{
    printf("ERROR: Malloc failed! Out of heap memory.\n");
    printf("Current heap: %lu bytes free of %lu total\n", 
           (unsigned long)xPortGetFreeHeapSize(), 
           (unsigned long)configTOTAL_HEAP_SIZE);
    
    // Halt execution on malloc failure
    for(;;);
}

// Stack overflow hook (called when stack overflow detected)
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("ERROR: Stack overflow in task: %s\n", pcTaskName);
    printf("Task handle: %p\n", (void*)xTask);
    
    // Halt execution on stack overflow
    for(;;);
}