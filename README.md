# FreeRTOS Learning Project

[![FreeRTOS Build and Test](https://github.com/AeonJh/FreeRTOS-Learning/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/AeonJh/FreeRTOS-Learning/actions/workflows/build.yml)

CMake-based FreeRTOS learning environment with clangd support.

## Quick Start

1. **Build the project:**
   ```bash
   ./build.sh
   ```

2. **Run examples:**
   ```bash
   ./run_examples.sh
   ```

## Features

- ✅ CMake build system
- ✅ Automatic `compile_commands.json` generation for clangd
- ✅ FreeRTOS as git submodule (always latest)
- ✅ Multiple learning examples
- ✅ Cross-platform POSIX port

## Examples

- `01_basic_task.c` - Task creation, priorities, delays
- `02_queue_example.c` - Producer-consumer communication
- `03_semaphore_example.c` - Synchronization and mutexes  
- `04_timer_example.c` - Software timers and callbacks

## Development

- **Build:** `./build.sh` or `./build.sh Release`
- **Clean:** `rm -rf build/`
- **IDE Support:** `compile_commands.json` auto-generated for clangd

## Git Submodules

```bash
git submodule update --init --recursive  # First time setup
git submodule update --remote           # Update to latest FreeRTOS
```