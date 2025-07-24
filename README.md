# Pacman ARM Project

## Overview
This project implements the classic **Pacman game** on an ARM-based microcontroller platform.  
It demonstrates embedded systems programming concepts such as hardware abstraction, real-time event handling, and display control using a TFT screen.  
The firmware is modular, ensuring scalability, maintainability, and portability.

---

## Features
- **Pacman Gameplay:** Fully functional Pacman with movement logic, ghost AI, and collision detection.  
- **TFT Display Rendering:** Smooth frame rendering for characters and map.  
- **Real-Time Operation:** Uses SysTick timer for precise timing of game events.  
- **User Input Handling:** Reads control inputs using GPIO pins.  
- **Modular Drivers:** Separate hardware abstraction layers for SPI, TFT, SysTick, RCC, and GPIO.

---

## Hardware Requirements
- ARM-based microcontroller (e.g., STM32)  
- TFT display compatible with SPI interface  
- Push buttons for user input  
- Power supply and supporting components  

---

## Firmware Drivers Used
- **SPI:** Handles communication with TFT display.  
- **SysTick:** Provides time delays and periodic interrupts for game logic.  
- **TFT Driver:** Manages graphics rendering on the TFT display.  
- **RCC:** Configures and manages system clock for peripherals.  
- **MGPIO:** Handles input buttons and digital outputs.

---
## Advanced Firmware Features Used

- **Modular Driver Architecture**  
  Each peripheral (SPI, SysTick, GPIO, RCC, TFT) is implemented as an independent driver, improving scalability and reusability.

- **Real-Time Task Scheduling**  
  The SysTick timer generates precise periodic interrupts for handling game timing (Pacman movement, ghost AI, and screen refresh) in real time.

- **Hardware Abstraction Layer (HAL) Approach**  
  Code is separated into interface (`.h`) and implementation (`.c`) files, following industry-standard HAL practices.

- **Optimized SPI Communication**  
  High-speed SPI is used for fast TFT rendering, ensuring smooth frame updates with minimal latency.

- **Custom Graphics Engine**  
  A lightweight rendering engine is implemented on the TFT driver for drawing sprites (Pacman, ghosts, walls) and updating only changed parts of the screen to optimize performance.

- **Interrupt-Based Input Handling**  
  GPIO input pins are configured with interrupt capability for responsive button presses without blocking the main loop.

- **Clock Tree Management**  
  RCC driver ensures optimal clock distribution to peripherals, enabling low-power but high-performance operation.

- **Scalable Code Structure**  
  Designed to support additional peripherals (sound, networking, or storage) without restructuring the entire firmware.
