/*
 * FreeRTOS Software Timer Example
 * 
 * This example demonstrates:
 * - Creating software timers
 * - One-shot vs auto-reload timers
 * - Timer callbacks
 * - Starting/stopping timers from tasks
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include <stdio.h>

TimerHandle_t xOneShotTimer;
TimerHandle_t xAutoReloadTimer;

static int timerCallbackCount = 0;

void oneShotTimerCallback(TimerHandle_t xTimer)
{
    printf("One-shot timer expired at tick %lu\n", xTaskGetTickCount());
}

void autoReloadTimerCallback(TimerHandle_t xTimer)
{
    timerCallbackCount++;
    printf("Auto-reload timer callback #%d at tick %lu\n", 
           timerCallbackCount, xTaskGetTickCount());
    
    // Stop after 5 callbacks to demonstrate timer control
    if (timerCallbackCount >= 5)
    {
        printf("Stopping auto-reload timer\n");
        xTimerStop(xTimer, 0);
    }
}

void timerControlTask(void *pvParameters)
{
    for (;;)
    {
        printf("Control: Starting one-shot timer (3 seconds)\n");
        xTimerStart(xOneShotTimer, 0);
        
        vTaskDelay(pdMS_TO_TICKS(5000));  // Wait 5 seconds
        
        printf("Control: Starting auto-reload timer (1 second interval)\n");
        timerCallbackCount = 0;  // Reset counter
        xTimerStart(xAutoReloadTimer, 0);
        
        vTaskDelay(pdMS_TO_TICKS(8000));  // Wait 8 seconds
        
        printf("Control: Cycle complete, waiting before next cycle...\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void monitorTask(void *pvParameters)
{
    for (;;)
    {
        printf("Monitor: System running at tick %lu\n", xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main(void)
{
    printf("Starting FreeRTOS Timer Example\n");
    
    // Create one-shot timer (3 second period)
    xOneShotTimer = xTimerCreate(
        "OneShot",                    // Timer name
        pdMS_TO_TICKS(3000),         // Timer period in ticks
        pdFALSE,                     // Auto-reload (pdFALSE = one-shot)
        0,                           // Timer ID
        oneShotTimerCallback         // Callback function
    );
    
    // Create auto-reload timer (1 second period)
    xAutoReloadTimer = xTimerCreate(
        "AutoReload",
        pdMS_TO_TICKS(1000),
        pdTRUE,                      // Auto-reload (pdTRUE = repeating)
        0,
        autoReloadTimerCallback
    );
    
    if (xOneShotTimer != NULL && xAutoReloadTimer != NULL)
    {
        xTaskCreate(
            timerControlTask,
            "TimerControl",
            configMINIMAL_STACK_SIZE,
            NULL,
            2,
            NULL
        );
        
        xTaskCreate(
            monitorTask,
            "Monitor",
            configMINIMAL_STACK_SIZE,
            NULL,
            1,
            NULL
        );
        
        vTaskStartScheduler();
    }
    else
    {
        printf("ERROR: Timer creation failed!\n");
    }
    
    for (;;);
    return 0;
}