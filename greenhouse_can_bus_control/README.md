# Greenhouse CAN Bus Control System

## Description

Distributed greenhouse monitoring and control system implemented using CAN Bus communication.

The system uses multiple microcontroller nodes to acquire environmental
data, display monitoring information, and control a cooling fan according
to the measured temperature.

## Overview

This project demonstrates the implementation of a distributed embedded
system in which different microcontrollers communicate through a CAN Bus
network.

The system integrates an ESP32 sensor node, an ESP32 monitoring node,
and an STM32 control node.

Each node performs a specific task, allowing the system to separate
sensor acquisition, user interface, and actuator control.

The project integrates:

- ESP32 sensor node
- ESP32 OLED monitoring node
- STM32 fan control node

The system automatically regulates greenhouse temperature using PWM fan control based on environmental data.

## System Architecture

```text
                    ┌─────────────────────┐
                    │      DHT11          │
                    │ Temperature/Humidity│
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │ ESP32 Sensor Node   │
                    │                     │
                    │ Data acquisition    │
                    │ CAN transmission    │
                    └──────────┬──────────┘
                               │
                               │
                         CAN Bus Network
                               │
                ┌──────────────┴──────────────┐
                │                             │
                ▼                             ▼
    ┌─────────────────────┐       ┌─────────────────────┐
    │ ESP32 Display Node  │       │ STM32 Controller    │
    │                     │       │                     │
    │ CAN reception       │       │ CAN reception       │
    │ OLED visualization  │       │ Temperature control │
    └─────────────────────┘       │ PWM generation      │
                                  └──────────┬──────────┘
                                             │
                                             ▼
                                      ┌─────────────┐
                                      │ Cooling Fan │
                                      └─────────────┘

```
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

## Documentation

Paper available in:

docs/greenhouse_can.pdf

## Authors

- Jose Eduardo Chim Cano
- Ian Eduardo Paredes Castillo
- Alan Sebastian Ortiz
