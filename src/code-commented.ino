// Include necessary libraries for LCD, IR remote, and Servo control
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Servo.h>

Servo servo; // Create a Servo object to control the servo motor

// Define pin assignments for various components
const int lightBulb = 2; // BULB PIN
const int yellowLED1 = 3;
const int yellowLED2 = 4;
const int redLED = 5;
const int blueLED = 7;
const int resetButton = 10; // Button to reset the system
const int turnRight = 11; // Button to turn servo to 'unlock'
const int powerBulb = 12; // Button to toggle light bulb
const int turnLeft = 13; // Button to turn servo to 'lock'

// Define the password sequence
const int password[] = {1, 2, 3, 5, 8};
int userInput[5]; // Array to store user input via IR remote
int passwordLength = 5; // Define the length of the password
int userInputIndex = 0; // Index to keep track of user input
int button = 0; // Variable to store the button pressed

// State variables
bool isPasswordEntered = false;
bool isUnlocked = false;
bool isSystemActive = true;
bool isLightOn = false;

// Initialize LCD displays with their I2C addresses
LiquidCrystal_I2C lcd0(0x20, 16, 2);
LiquidCrystal_I2C lcd1(0x21, 16, 2);
LiquidCrystal_I2C lcd2(0x22, 16, 2);

// Function to map IR codes to button presses
int mapCodeToButton(unsigned long code) {
    // Use a switch case to map the IR codes to button numbers or actions
    switch(code) {
        // List of IR codes followed by their corresponding button/action
        case 0xFF00BF00: return 10;
        case 0xFE01BF00: return 10;
        case 0xFD02BF00: return 10;
        case 0xFB04BF00: return turnLeft;
        case 0xFA05BF00: return powerBulb;
        case 0xF906BF00: return turnRight;
        case 0xF708BF00: return 10;
        case 0xF609BF00: return 10;
        case 0xF50ABF00: return 10;
        case 0xF30CBF00: return 10;
        case 0xF20DBF00: return 10;
        case 0xF10EBF00: return 10;
        case 0xEF10BF00: return 1;
        case 0xEE11BF00: return 2;
        case 0xED12BF00: return 3;
        case 0xEB14BF00: return 4;
        case 0xEA15BF00: return 5;
        case 0xE916BF00: return 6;
        case 0xE718BF00: return 7;
        case 0xE619BF00: return 8;
        case 0xE51ABF00: return 9;

        default: return -1; // Return -1 if no matching code is found
    }
}

// Function to read IR input and map it to a button press
int readInfrared() {
    int result = -1;

    if (IrReceiver.decode()) {
        unsigned long code = IrReceiver.decodedIRData.decodedRawData;
        result = mapCodeToButton(code);
        IrReceiver.resume(); // Prepare for the next value
    }

    return result;
}

