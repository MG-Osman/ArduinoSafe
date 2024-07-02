
# ArduinoSafe
[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)

[![Simulation on Wokwi](https://github.com/MG-Osman/ArduinoSafe/assets/58115228/f65196db-68e2-4ef5-9a8e-ffb34c9bc546)]([https://wokwi.com/projects/382086358098834433](https://wokwi.com/projects/402300394862997505))
* Arduino Safe Simulation on Wokwi - Click Image to view the live simulation*

## Description

This project implements a digital safe system using an Arduino Uno. It features PIN-based authentication, an LCD interface for user interaction, and a servo motor to simulate the locking mechanism. The system provides a secure and interactive way to manage access to a simulated safe.

## Features

- PIN-based authentication
- LCD display for user feedback
- Servo motor for lock simulation
- Persistent PIN storage using EEPROM
- LED and buzzer for audio-visual feedback
- Initial PIN setup functionality

## Hardware Requirements

- Arduino Uno
- 16x2 LCD Display
- 4x4 Membrane Keypad
- Servo Motor
- LED
- Buzzer
- Resistors and connecting wires

## Software Dependencies

- [Arduino IDE](https://www.arduino.cc/en/software)
- Libraries:
  - [Keypad.h](https://playground.arduino.cc/Code/Keypad/)
  - [Servo.h](https://www.arduino.cc/reference/en/libraries/servo/)
  - [LiquidCrystal.h](https://www.arduino.cc/en/Reference/LiquidCrystal)
  - EEPROM.h (built-in)

## Setup and Installation

1. Connect the hardware components according to the circuit diagram.
2. Install the Arduino IDE and required libraries.
3. Clone this repository or download the source code.
4. Open the `.ino` file in Arduino IDE.
5. Upload the code to your Arduino Uno.

## Usage

1. On first run, the system will prompt for initial PIN setup.
2. Enter a 4-digit PIN to lock the safe.
3. To unlock, enter the correct PIN.
4. When unlocked, press 'A' to lock the safe again.

