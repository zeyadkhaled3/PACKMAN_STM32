# Packman ARM Firmware – Include Files Documentation

## Overview
This firmware is developed for running the Pacman game on an ARM-based microcontroller platform.  
It utilizes modular drivers to ensure scalability, maintainability, and portability across different hardware.

---

## Included Drivers

### 1. SPI (Serial Peripheral Interface)
- **Purpose:**  
  Provides high-speed serial communication between the microcontroller and external peripherals.
- **Usage in this Project:**  
  Used to interface with the TFT display for rendering Pacman graphics efficiently.
- **Header File:**  
  `MSPI_interface.h`

---

### 2. SysTick (System Timer)
- **Purpose:**  
  Offers precise timing, delays, and periodic interrupts.
- **Usage in this Project:**  
  Generates consistent frame updates and timing for Pacman movement and ghost AI.
- **Header File:**  
  `MSYSTICK_interface.h`

---

### 3. TFT Driver
- **Purpose:**  
  Handles initialization and drawing operations for the TFT display.
- **Usage in this Project:**  
  Responsible for rendering game characters (Pacman, ghosts, map) and updating the screen.
- **Header File:**  
  `TFT_interface.h`

---

### 4. RCC (Reset and Clock Control)
- **Purpose:**  
  Configures and manages clock signals for the microcontroller and its peripherals.
- **Usage in this Project:**  
  Ensures stable operation of all modules (SPI, SysTick, GPIO) by providing required clock frequencies.
- **Header File:**  
  `RCC_interface.h`

---

### 5. MGPIO (General Purpose I/O)
- **Purpose:**  
  Provides control over the microcontroller’s general-purpose input/output pins.
- **Usage in this Project:**  
  Used for reading user inputs (game control buttons) and controlling hardware signals when required.
- **Header File:**  
  `MGPIO_interface.h`
