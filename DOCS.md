# Arduino-based Lock System

## Overview
This system utilizes Arduino to control a lock mechanism with a servo motor, based on inputs from an IR remote control. It provides user feedback through LEDs and LCD displays.

## Main Components
- **Servo Motor**: Manages the locking mechanism.
- **IR Receiver**: Interprets signals from an IR remote.
- **LEDs**: Indicate the system's status and servo's rotation.
- **LCD Displays**: Show instructions and system status.

## List of All Components

| Name   | Quantity | Component                       |
| ------ | -------- | ------------------------------- |
| U1     | 1        | Arduino Uno R3                  |
| SERVO1 | 1        | Positional Micro Servo          |
| U2     | 1        | IR sensor                       |
| D1     | 1        | Yellow LED                      |
| D3     | 1        | Green LED                       |
| D4     | 1        | Red LED                         |
| D5     | 1        | Blue LED                        |
| R1     | 4        | 1 kΩ Resistor                   |
| L1     | 1        | Light bulb                      |
| K1     | 1        | Relay SPDT                      |
| Bat4   | 1        | 2 batteries, AA, 1.5V Battery   |
| U6     | 1        | PCF8574-based, 32 LCD 16 x 2 (I2C) |
| U7     | 1        | PCF8574-based, 33 LCD 16 x 2 (I2C) |
| U4     | 1        | PCF8574-based, 34 LCD 16 x 2 (I2C) |

## Features
1. **Password Entry via IR Remote**: Users input a 5-digit password using the remote.
2. **Lock Control with Servo Motor**: The servo toggles the lock based on the password input.
3. **LED Indicators**:
   - Red LED: System is locked.
   - Blue LED: System is unlocked.
   - Yellow LEDs: Indicate the status of the servo motor.
4. **LCD Status Messages**: Display password entry prompts and system status.
5. **Reset Functionality**: Resets the system to a locked state and clears the entered password.

## Operation
- The system awaits password input. Correct entry unlocks the system, rotating the servo, turning the blue LED on, and displaying a success message on the LCDs.
- Yellow LEDs show the servo's activity.
- An incorrect password entry keeps the system locked, indicated by the red LED and error messages on the LCD.
- Manual lock/unlock is possible via IR remote buttons.
- An additional feature allows for light bulb control when the system is unlocked.

## Installation
- Ensure the Arduino environment and necessary libraries for the IR receiver, servo, and LCD (LiquidCrystal_I2C) are installed.
- Connect hardware components according to the specified pin numbers in the code.

## Notes
This documentation provides a basic overview and operational guide for the Arduino-based lock system. For detailed instructions or troubleshooting, refer to the specific library documentation or Arduino forums.
