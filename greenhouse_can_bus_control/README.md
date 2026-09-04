# Greenhouse CAN Bus Control System

## Description

Distributed greenhouse monitoring and control system implemented using CAN Bus communication.

The project integrates:

- ESP32 sensor node
- ESP32 OLED monitoring node
- STM32 fan control node

The system automatically regulates greenhouse temperature using PWM fan control based on environmental data.

## Hardware

- ESP32
- STM32 Bluepill
- DHT11
- SSD1306 OLED
- CAN Bus Modules
- Cooling Fan

## Features

- Temperature monitoring
- Humidity monitoring
- CAN communication
- OLED visualization
- PWM fan control

## Repository Structure

node1_esp32_sensor/
node2_esp32_display/
node3_stm32_controller/
docs/

## Documentation

Paper available in:

docs/greenhouse_can.pdf

## Authors

- Jose Eduardo Chim Cano
- Ian Eduardo Paredes Castillo
- Alan Sebastian Ortiz
