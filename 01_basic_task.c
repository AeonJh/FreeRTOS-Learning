/*
 * FreeRTOS Basic Task Example
 * 
 * This example demonstrates:
 * - Creating tasks
 * - Task priorities
 * - Basic task scheduling
 * - Using vTaskDelay()
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void task1(void *pvParameters)
{
    const char *taskName = (const char *)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    for (;;)
    {
        printf("%s is running at tick %lu\n", taskName, xTaskGetTickCount());
        
        // Delay for 1000ms (1 second)
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

void task2(void *pvParameters)
{
    const char *taskName = (const char *)pvParameters;
    
    for (;;)
    {
        printf("%s is running at tick %lu\n", taskName, xTaskGetTickCount());
        
        // Simple delay - less precise than vTaskDelayUntil
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    printf("Starting FreeRTOS Basic Task Example\n");
    
    // Create Task 1 with higher priority
    xTaskCreate(
        task1,              // Function that implements the task
        "Task1",            // Text name for the task
        configMINIMAL_STACK_SIZE, // Stack size in words
        "High Priority Task",     // Parameter passed to task
        2,                  // Priority (0 = lowest, higher numbers = higher priority)
        NULL                // Task handle (not used here)
    );
    
    // Create Task 2 with lower priority
    xTaskCreate(
        task2,
        "Task2", 
        configMINIMAL_STACK_SIZE,
        "Low Priority Task",
        1,                  // Lower priority than Task1
        NULL
    );
    
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
    
    // Should never reach here unless insufficient heap memory
    printf("ERROR: Scheduler failed to start!\n");
    for (;;);
    
    return 0;
}