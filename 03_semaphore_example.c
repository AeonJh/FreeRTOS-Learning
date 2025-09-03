/*
 * FreeRTOS Semaphore Example
 * 
 * This example demonstrates:
 * - Binary semaphores for synchronization
 * - Counting semaphores for resource management
 * - Mutual exclusion (mutex)
 * - Critical sections
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xCountingSemaphore;
SemaphoreHandle_t xMutex;

int sharedResource = 0;

void taskGiver(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    for (;;)
    {
        // Give binary semaphore every 2 seconds
        xSemaphoreGive(xBinarySemaphore);
        printf("Giver: Binary semaphore given\n");
        
        // Give counting semaphore (simulate freeing resources)
        xSemaphoreGive(xCountingSemaphore);
        printf("Giver: Counting semaphore given (resources available: %d)\n", 
               uxSemaphoreGetCount(xCountingSemaphore));
        
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));
    }
}

void taskTaker(void *pvParameters)
{
    for (;;)
    {
        // Wait for binary semaphore
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("Taker: Binary semaphore received, doing work...\n");
            vTaskDelay(pdMS_TO_TICKS(500));  // Simulate work
        }
    }
}

void resourceUser1(void *pvParameters)
{
    for (;;)
    {
        // Try to get a resource (counting semaphore)
        if (xSemaphoreTake(xCountingSemaphore, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            printf("User1: Got resource, using it...\n");
            
            // Use mutex to protect shared resource
            if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdTRUE)
            {
                int temp = sharedResource;
                vTaskDelay(1);  // Simulate processing time where interruption could occur
                sharedResource = temp + 1;
                printf("User1: Updated shared resource to %d\n", sharedResource);
                
                xSemaphoreGive(xMutex);
            }
            
            vTaskDelay(pdMS_TO_TICKS(1000));  // Simulate using resource
            // Resource automatically returned when we give counting semaphore back
        }
        else
        {
            printf("User1: No resources available\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

void resourceUser2(void *pvParameters)
{
    for (;;)
    {
        if (xSemaphoreTake(xCountingSemaphore, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            printf("User2: Got resource, using it...\n");
            
            if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdTRUE)
            {
                int temp = sharedResource;
                vTaskDelay(1);
                sharedResource = temp + 10;
                printf("User2: Updated shared resource to %d\n", sharedResource);
                
                xSemaphoreGive(xMutex);
            }
            
            vTaskDelay(pdMS_TO_TICKS(1200));
        }
        else
        {
            printf("User2: No resources available\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

int main(void)
{
    printf("Starting FreeRTOS Semaphore Example\n");
    
    // Create binary semaphore (starts empty)
    xBinarySemaphore = xSemaphoreCreateBinary();
    
    // Create counting semaphore (3 resources available)
    xCountingSemaphore = xSemaphoreCreateCounting(3, 0);
    
    // Create mutex for protecting shared resource
    xMutex = xSemaphoreCreateMutex();
    
    if (xBinarySemaphore != NULL && xCountingSemaphore != NULL && xMutex != NULL)
    {
        xTaskCreate(taskGiver, "Giver", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
        xTaskCreate(taskTaker, "Taker", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
        xTaskCreate(resourceUser1, "User1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(resourceUser2, "User2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        
        vTaskStartScheduler();
    }
    else
    {
        printf("ERROR: Semaphore creation failed!\n");
    }
    
    for (;;);
    return 0;
}