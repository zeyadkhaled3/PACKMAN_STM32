# Packman ARM Firmware – Source Files Documentation

## Overview
This firmware is designed to run the Pacman game on an ARM-based microcontroller platform.  
It uses modular driver source files to ensure clarity, maintainability, and ease of development.

---

## Source Files

### 1. `MSPI_program.c`
- **Purpose:**  
  Implements SPI communication protocol functions.
- **Key Responsibilities:**  
  - Initialize SPI peripheral.  
  - Handle data transmission and reception.  
  - Interface with the TFT driver for high-speed display updates.  

---

### 2. `MSYSTK_program.c`
- **Purpose:**  
  Implements SysTick timer functionalities.
- **Key Responsibilities:**  
  - Provide delay functions.  
  - Generate periodic interrupts for frame timing and ghost movement logic.  
  - Synchronize game events (Pacman movement, score updates).  

---

### 3. `TFT_program.c`
- **Purpose:**  
  Provides APIs for the TFT display.
- **Key Responsibilities:**  
  - Initialize and configure the TFT display.  
  - Draw characters, ghosts, and game map on the screen.  
  - Update frames during gameplay.  

---

### 4. `RCC_program.c`
- **Purpose:**  
  Implements clock configuration and management.
- **Key Responsibilities:**  
  - Enable and configure system clocks for all peripherals.  
  - Ensure stable and optimized system performance.  

---

### 5. `MGPIO_program.c`
- **Purpose:**  
  Handles General Purpose Input/Output functionality.
- **Key Responsibilities:**  
  - Read player input (control buttons).  
  - Control status LEDs or other digital outputs if required.  

---
