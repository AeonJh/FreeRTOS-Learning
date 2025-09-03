/*
 * FreeRTOS Configuration for Learning Examples
 * Based on FreeRTOS v11.2.0 template
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdio.h>

// Hardware description
#define configCPU_CLOCK_HZ                        100000000
#define configTICK_RATE_HZ                        1000
#define configTICK_TYPE_WIDTH_IN_BITS             TICK_TYPE_WIDTH_32_BITS

// Scheduling behaviour  
#define configUSE_PREEMPTION                      1
#define configUSE_TIME_SLICING                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   0
#define configUSE_TICKLESS_IDLE                   0
#define configMAX_PRIORITIES                      5
#define configMINIMAL_STACK_SIZE                  128
#define configMAX_TASK_NAME_LEN                   16
#define configIDLE_SHOULD_YIELD                   1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES     1

// Memory allocation
#define configSUPPORT_STATIC_ALLOCATION           0
#define configSUPPORT_DYNAMIC_ALLOCATION          1
#define configTOTAL_HEAP_SIZE                     32768
#define configAPPLICATION_ALLOCATED_HEAP          0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0
#define configENABLE_HEAP_PROTECTOR               0

// Hook functions
#define configUSE_IDLE_HOOK                       0
#define configUSE_TICK_HOOK                       0
#define configUSE_MALLOC_FAILED_HOOK              0
#define configUSE_DAEMON_TASK_STARTUP_HOOK        0
#define configCHECK_FOR_STACK_OVERFLOW            0

// Software timers
#define configUSE_TIMERS                          1
#define configTIMER_TASK_PRIORITY                 (configMAX_PRIORITIES - 1)
#define configTIMER_TASK_STACK_DEPTH              configMINIMAL_STACK_SIZE
#define configTIMER_QUEUE_LENGTH                  5

// Features
#define configUSE_TASK_NOTIFICATIONS              1
#define configUSE_MUTEXES                         1
#define configUSE_RECURSIVE_MUTEXES               1
#define configUSE_COUNTING_SEMAPHORES             1
#define configUSE_QUEUE_SETS                      1
#define configUSE_EVENT_GROUPS                    1
#define configUSE_STREAM_BUFFERS                  1

// Debug and trace
#define configUSE_TRACE_FACILITY                  1
#define configUSE_STATS_FORMATTING_FUNCTIONS      1
#define configGENERATE_RUN_TIME_STATS             0

// API includes
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_xTaskGetSchedulerState            1
#define INCLUDE_xTaskGetCurrentTaskHandle         1
#define INCLUDE_uxTaskGetStackHighWaterMark       1
#define INCLUDE_xTaskGetIdleTaskHandle            1
#define INCLUDE_eTaskGetState                     1
#define INCLUDE_xTimerPendFunctionCall            1

// Assert macro
#define configASSERT(x) if((x) == 0) { printf("ASSERT FAILED: %s:%d\n", __FILE__, __LINE__); for(;;); }

#endif /* FREERTOS_CONFIG_H */