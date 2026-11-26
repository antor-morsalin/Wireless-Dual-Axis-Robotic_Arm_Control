# Wirelessly Controlled Dual-Axis Robotic Arm

A motion-controlled robotic arm that translates hand orientation into responsive two-axis servo movement using ESP32 and ESP-NOW.

## Overview

The project explores an intuitive alternative to conventional button-based robotic arm control: the operator moves their hand, and the arm follows its motion wirelessly. The system uses two ESP32 boards to exchange sensor-derived orientation data and control the arm's two axes.

Developed for the **Microprocessor and Embedded Systems** course at American International University-Bangladesh.

## System architecture

```text
Hand movement
    |
Motion sensing and orientation data
    |
Transmitter ESP32
    |  ESP-NOW
Receiver ESP32
    |
Orientation-to-servo mapping
    |
Dual-axis robotic arm
```

## Key features

- Two-axis motion control through hand movement
- Wireless ESP32-to-ESP32 communication using ESP-NOW
- Sensor-derived orientation mapped to servo movement
- Responsive, low-latency control without a conventional wired controller

## Technologies and hardware

| Component | Role |
| --- | --- |
| ESP32 (two boards) | Transmitter and receiver |
| ESP-NOW | Wireless data exchange |
| Motion sensor | Captures hand orientation |
| Servo motors | Actuate the two arm axes |
| C++ | Embedded control logic |

## Getting started

- Prepare the two ESP32 boards and the motion-sensing and servo hardware used by the implementation.
- Identify the transmitter and receiver firmware and configure their board settings and communication identifiers as required by the code.
- Follow the firmware's pin assignments and calibrate the orientation-to-servo mapping for the physical assembly.
- Upload the corresponding firmware to each board and test each axis independently before operating the full arm.

Use hardware-appropriate power supplies and keep the servo travel within safe mechanical limits.

## Engineering focus

The main challenge is maintaining a responsive connection between physical hand movement and actuator motion while coordinating sensing, wireless communication and embedded control. Latency was not quantified in the available project record.

## Project links

- [Project overview and demonstration](https://morsalin-antor-portfolio.vercel.app/project_info.html?name=robo_arm)
- [GitHub profile](https://github.com/antor-morsalin)
