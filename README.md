# DigiKey FreeRTOS Course — ESP32 Exercises

My solutions and demos from [Shawn Hymel's Introduction to RTOS](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz) series on DigiKey's YouTube channel, running on an ESP32-S3.

## Exercises

| Folder | Topic | Description |
|--------|-------|-------------|
| `blink/` | Task Creation | Single FreeRTOS task that toggles an LED at 500 ms intervals using `vTaskDelay`. |
| `2task_with_priority_demo/` | Task Priorities | Two tasks printing to Serial at different priorities — demonstrates preemption and interleaved output. |
| `led_intensity_with_serial_read/` | Task Communication | One task reads an intensity value (0–255) from Serial; another drives LED PWM accordingly. Uses a shared `volatile` variable. |
| `memory_alloc_demo/` | Memory Management | Explores stack high-water marks (`uxTaskGetStackHighWaterMark`) and heap allocation with `pvPortMalloc` / `vPortFree`. |
| `memory_alloc_challenge/` | Memory Challenge | Two tasks communicate via a shared buffer: one reads Serial input, the other prints the received message. |
| `queue_demo/` | Queues (Demo) | Producer sends integers to a FreeRTOS queue; consumer prints them — basic `xQueueSend` / `xQueueReceive` usage. |
| `queue_challenge/` | Queues (Challenge) | Serial command parser: typing `delay <ms>` queues a blink duration for a second task, which toggles the LED and sends a confirmation back through a second queue. |

## Tech Stack

- **Language:** C / C++ (Arduino framework)
- **RTOS:** FreeRTOS (ESP-IDF port)
- **Key APIs:** `xTaskCreatePinnedToCore`, `vTaskDelay`, `xQueueCreate`, `xQueueSend`, `xQueueReceive`, `pvPortMalloc`, `vPortFree`, `uxTaskGetStackHighWaterMark`
- **Concepts:** Task creation & scheduling, task priorities & preemption, shared `volatile` variables, memory allocation (stack vs heap), inter-task communication with queues, non-blocking delays
- **Peripherals:** GPIO (digital output, PWM), Serial (UART), ADC

## Hardware

- **Board:** ESP32-S3-CAM (or any ESP32-S3 dev board)
- **LED pin:** GPIO 2 (built-in) / GPIO 15 (external, used in some sketches)
- **IDE:** Arduino IDE with ESP32 board support

## Building

1. Install the [ESP32 Arduino core](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
2. Open any `.ino` file in Arduino IDE.
3. Select your ESP32-S3 board and port.
4. Upload.

## Course Reference

Based on the official companion repo: [ShawnHymel/introduction-to-rtos](https://github.com/ShawnHymel/introduction-to-rtos)
