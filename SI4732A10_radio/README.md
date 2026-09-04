# Multiband Radio Receiver Using the SI4732

A functional FM radio receiver developed using the **SI4732 integrated circuit** and an **ESP32**, featuring an OLED display, rotary encoder, custom SMD adapter PCB, and an external audio amplification stage.

## 📖 Overview

This project was developed as part of the **Introduction to Communication Systems** course at the Universidad Politécnica de Yucatán.

The objective was to build a functional radio receiver capable of tuning FM stations, displaying the current frequency and signal quality, and providing amplified audio output through external speakers.

The project combines embedded software, digital communication, PCB design, and radio reception into a single system.

## ✨ Features

- FM radio reception.
- Frequency tuning from **87.5 MHz to 108.0 MHz**.
- Frequency steps of **0.1 MHz**.
- OLED display for the current station and signal information.
- Real-time monitoring of **RSSI** and **SNR**.
- Rotary encoder for station selection.
- I2C communication between the ESP32, OLED display, and SI4732.
- Non-blocking firmware using `millis()`.
- Custom SMD adapter PCB for the SI4732.
- External audio amplification stage.
- Stereo audio output through two speakers.

## 🛠️ Hardware

The main components of the system are:

| Component | Description |
|---|---|
| **ESP32** | Main microcontroller responsible for system control |
| **SI4732** | Radio receiver integrated circuit |
| **OLED Display** | Displays the current frequency and signal information |
| **Rotary Encoder** | Allows the user to change the tuned station |
| **Custom PCB** | SMD adapter board for the SI4732 |
| **Crystal Oscillator** | Provides the required clock signal for the radio IC |
| **Decoupling Capacitors** | Help reduce power-supply noise |
| **Audio Amplifier** | Increases the audio signal level |
| **Potentiometer** | Controls the audio volume |
| **Speakers** | Provide stereo audio output |

## 🔌 System Architecture

The system is divided into three main sections:

### 1. Radio Reception

The **SI4732** is responsible for receiving and tuning FM radio stations.

Because the IC is designed for SMD assembly, a custom adapter PCB was designed to make it easier to connect to a breadboard and integrate it into the complete system.

### 2. Embedded Control

The **ESP32** acts as the main controller. It communicates with the SI4732 and the OLED display through the **I2C protocol**.

The rotary encoder allows the user to change the tuned frequency, while the firmware manages the radio configuration and display updates.

### 3. Audio Output

The audio signal from the radio IC is sent to an external amplification stage.

This stage increases the signal level and allows the audio to be reproduced through two stereo speakers.

## 💻 Firmware

The firmware was developed to provide a fluid and stable user experience.

### Main Functions

- Initialize the I2C communication bus.
- Configure the SI4732 in FM mode.
- Read the rotary encoder.
- Increase or decrease the tuned frequency.
- Apply software limits to the FM band.
- Read RSSI and SNR values.
- Update the OLED display.
- Control the audio output system.

### Non-Blocking Programming

Instead of using `delay()` for periodic updates, the firmware uses `millis()`.

This allows the display to be updated approximately every **300 milliseconds** without blocking the rest of the system, keeping the rotary encoder responsive.

## 📡 FM Tuning

The receiver was configured to operate within the commercial FM band:

```text
Minimum frequency: 87.5 MHz
Maximum frequency: 108.0 MHz
Frequency step:    0.1 MHz
```

The firmware applies software limits to prevent the user from tuning outside the configured band.

## 📊 Signal Monitoring

The OLED display provides information about the current reception quality.

The system reads:

- **RSSI:** Received Signal Strength Indicator.
- **SNR:** Signal-to-Noise Ratio.

These values are used to monitor the quality of the received signal and provide a graphical indication of reception.

## 🖥️ User Interface

The user interacts with the receiver through:

- **Rotary encoder:** Changes the tuned frequency.
- **OLED display:** Shows the current station and signal information.
- **Audio output:** Allows the received station to be heard through external speakers.

## 📁 Project Structure

The following structure is recommended for organizing the repository:

```text
Multiband-Radio-SI4732/
│
├── README.md
│
├── docs/
│   └── Introduction_to_Communication_Systems_Final_Project.pdf
│
├── src/
│   └── ... ESP32 firmware ...
│
├── hardware/
│   ├── schematic/
│   ├── pcb/
│   └── gerbers/
│
└── images/
    ├── receiver.jpg
    ├── pcb.jpg
    └── oled.jpg
```

> **Note:** The folders above are a suggested organization. Add the corresponding files only if they are available in your project.

## 📚 Technical Concepts

This project involved the following concepts:

- Embedded systems.
- FM radio reception.
- I2C communication.
- Microcontroller programming.
- PCB design.
- SMD component integration.
- Signal strength measurement.
- Signal-to-noise ratio.
- Non-blocking programming.
- Audio amplification.

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Integrating a radio receiver IC with an ESP32.
- Designing an adapter PCB for an SMD component.
- Implementing I2C communication between multiple devices.
- Developing a user interface for an embedded system.
- Monitoring radio signal quality.
- Implementing non-blocking firmware.
- Integrating hardware and software into a functional communication system.

## 📄 Documentation

The complete project documentation is available in the following file:

**Introduction to Communication Systems — Final Project**

The document includes the project objective, hardware description, firmware explanation, and conclusion.

## 👥 Team

- **Jose Eduardo Chim Cano**
- **Víctor Adrián Jimenes Castañedas**
- **Alan Sebastián Ortiz Pebas**
- **Ian Eduardo Paredes Castillo**

## 🎓 Academic Information

**Course:** Introduction to Communication Systems  
**Program:** Embedded Systems Engineering  
**University:** Universidad Politécnica de Yucatán  
**Semester:** 7th Semester  
**Project:** Multiband Radio Receiver Using the SI4732 Integrated Circuit

## 📌 Conclusion

The project demonstrated the successful integration of hardware and software through the development of a functional FM radio receiver.

The combination of the **SI4732**, **ESP32**, custom adapter PCB, OLED interface, and external audio amplification stage resulted in a system capable of tuning FM stations and monitoring reception quality in real time.

This project provided practical experience in embedded systems design and the implementation of communication technologies.
