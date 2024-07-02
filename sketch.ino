#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo setup
Servo lockServo;
const int SERVO_PIN = 10;

// LCD setup
const int RS = A0, EN = A1, D4 = A2, D5 = A3, D6 = A4, D7 = A5;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// LED and Buzzer setup
const int LED_PIN = 11;
const int BUZZER_PIN = 12;

// Safe parameters
String CORRECT_PIN = "";
String entered_pin = "";
bool is_locked = true;

void setup() {
  // Initialize components
  lockServo.attach(SERVO_PIN);
  lcd.begin(16, 2);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Welcome message
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("MG-Osman'9 safe");
  delay(800);

  // Check if PIN exists in EEPROM
  if (EEPROM.read(0) == 255) {  // 255 is the default value for unwritten EEPROM
    lcd.clear();
    lcd.print("Set initial PIN:");
    setNewPin();
  } else {
    // Read existing PIN from EEPROM
    for (int i = 0; i < 4; i++) {
      CORRECT_PIN += String(EEPROM.read(i));
    }
    lockSafe();
  }
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  if (is_locked) {
    if (key >= '0' && key <= '9') {
      if (entered_pin.length() < 4) {
        entered_pin += key;
        updatePinDisplay();
        playTone(1000, 100);
      }
    } else if (key == '#') {
      checkPin();
    } else if (key == '*') {
      entered_pin = "";
      updatePinDisplay();
    }
  } else {
    if (key == 'A') {
      lockSafe();
    }
  }
}

void checkPin() {
  if (entered_pin == CORRECT_PIN) {
    unlockSafe();
  } else {
    lcd.clear();
    lcd.print("Incorrect PIN");
    playTone(200, 1000);
    blinkLED(3, 200);
    delay(700);
    lockSafe();
  }
  entered_pin = "";
}

void unlockSafe() {
  is_locked = false;
  lockServo.write(0);
  digitalWrite(LED_PIN, HIGH);
  lcd.clear();
  lcd.print("Safe Unlocked");
  lcd.setCursor(0, 1);
  lcd.print("Press A to lock");
  playTone(2000, 500);
}

void lockSafe() {
  is_locked = true;
  lockServo.write(90);
  digitalWrite(LED_PIN, LOW);
  lcd.clear();
  lcd.print("Safe Locked");
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN:");
  entered_pin = "";
  playTone(1500, 500);
}

void setNewPin() {
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        if (entered_pin.length() < 4) {
          entered_pin += key;
          updatePinDisplay();
          playTone(1000, 100);
        }
      } else if (key == '#') {
        if (entered_pin.length() == 4) {
          CORRECT_PIN = entered_pin;
          // Save PIN to EEPROM
          for (int i = 0; i < 4; i++) {
            EEPROM.write(i, entered_pin[i] - '0');
          }
          lcd.clear();
          lcd.print("New PIN set");
          delay(800);
          lockSafe();
          return;
        } else {
          lcd.clear();
          lcd.print("PIN must be 4");
          lcd.setCursor(0, 1);
          lcd.print("digits long");
          delay(2000);
          lcd.clear();
          lcd.print("Set initial PIN:");
          entered_pin = "";
        }
      }
    }
  }
}

void updatePinDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("Enter PIN:      ");
  lcd.setCursor(10, 1);
  for (int i = 0; i < entered_pin.length(); i++) {
    lcd.print('*');
  }
}

void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
}

void blinkLED(int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    delay(duration);
  }
}
