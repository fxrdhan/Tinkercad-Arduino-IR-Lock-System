#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Servo.h>

Servo servo;

const int lightBulb = 2; // BULB PIN

const int yellowLED1 = 3;
const int yellowLED2 = 4;
const int redLED = 5;
const int blueLED = 7;
const int resetButton = 10;
const int turnRight = 11;
const int powerBulb = 12;
const int turnLeft = 13;

const int password[] = {1, 2, 3, 5, 8};
int userInput[5];
int passwordLength = 5;
int userInputIndex = 0;
int button = 0;
int pos = 0;

bool isPasswordEntered = false;
bool isUnlocked = false;
bool isSystemActive = true;
bool isLightOn = false;

LiquidCrystal_I2C lcd0(0x20, 16, 2);
LiquidCrystal_I2C lcd1(0x21, 16, 2);
LiquidCrystal_I2C lcd2(0x22, 16, 2);

int mapCodeToButton(unsigned long code) {
    switch(code) {
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

        default: return -1;
    }
}

int readInfrared() {
    int result = -1;

    if (IrReceiver.decode()) {
        unsigned long code = IrReceiver.decodedIRData.decodedRawData;
        result = mapCodeToButton(code);
        IrReceiver.resume();
    }

    return result;
}

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(6);
    servo.attach(8, 500, 2500);

    pinMode(redLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
  	pinMode(yellowLED1, OUTPUT);
  	pinMode(yellowLED2, OUTPUT);
  	pinMode(lightBulb, OUTPUT);

  	digitalWrite(yellowLED1, LOW);
    digitalWrite(yellowLED2, HIGH);
  	digitalWrite(redLED, HIGH);
  	digitalWrite(lightBulb, HIGH);

  	lcd0.init();
    lcd1.init();
  	lcd2.init();
    lcd0.backlight();
    lcd1.backlight();
    lcd2.backlight();

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

  	delay(1500);

    lcd2.clear();
  	lcd2.setCursor(0, 0);
    lcd2.print("Enter a Password");
  	lcd2.setCursor(0, 1);
  	lcd2.print(">");
}

void loop() {
    button = readInfrared();

    if (!isPasswordEntered && button >= 0 && button <= 9 && userInputIndex < passwordLength) {
        userInput[userInputIndex] = button;
        userInputIndex++;

        lcd2.setCursor(userInputIndex, 1);
        lcd2.print("*");
    }

    if (userInputIndex == passwordLength) {
        bool isCorrect = true;

        for (int i = 0; i < passwordLength; i++) {
            if (userInput[i] != password[i]) {
                isCorrect = false;
                break;
            }
        }

        userInputIndex = 0;

        if (isCorrect) {
            isPasswordEntered = true;

            digitalWrite(redLED, LOW);
            digitalWrite(blueLED, HIGH);

            lcd2.clear();
            lcd2.setCursor(0, 0);
            lcd2.print("Valid Password");
            delay(1000);
            lcd2.setCursor(0, 1);
            lcd2.print("Access Granted!");

            servo.write(0);
            digitalWrite(yellowLED1, HIGH);
            digitalWrite(yellowLED2, LOW);

            isUnlocked = true;

        } else {
            lcd2.clear();
            lcd2.setCursor(0, 0);
            lcd2.print("Invalid Password");

            delay(1000);

            lcd2.setCursor(0, 1);
            lcd2.print("Access Denied!");

            delay(1000);

            lcd2.clear();
            lcd2.setCursor(0, 0);
            lcd2.print("Enter Password:");
            lcd2.setCursor(0, 1);
  			lcd2.print(">");
        }
    }

    if (isPasswordEntered) {
        if (button == turnLeft && isUnlocked) {
            servo.write(90);

            digitalWrite(yellowLED1, LOW);
            digitalWrite(yellowLED2, HIGH);

            isUnlocked = false;

            lcd1.clear();
            lcd1.setCursor(0, 0);
            lcd1.print("System: Locked");

        } else if (button == turnRight && !isUnlocked) {
            servo.write(0);

            digitalWrite(yellowLED1, HIGH);
            digitalWrite(yellowLED2, LOW);

            isUnlocked = true;

            lcd1.clear();
            lcd1.setCursor(0, 0);
            lcd1.print("System: Unlocked");

        }

      	if (button == powerBulb && isUnlocked) {
 		 	if (isLightOn) {
                digitalWrite(lightBulb, LOW);
                isLightOn = false;
            } else {
                digitalWrite(lightBulb, HIGH);
                isLightOn = true;
            }
    	}
    }

    if (button == resetButton) {
        servo.write(90);

        digitalWrite(yellowLED1, LOW);
        digitalWrite(yellowLED2, HIGH);
      	digitalWrite(redLED, HIGH);
      	digitalWrite(blueLED, LOW);

        isUnlocked = false;
        isPasswordEntered = false;
        userInputIndex = 0;

        lcd1.clear();
        lcd1.setCursor(0, 0);
        lcd1.print("System: Locked");

        lcd2.clear();
        lcd2.print("Enter Password");
        lcd2.setCursor(0, 1);
        lcd2.print("to Continue...");

        delay(1500);

      	lcd2.clear();
      	lcd2.setCursor(0, 0);
      	lcd2.print("Enter a Password");
       	lcd2.setCursor(0, 1);
  		lcd2.print(">");
    }
}
