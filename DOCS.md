# Tinkercad Arduino IR Lock System Documentation

## Overview
This documentation outlines the process for building a simulated lock system on Tinkercad using an Arduino Uno R3. The system is controlled by an IR remote, which interacts with a servo motor to lock or unlock a mechanism. Feedback is provided through LEDs and LCD displays.

## Main Components
- **Servo Motor**: Operates the lock mechanism.
- **IR Receiver**: Receives signals from the IR remote.
- **LEDs**: Visual indicators of the system's status.
- **LCD Displays**: Provide real-time system status and instructions.

## Building the Prototype on Tinkercad
To create the Tinkercad simulation of the lock system, follow these steps:

1. **Set Up the Workspace**: 
   - Log into your Tinkercad account and create a new project.
   - Select the 'Circuits' section to start a new simulation.

2. **Add Components**: 
   - Use the components panel to drag and drop the Arduino Uno R3 and other components onto the workspace.
   - Ensure that you have all components listed in the 'List of All Components' section available in your simulation.

3. **Wiring**: 
   - Connect the components as specified in the circuit diagram or based on the pin assignments in the provided code.
   - Use wires to connect the IR receiver, servo motor, LEDs, and LCD displays to the corresponding pins on the Arduino.

4. **Code Upload**: 
   - Copy the provided Arduino code into the code editor within Tinkercad.
   - Review and verify the code, checking that all pin assignments match your wiring.

5. **Test the Simulation**: 
   - Click 'Start Simulation' to power the virtual Arduino and run the code.
   - Use the simulated IR remote to enter the password and observe the behavior of the lock system.

6. **Iterate and Debug**: 
   - Make adjustments to the wiring and code as necessary.
   - Use Tinkercad's debugging tools to monitor signals and ensure proper operation.

## List of Components
| Name   | Quantity | Component                           |
| ------ | -------- | ----------------------------------- |
| U1     | 1        | Arduino Uno R3 (Simulated)          |
| SERVO1 | 1        | Positional Micro Servo (Simulated)  |
| U2     | 1        | IR sensor (Simulated)               |
| D1     | 1        | Yellow LED (Simulated)              |
| D3     | 1        | Green LED (Simulated)               |
| D4     | 1        | Red LED (Simulated)                 |
| D5     | 1        | Blue LED (Simulated)                |
| R1-R4  | 4        | 1 kΩ Resistor (Simulated)           |
| L1     | 1        | Light bulb (Simulated)              |
| K1     | 1        | Relay SPDT (Simulated)              |
| Bat4   | 1        | 2 batteries, AA, 1.5V Battery (Simulated) |
| U6-U8  | 3        | PCF8574-based, LCD 16 x 2 (I2C) (Simulated) |

## Features
- Password entry and verification using an IR remote.
- Servo motor actuates the lock in response to the correct password.
- LED indicators for system status: red for locked, blue for unlocked, yellow for servo activity.
- LCD displays provide instructional and status messages.
- Reset feature to secure the system and clear the entered password.

## Operation
- Once the system is powered on, it will prompt for the password via the LCD.
- Entering the correct password will unlock the system, indicated by the servo's rotation and blue LED illumination.
- Incorrect password attempts will result in a locked system status, with red LED indication and error message on the LCD.
- The system can be locked or unlocked manually with specific buttons on the IR remote.
- The light bulb can be controlled when the system is in the unlocked state.

## Notes
This simulation provides a framework for understanding the interplay between various electronic components in an access control system. The hands-on experience gained from building and troubleshooting this simulation is invaluable for learning the basics of electronics and Arduino programming.

## Troubleshooting
- If components do not behave as expected, check the wiring against the pin assignments in the code.
- Ensure that the IR remote buttons are mapped correctly within the code to their respective functions.
- Use the Tinkercad's built-in logic analyzer to trace signals and debug the system.
