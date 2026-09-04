# STM32 Development Board with Integrated IoT Connectivity

Custom STM32F411CEU6 development board designed for embedded systems, IoT applications, and future smart agriculture solutions.

## Project Overview

This project consists of the design, manufacturing, assembly, and validation of a custom development board based on the STM32F411CEU6 microcontroller.

Unlike conventional STM32 development boards, this design integrates:

- ESP8266 WiFi connectivity
- CH340G USB-to-UART communication
- On-board Boost Converter
- GPIO expansion interface
- ADC, PWM, UART, and I2C support
- Custom PCB designed in EasyEDA
- Industrial-oriented hardware architecture

The board was developed as part of the Embedded Systems course and follows several IPC standards to ensure manufacturability, assembly quality, and signal integrity. 【1-e4a3fa】

---

## Features

✅ STM32F411CEU6 Microcontroller

✅ ESP8266 (ESP-12F) WiFi Module

✅ CH340G USB-UART Interface

✅ Boost Converter Power Stage

✅ PWM Generation

✅ ADC Data Acquisition

✅ UART Telemetry

✅ I2C Communication

✅ GPIO Expansion Headers

✅ PCB Designed Following IPC Standards

---

## Hardware Architecture

### Main Components

- STM32F411CEU6
- ESP8266 ESP-12F
- CH340G USB Interface
- AMS1117 3.3V Regulator
- Boost Converter Stage
- PCIe-Based Expansion Connector
- User Push Buttons and Status LEDs

---

## PCB Design

The PCB was designed using EasyEDA and manufactured through JLCPCB.

Design considerations include:

- Two-layer PCB
- Ground planes on top and bottom layers
- Mixed SMD and THT technologies
- Dedicated decoupling network
- IPC-compliant footprint selection
- Optimized routing for power and signal integrity

### PCB Images

Add your PCB images here:

![PCB Top](images/pcb_top.pngb_bottom.png

![3ges/pcb_3d.png

---

## Functional Validation

The final hardware was validated through multiple tests.

### ADC Validation

- 12-bit ADC acquisition
- Input range from 0V to 3.3V
- Error margin below 2%

### PWM Validation

- Variable duty cycle generation
- LED brightness control

### UART Communication

- Reliable communication at 115200 baud
- Real-time telemetry monitoring

### I2C Validation

- LCD 16x2 communication
- Real-time system status display

### Power Stage Validation

- Stable Boost Converter operation
- Output voltage up to approximately 12V
- Thermal stability during continuous operation

---

## Applications

Potential applications include:

- Smart Agriculture
- Greenhouse Automation
- IoT Monitoring Systems
- Environmental Control
- Embedded Systems Education
- Rapid Prototyping

---

## Development Tools

### Hardware

- EasyEDA
- JLCPCB Manufacturing Services

### Firmware

- STM32CubeIDE
- STM32 HAL Libraries
- C Programming Language

### Validation

- Hercules Serial Terminal
- Digital Multimeter
- Oscilloscope

---

## Repository Structure

```text
STM32-Development-Board/
│
├── README.md
├── docs/
│   └── STM32_development_board.pdf
│
├── hardware/
│   ├── schematic.pdf
│   ├── pcb_top.png
│   ├── pcb_bottom.png
│   ├── pcb_3d.png
│   └── gerbers/
│
├── firmware/
│   └── source_code
│
└── images/
```

---

## Documentation

The complete technical report can be found in:

```text
docs/STM32_development_board.pdf
```

The document includes:

- System architecture
- Component selection
- PCB manufacturing process
- IPC standards implementation
- Firmware architecture
- Testing and validation results

---

## Future Improvements

- MQTT implementation
- Cloud connectivity
- Mobile dashboard
- PID temperature control
- Smart greenhouse automation
- RGB Grow Light control
- Data logging and analytics

---

## Author

**José Eduardo Chim Cano**

Embedded Systems Engineering Student

GitHub: https://github.com/TU-USUARIO

LinkedIn: https://linkedin.com/in/TU-USUARIO

---

## License

This project is intended for educational and research purposes.
