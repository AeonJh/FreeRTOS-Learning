cmake_minimum_required(VERSION 3.16)
project(FreeRTOS_Learn C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Enable compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FreeRTOS configuration
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/freertos)
set(FREERTOS_PORT_DIR ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FREERTOS_DIR}/include
    ${FREERTOS_PORT_DIR}
    ${FREERTOS_PORT_DIR}/utils
)

# Compiler definitions
add_definitions(-DprojCOVERAGE_TEST=0)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g -pthread")

# FreeRTOS source files
set(FREERTOS_SOURCES
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/event_groups.c
    ${FREERTOS_DIR}/stream_buffer.c
    ${FREERTOS_DIR}/portable/MemMang/heap_3.c
    ${FREERTOS_PORT_DIR}/port.c
    ${FREERTOS_PORT_DIR}/utils/wait_for_event.c
)

# Create FreeRTOS library
add_library(freertos_kernel STATIC ${FREERTOS_SOURCES})
target_link_libraries(freertos_kernel pthread)

# Example executables
add_executable(01_basic_task 01_basic_task.c)
target_link_libraries(01_basic_task freertos_kernel pthread)

add_executable(02_queue_example 02_queue_example.c)
target_link_libraries(02_queue_example freertos_kernel pthread)

add_executable(03_semaphore_example 03_semaphore_example.c)
target_link_libraries(03_semaphore_example freertos_kernel pthread)

add_executable(04_timer_example 04_timer_example.c)
target_link_libraries(04_timer_example freertos_kernel pthread)

# Custom target to build all examples
add_custom_target(examples ALL
    DEPENDS 01_basic_task 02_queue_example 03_semaphore_example 04_timer_example
)