// Setup function to initialize the system
void setup() {
    Serial.begin(9600); // Start serial communication for debugging
    IrReceiver.begin(6); // Start the IR receiver on pin 6
    servo.attach(8, 500, 2500); // Attach the servo on pin 8

    // Set pin modes for LEDs and output devices
    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    pinMode(yellowLED1, OUTPUT);
    pinMode(yellowLED2, OUTPUT);
    pinMode(lightBulb, OUTPUT);

    // Initialize devices to their default state
    digitalWrite(yellowLED1, LOW);
    digitalWrite(yellowLED2, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(lightBulb, HIGH);

    // Initialize LCDs and turn on their backlights
    lcd0.init();
    lcd1.init();
    lcd2.init();
    lcd0.backlight();
    lcd1.backlight();
    lcd2.backlight();

    // Display the initial messages on LCDs
    lcd0.setCursor(0, 0);
    lcd0.print("Arduino IR");
    lcd0.setCursor(0, 1);
    lcd0.print("Lock System");

    lcd1.setCursor(0, 0);
    lcd1.print("System: Locked");

    lcd2.setCursor(0, 0);
    lcd2.print("Enter Password");
    lcd2.setCursor(0, 1);
    lcd2.print("to Continue...");

    delay(1500); // Short delay before clearing the message

    lcd2.clear();
    lcd2.setCursor(0, 0);
    lcd2.print("Enter a Password");
    lcd2.setCursor(0, 1);
    lcd2.print(">");
}

void loop() {
    // Read the button pressed from the IR remote
    button = readInfrared();

    // Handle the input only if the password is not yet entered, the button pressed is a digit, and we haven't reached the password length
    if (!isPasswordEntered && button >= 0 && button <= 9 && userInputIndex < passwordLength) {
        userInput[userInputIndex++] = button; // Store the button press and increment index
        lcd2.setCursor(userInputIndex, 1); // Move the cursor on LCD
        lcd2.print("*"); // Display asterisk for each digit entered
    }

    // Check if password is fully entered
    if (userInputIndex == passwordLength) {
        bool isCorrect = true; // Assume password is correct

        // Check entered password against the set password
        for (int i = 0; i < passwordLength; i++) {
            if (userInput[i] != password[i]) {
                isCorrect = false; // Set flag to false if any digit is wrong
                break;
            }
        }

        // Reset input index for next input
        userInputIndex = 0;

        // Take action based on whether the entered password is correct
        if (isCorrect) {
            // Correct password actions
            isPasswordEntered = true;
            digitalWrite(redLED, LOW); // Turn off red LED
            digitalWrite(blueLED, HIGH); // Turn on blue LED
            lcd2.clear();
            lcd2.print("Valid Password");
            delay(1000);
            lcd2.print("Access Granted!");
            servo.write(0); // Unlock position for servo
            digitalWrite(yellowLED1, HIGH); // Turn on yellow LED1
            digitalWrite(yellowLED2, LOW); // Turn off yellow LED2
            isUnlocked = true;
        } else {
            // Incorrect password actions
            lcd2.clear();
            lcd2.print("Invalid Password");
            delay(1000);
            lcd2.setCursor(0, 1);
            lcd2.print("Access Denied!");
            delay(1000);
            lcd2.clear();
            lcd2.print("Enter Password:");
            lcd2.setCursor(0, 1);
            lcd2.print(">");
        }
    }

    // If password is entered, handle the locking and unlocking actions
    if (isPasswordEntered) {
        // Turn the servo to the lock position if the lock button is pressed
        if (button == turnLeft && isUnlocked) {
            servo.write(90); // Lock position for servo
            // Update system status LEDs
            digitalWrite(yellowLED1, LOW);
            digitalWrite(yellowLED2, HIGH);
            // Update unlocked status
            isUnlocked = false;
            lcd1.print("System: Locked");
        }
        // Turn the servo to the unlock position if the unlock button is pressed
        else if (button == turnRight && !isUnlocked) {
            servo.write(0); // Unlock position for servo
            // Update system status LEDs
            digitalWrite(yellowLED1, HIGH);
            digitalWrite(yellowLED2, LOW);
            // Update unlocked status
            isUnlocked = true;
            lcd1.print("System: Unlocked");
        }

        // Handle light bulb control
        if (button == powerBulb && isUnlocked) {
            isLightOn = !isLightOn; // Toggle light status
            digitalWrite(lightBulb, isLightOn ? HIGH : LOW); // Set light bulb state
        }
    }

    // Reset the system if the reset button is pressed
    if (button == resetButton) {
        // Return servo to lock position
        servo.write(90);
        // Update system status LEDs
        digitalWrite(yellowLED1, LOW);
        digitalWrite(yellowLED2, HIGH);
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, LOW);
        // Reset system states
        isUnlocked = false;
        isPasswordEntered = false;
        userInputIndex = 0;
        // Clear and update LCD messages
        lcd1.print("System: Locked");
        lcd2.clear();
        lcd2.print("Enter Password");
        lcd2.setCursor(0, 1);
        lcd2.print("to Continue...");
        delay(1500); // Brief pause before next input
        lcd2.clear();
        lcd2.print("Enter a Password");
        lcd2.setCursor(0, 1);
        lcd2.print(">");
    }
}
