#!/bin/bash
# FreeRTOS Learning Examples Test Runner

# Check if we're in build directory, if not assume executables are in build/
if [ -f "./01_basic_task" ]; then
    EXEC_PREFIX="./"
else
    EXEC_PREFIX="./build/"
fi

echo "FreeRTOS Learning Examples"
echo "=========================="
echo ""

echo "Available examples:"
echo "1. 01_basic_task      - Basic task creation and scheduling"
echo "2. 02_queue_example   - Inter-task communication with queues"  
echo "3. 03_semaphore_example - Synchronization with semaphores"
echo "4. 04_timer_example   - Software timers"
echo ""

read -p "Choose example (1-4) or 'all' to run all briefly: " choice

case $choice in
    1)
        echo "Running basic task example for 3 seconds..."
        timeout 3s ${EXEC_PREFIX}01_basic_task
        ;;
    2)
        echo "Running queue example for 3 seconds..."
        timeout 3s ${EXEC_PREFIX}02_queue_example
        ;;
    3)
        echo "Running semaphore example for 3 seconds..."
        timeout 3s ${EXEC_PREFIX}03_semaphore_example
        ;;
    4)
        echo "Running timer example for 10 seconds..."
        timeout 10s ${EXEC_PREFIX}04_timer_example
        ;;
    all)
        echo "Running all examples briefly..."
        echo ""
        echo "=== Basic Tasks ==="
        timeout 2s ${EXEC_PREFIX}01_basic_task
        echo ""
        echo "=== Queues ==="
        timeout 2s ${EXEC_PREFIX}02_queue_example
        echo ""
        echo "=== Semaphores ==="
        timeout 3s ${EXEC_PREFIX}03_semaphore_example
        echo ""
        echo "=== Timers ==="
        timeout 5s ${EXEC_PREFIX}04_timer_example
        echo ""
        echo "All examples completed!"
        ;;
    *)
        echo "Invalid choice. Use 1-4 or 'all'"
        exit 1
        ;;
esac