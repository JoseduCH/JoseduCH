# Diesel Level Monitoring System

ESP32-based embedded system for real-time diesel tank monitoring in emergency power plants.

## Overview

This project was developed during my professional internship at the **Centro de Investigación Científica de Yucatán (CICY)**.

The objective was to design and develop an embedded electronic system capable of monitoring the diesel level of an emergency power plant tank. The system measures the distance between an ultrasonic sensor and the fuel surface, calculates the remaining fuel volume and percentage, and provides both local and remote visualization.

The system combines embedded programming, sensor integration, PCB development, and Internet of Things (IoT) technologies to provide a practical solution for continuous fuel monitoring.

> **Note:** This repository presents the technical aspects of the project that can be publicly shared. Confidential information, credentials, and internal infrastructure details are not included.

## Features

- Real-time diesel level measurement.
- Distance measurement using the JSN-SR04T ultrasonic sensor.
- Calculation of fuel volume and filling percentage.
- Local visualization through a 128 × 64 OLED display.
- RGB LED indication of the tank status.
- Critical-level warning with a blinking red LED.
- Wi-Fi connectivity using the ESP32.
- Remote data visualization through Ubidots.
- MQTT communication for IoT data transmission.
- Custom embedded PCB.
- 3D enclosure design.
- Functional testing and validation of the prototype.

## System Architecture

The system is based on an ESP32 microcontroller that receives distance measurements from an ultrasonic sensor and processes the information to determine the fuel level.

The calculated data is displayed locally through an OLED screen and an RGB LED. Additionally, the ESP32 connects to a Wi-Fi network and publishes the measurements to Ubidots using MQTT.

```text
                    ┌─────────────────────┐
                    │   Diesel Tank       │
                    │                     │
                    │  JSN-SR04T Sensor   │
                    └──────────┬──────────┘
                               │
                               │ Distance
                               ▼
                    ┌─────────────────────┐
                    │       ESP32         │
                    │                     │
                    │  Sensor Processing  │
                    │  Volume Calculation │
                    │  Level Percentage   │
                    └──────┬──────┬───────┘
                           │      │
                ┌──────────┘      └──────────┐
                │                            │
                ▼                            ▼
       ┌─────────────────┐         ┌─────────────────┐
       │   OLED Display  │         │     RGB LED     │
       │                 │         │                 │
       │ Volume          │         │ Tank Status     │
       │ Percentage      │         │ Visual Alert    │
       └─────────────────┘         └─────────────────┘

                               │
                               │ Wi-Fi
                               ▼
                    ┌─────────────────────┐
                    │      Ubidots       │
                    │                     │
                    │ Remote Monitoring   │
                    │ Dashboards          │
                    └─────────────────────┘
```

## Hardware

### Main Components

| Component | Description |
|---|---|
| **ESP32** | Main microcontroller with integrated Wi-Fi and Bluetooth |
| **JSN-SR04T** | Waterproof ultrasonic distance sensor |
| **128 × 64 OLED** | Local data visualization |
| **RGB LED** | Visual indication of tank status |
| **Custom PCB** | Embedded electronic board |
| **3D Enclosure** | Mechanical housing for the PCB |

### ESP32

The ESP32 was selected because it provides the processing capabilities required for the project and includes integrated Wi-Fi, which simplifies the IoT implementation.

The microcontroller is responsible for:

- Reading the ultrasonic sensor.
- Processing the distance measurements.
- Calculating the fuel volume.
- Calculating the filling percentage.
- Updating the OLED display.
- Controlling the RGB LED.
- Connecting to the Wi-Fi network.
- Publishing data to Ubidots.

### JSN-SR04T Ultrasonic Sensor

The JSN-SR04T is a waterproof ultrasonic distance sensor used to measure the distance between the sensor and the diesel surface.

The sensor operates at 5 V and uses a waterproof 40 kHz probe.

During the initial tests, a logic-level converter was used to interface the sensor with the ESP32. In the final PCB implementation, a resistor voltage divider was used instead.

### OLED Display

A 128 × 64 OLED display with an I2C interface was integrated to provide local visualization of the system data.

The display shows information such as:

- Fuel volume.
- Filling percentage.
- Warning status.

The project used the following libraries:

```cpp
Adafruit_GFX.h
Adafruit_SSD1306.h
```

### RGB LED

The RGB LED provides a visual indication of the tank condition.

| Fuel Level | LED Status |
|---|---|
| **75% – 100%** | Green |
| **25% – 75%** | Yellow |
| **Below 25%** | Red |
| **Critical Level** | Blinking red |

When the tank reaches a critical level, the system also displays a warning image on the OLED screen.

## Pin Configuration

The following table shows the ESP32 pin configuration used in the project.

| Component | ESP32 Pin |
|---|---|
| Ultrasonic Trigger | GPIO 5 |
| Ultrasonic Echo | GPIO 18 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| RGB LED Red | GPIO 25 |
| RGB LED Green | GPIO 26 |
| RGB LED Blue | GPIO 27 |

## How It Works

### 1. Distance Measurement

The JSN-SR04T sensor measures the distance between the sensor and the surface of the diesel.

The ESP32 receives the measurement and processes it to determine the current fuel level.

### 2. Tank Calibration

To calculate the fuel volume, the following parameters are required:

