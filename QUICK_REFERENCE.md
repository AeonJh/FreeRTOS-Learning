# FreeRTOS Quick Learning Guide

## Core Concepts

### 1. Tasks (`01_basic_task.c`)
- **Task**: Independent thread of execution
- **Priority**: Higher numbers = higher priority (0 = lowest)
- **Stack**: Each task has its own stack space
- **Scheduling**: Preemptive, priority-based

Key Functions:
- `xTaskCreate()` - Create a task
- `vTaskDelay()` - Block task for specified time
- `vTaskDelayUntil()` - Precise periodic timing
- `vTaskDelete()` - Delete task

### 2. Queues (`02_queue_example.c`)
- **Purpose**: Safe data transfer between tasks
- **FIFO**: First In, First Out
- **Blocking**: Tasks can wait for queue space/data
- **Thread-safe**: No need for additional protection

Key Functions:
- `xQueueCreate()` - Create queue
- `xQueueSend()` - Send data to queue
- `xQueueReceive()` - Receive data from queue

### 3. Semaphores (`03_semaphore_example.c`)
- **Binary**: Signal/synchronization (0 or 1)
- **Counting**: Resource management (0 to N)
- **Mutex**: Mutual exclusion with priority inheritance

Key Functions:
- `xSemaphoreCreateBinary()` - Create binary semaphore
- `xSemaphoreCreateCounting()` - Create counting semaphore
- `xSemaphoreCreateMutex()` - Create mutex
- `xSemaphoreTake()` - Take semaphore (may block)
- `xSemaphoreGive()` - Give/release semaphore

### 4. Software Timers (`04_timer_example.c`)
- **One-shot**: Expires once
- **Auto-reload**: Repeats automatically
- **Callback**: Function called when timer expires
- **Timer Task**: Runs at configurable priority

## Quick Start Steps

1. **Include headers**: `FreeRTOS.h`, `task.h`, etc.
2. **Configure**: Set up `FreeRTOSConfig.h`
3. **Create objects**: Tasks, queues, semaphores
4. **Start scheduler**: `vTaskStartScheduler()`

## Common Patterns

```c
// Task template
void myTask(void *pvParameters) {
    for (;;) {
        // Do work
        vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second delay
    }
}

// Create task
xTaskCreate(myTask, "MyTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
```

## Key Macros
- `pdMS_TO_TICKS(ms)` - Convert milliseconds to ticks
- `portMAX_DELAY` - Wait forever
- `pdTRUE`/`pdFALSE` - Success/failure return values

## Memory Management
- Each task needs its own stack
- Heap used for dynamic allocation
- Configure `configTOTAL_HEAP_SIZE` appropriately

## Best Practices
1. Use appropriate delays to prevent CPU hogging
2. Handle queue/semaphore failures gracefully
3. Use mutexes for shared resource protection
4. Set task priorities carefully
5. Monitor stack usage in development