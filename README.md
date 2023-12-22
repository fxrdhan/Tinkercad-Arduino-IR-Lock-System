# Tinkercad Arduino IR Lock System Simulation

## Introduction
This repository contains documentation and code for a simulated Arduino lock system on Tinkercad. The system employs a servo motor controlled by an IR remote, with status indicators provided by LEDs and messages displayed on LCD screens.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Bill of Materials](#bill-of-materials)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features
- Secure password entry via an IR remote
- Actuation of a locking mechanism using a servo motor
- Visual status indicators via LED lights
- Interactive user feedback through LCD displays
- Reset functionality for returning the system to a secure state

## List of Materials
The bill of materials represents the components used in the Tinkercad simulation.

| Name   | Quantity | Component                       |
| ------ | -------- | ------------------------------- |
| U1     | 1        | Arduino Uno R3 (Simulated)      |
| SERVO1 | 1        | Positional Micro Servo (Simulated) |
| U2     | 1        | IR sensor (Simulated)           |
| D1     | 1        | Yellow LED (Simulated)          |
| D3     | 1        | Green LED (Simulated)           |
| D4     | 1        | Red LED (Simulated)             |
| D5     | 1        | Blue LED (Simulated)            |
| R1-R4  | 4        | 1 kΩ Resistor (Simulated)       |
| L1     | 1        | Light bulb (Simulated)          |
| K1     | 1        | Relay SPDT (Simulated)          |
| Bat4   | 1        | 2 batteries, AA, 1.5V Battery (Simulated) |
| U6-U8  | 3        | PCF8574-based, LCD 16 x 2 (I2C) (Simulated) |

## Documentation
For detailed instructions on how to use the simulation, please refer to the `DOCUMENTATION.md` file included in this repository. It contains step-by-step guidance and operational details necessary to interact with the simulation effectively.

## Contributing
Contributions to improve the documentation or the code are welcome. Please submit pull requests with detailed descriptions of your changes for review.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