- Tank radius.
- Tank length.
- Distance corresponding to the full condition.
- Distance corresponding to the empty condition.

For this implementation, the reference distance for the full condition was set to **25 cm**.

The tank was considered empty when the measured distance reached the defined empty reference.

The usable measurement range was calculated as:

```text
Usable Capacity = Empty Distance − Full Distance
```

### 3. Fuel Volume Calculation

The tank was modeled as a horizontal cylinder.

The volume calculation uses the measured fuel height and the tank dimensions.

For the implementation described in the project documentation:

| Parameter | Value |
|---|---:|
| Tank Radius | 29.25 cm |
| Full Reference | 25 cm |
| Empty Reference | 78.5 cm |
| Tank Length | 87.5 cm |
| Usable Measurement Range | 53.5 cm |
| Maximum Calculated Volume | 225.98 L |

The calculated volume is then used to determine the filling percentage.

### 4. Filling Percentage

The filling percentage is calculated by comparing the current fuel volume with the maximum tank capacity.

```text
Filling Percentage = (Current Volume / Maximum Volume) × 100
```

The resulting percentage is displayed on the OLED and used to determine the RGB LED status.

### 5. Local Monitoring

The OLED provides immediate access to the current tank information.

The RGB LED provides an additional visual indication of the system condition, allowing the user to identify normal, stable, and critical states.

### 6. IoT Integration

The ESP32 connects to a local Wi-Fi network and transmits the measured data to Ubidots.

The communication process is based on MQTT.

```text
ESP32 → Wi-Fi → MQTT → Ubidots
```

The transmitted variables include:

- Tank volume.
- Fuel percentage.
- Tank monitoring data.

Ubidots provides dashboards for remote visualization of the measurements.

## Development Process

The project was developed through several stages.

### 1. Sensor Testing

The first stage consisted of testing the ultrasonic sensor with the ESP32.

The objective was to verify the sensor operation and obtain distance measurements.

### 2. Diesel Tank Measurements

The sensor was then tested using the diesel tank to evaluate its behavior under the intended application conditions.

The measurements were used to establish the reference distances required for the volume calculation.

### 3. Schematic and PCB Design

After validating the sensor measurements, the electronic schematic and PCB were developed.

The final implementation included the ESP32, sensor interface, OLED connection, and RGB LED control.

### 4. Firmware Development

The firmware was developed to:

- Read the sensor.
- Process the measurements.
- Calculate volume and percentage.
- Display the information locally.
- Control the RGB LED.
- Connect to Wi-Fi.
- Publish data to Ubidots.

### 5. PCB Testing

The final PCB was assembled and tested to verify the operation of the electronic system.

### 6. Enclosure Design

A 3D enclosure was designed using Siemens NX.

The enclosure was intended to provide a mechanical housing for the PCB and allow future implementation using 3D printing.

## IoT Integration

The ESP32 uses its integrated Wi-Fi module to connect to the internet.

After establishing the connection, the system publishes the measured data to Ubidots through MQTT.

The cloud platform allows the information to be viewed remotely through dashboards.

This integration makes it possible to monitor the tank from a computer or smartphone with internet access.

## Results

The developed prototype successfully demonstrated the following functionalities:

- Measurement of the distance between the sensor and the diesel level.
- Calculation of fuel volume.
- Calculation of filling percentage.
- Local visualization through the OLED display.
- RGB LED status indication.
- Wi-Fi connectivity.
- Data transmission to Ubidots.
- Remote monitoring through the IoT platform.
- ESP32 programming and parameter modification.

The project demonstrated the feasibility of using an embedded electronic system for continuous diesel level monitoring.

## Technologies Used

### Hardware

- ESP32
- JSN-SR04T Ultrasonic Sensor
- 128 × 64 OLED Display
- RGB LED
- Custom PCB
- 3D Enclosure

### Software

- Arduino IDE
- EasyEDA
- Siemens NX
- Ubidots

### Communication

- Wi-Fi
- MQTT
- I2C

### Programming

- C/C++ for ESP32

## Project Contributions

This project was developed as part of a professional internship.

My contributions focused on:

- ESP32 firmware development.
- Ultrasonic sensor integration.
- Distance measurement.
- Fuel volume and percentage calculations.
- OLED display implementation.
- RGB LED status indication.
- Wi-Fi connectivity.
- MQTT communication.
- Ubidots integration.
- Prototype testing and validation.

The schematic, PCB, and enclosure design were developed by my project partner.

## Future Improvements

Possible future improvements include:

- Adding additional sensors for anomaly detection.
- Improving the calibration process.
- Implementing more advanced fuel-level alerts.
- Adding data logging.
- Improving the enclosure design.
- Integrating additional monitoring variables.
- Expanding the system for other industrial applications.

## Acknowledgments

I would like to thank the **Centro de Investigación Científica de Yucatán (CICY)** for providing the opportunity to develop this project during my professional internship.

This experience allowed me to apply and strengthen my knowledge of embedded systems, sensor integration, PCB development, and IoT technologies in a real-world engineering environment.

## Author

**Jose Eduardo Chim Cano**

Embedded Systems Engineering Student  
Universidad Politécnica de Yucatán

## License

This repository is intended for educational and portfolio purposes.

Please contact the author before using or redistributing project materials.
