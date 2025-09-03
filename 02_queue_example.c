/*
 * FreeRTOS Queue Communication Example
 * 
 * This example demonstrates:
 * - Creating queues
 * - Sending data between tasks
 * - Queue blocking behavior
 * - Producer-Consumer pattern
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

QueueHandle_t xQueue;

typedef struct {
    int sensorId;
    float value;
    TickType_t timestamp;
} SensorData_t;

void producerTask(void *pvParameters)
{
    SensorData_t sensorData;
    int counter = 0;
    
    for (;;)
    {
        // Simulate sensor reading
        sensorData.sensorId = 1;
        sensorData.value = 20.5 + (counter % 10);  // Simulate temperature 20.5-30.5
        sensorData.timestamp = xTaskGetTickCount();
        
        // Send data to queue (wait max 100ms if queue is full)
        if (xQueueSend(xQueue, &sensorData, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            printf("Producer: Sent sensor data %.1f at tick %lu\n", 
                   sensorData.value, sensorData.timestamp);
        }
        else
        {
            printf("Producer: Queue full, data lost!\n");
        }
        
        counter++;
        vTaskDelay(pdMS_TO_TICKS(300));  // Send every 300ms
    }
}

void consumerTask(void *pvParameters)
{
    SensorData_t receivedData;
    
    for (;;)
    {
        // Wait for data from queue (wait indefinitely)
        if (xQueueReceive(xQueue, &receivedData, portMAX_DELAY) == pdTRUE)
        {
            printf("Consumer: Received sensor %d = %.1f (sent at tick %lu)\n",
                   receivedData.sensorId, 
                   receivedData.value,
                   receivedData.timestamp);
        }
        
        // Simulate processing time
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main(void)
{
    printf("Starting FreeRTOS Queue Example\n");
    
    // Create queue that can hold 5 SensorData_t items
    xQueue = xQueueCreate(5, sizeof(SensorData_t));
    
    if (xQueue != NULL)
    {
        // Create producer task
        xTaskCreate(
            producerTask,
            "Producer",
            configMINIMAL_STACK_SIZE,
            NULL,
            2,  // Higher priority
            NULL
        );
        
        // Create consumer task  
        xTaskCreate(
            consumerTask,
            "Consumer",
            configMINIMAL_STACK_SIZE,
            NULL,
            1,  // Lower priority
            NULL
        );
        
        vTaskStartScheduler();
    }
    else
    {
        printf("ERROR: Queue creation failed!\n");
    }
    
    printf("ERROR: Scheduler failed to start!\n");
    for (;;);
    
    return 0;
}