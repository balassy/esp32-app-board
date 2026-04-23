// Test configuration:
#define TEST_ONBOARD_LED 0
#define TEST_RGB_LED_CA 1
#define TEST_BUTTON 0
#define TEST_BUZZER 0
#define TEST_RTC 0
#define TEST_SERVO 0
 
// App configuration:
inline constexpr unsigned long SERIAL_BAUD_RATE = 115200;

// Pin configuration:
inline constexpr uint8_t PIN_ONBOARD_LED = 2;
inline constexpr uint8_t PIN_RGB_LED_RED = 13;
inline constexpr uint8_t PIN_RGB_LED_GREEN = 12;
inline constexpr uint8_t PIN_RGB_LED_BLUE = 14;
inline constexpr uint8_t PIN_BUTTON = 32;
inline constexpr uint8_t PIN_BUZZER = 23;
inline constexpr uint8_t PIN_RTC_SDA = 21;
inline constexpr uint8_t PIN_RTC_SCL = 22;
inline constexpr uint8_t PIN_SERVO = 17;   // 4, 5, 16, 17

#include <Wire.h>        // I2C library required by the RTC module.
#include "RTClib.h"      // RTC library by Adafruit
#include <ESP32Servo.h>  // To control the SG90 servo motors

RTC_DS3231 rtc;
Servo servo;

void setup() {
  initSerial();

  #if TEST_ONBOARD_LED
    initOnboardLed();
  #endif

  #if TEST_RGB_LED_CA
    initRgbLed();
  #endif

  #if TEST_BUTTON
    initButton();
  #endif

  #if TEST_BUZZER
    initBuzzer();
  #endif

  #if TEST_RTC
    initRtc();
  #endif

  #if TEST_SERVO
    initServo();
  #endif
}

void loop() {
  #if TEST_ONBOARD_LED
    loopOnboardLed();
  #endif

  #if TEST_RGB_LED_CA
    loopRgbLed();
  #endif

  #if TEST_BUTTON
    loopButton();
  #endif

  #if TEST_RTC
    loopRtc();
  #endif

  #if TEST_SERVO
    loopServo();
  #endif  
}


void initSerial() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println();
  Serial.println(F("initSerial: Initializing serial connection DONE."));
}

void initOnboardLed() {
  Serial.println(F("initOnboardLed: Initializing onboard LED..."));

  pinMode(PIN_ONBOARD_LED, OUTPUT);

  Serial.println(F("initOnboardLed: Initializing onboard LED DONE."));
}

void initRgbLed() {
  Serial.println(F("initRgbLed: Initializing RGB LED..."));

  pinMode(PIN_RGB_LED_RED, OUTPUT);
  pinMode(PIN_RGB_LED_GREEN, OUTPUT);
  pinMode(PIN_RGB_LED_BLUE, OUTPUT);

  // Turn off.
  digitalWrite(PIN_RGB_LED_RED, HIGH);
  digitalWrite(PIN_RGB_LED_GREEN, HIGH);  
  digitalWrite(PIN_RGB_LED_BLUE, HIGH);  

  Serial.println(F("initRgbLed: Initializing RGB LED DONE."));
}

void initButton() {
  Serial.println(F("initButton: Initializing button..."));
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.println(F("initButton: Initializing button DONE."));
}

void initBuzzer() {
  Serial.println(F("initBuzzer: Initializing buzzer..."));
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, HIGH);
  delay(3000);
  digitalWrite(PIN_BUZZER, LOW);
  Serial.println(F("initBuzzer: Initializing buzzer DONE."));
}

void initRtc() {
  Serial.println(F("initRtc: Initializing Real-Time Clock module..."));
  Wire.begin(PIN_RTC_SDA, PIN_RTC_SCL);
  if (!rtc.begin()) {
    Serial.println(F("initRtc: Couldn't find RTC"));
    while (1);
  }
  Serial.println(F("initRtc: Initializing Real-Time Clock module DONE."));
}

void initServo() {
  Serial.println(F("initServo: Initializing servo motor..."));
  servo.attach(PIN_SERVO);
  Serial.println(F("initServo: Initializing servo motor DONE."));
} 

void loopOnboardLed() {
  Serial.println(F("loopOnboardLed: Turning on..."));
  digitalWrite(PIN_ONBOARD_LED, HIGH);
  delay(1000);

  Serial.println(F("loopOnboardLed: Turning off..."));
  digitalWrite(PIN_ONBOARD_LED, LOW);
  delay(1000);   
}

void loopRgbLed() {
  Serial.println(F("loopRgbLed: Turning on red..."));
  digitalWrite(PIN_RGB_LED_RED, LOW);
  delay(500);
  digitalWrite(PIN_RGB_LED_RED, HIGH);
  delay(500);
  Serial.println(F("loopRgbLed: Turning on green..."));
  digitalWrite(PIN_RGB_LED_GREEN, LOW);
  delay(500);
  digitalWrite(PIN_RGB_LED_GREEN, HIGH);
  delay(500);
  Serial.println(F("loopRgbLed: Turning on blue..."));
  digitalWrite(PIN_RGB_LED_BLUE, LOW);
  delay(500);
  digitalWrite(PIN_RGB_LED_BLUE, HIGH);
  delay(500);
  Serial.println(F("loopRgbLed: Turning on red and blue..."));
  digitalWrite(PIN_RGB_LED_RED, LOW);
  digitalWrite(PIN_RGB_LED_BLUE, LOW);
  delay(500);
  digitalWrite(PIN_RGB_LED_RED, HIGH);
  digitalWrite(PIN_RGB_LED_BLUE, HIGH); 
  delay(500);    
}

void loopButton() {
  if(digitalRead(PIN_BUTTON) == LOW) {
    Serial.println(F("loopButton: Pressed"));
  } 
}

void loopRtc() {
  DateTime currentTime = rtc.now();
  printDateTime(currentTime);
  delay(1000);
}

void loopServo() {
  moveServoTo(1);
  moveServoTo(170);
}

void printDateTime(const DateTime &dt) {
  char formattedDateTime[32];
  snprintf(formattedDateTime, sizeof(formattedDateTime), "RTC: %04d.%02d.%02d. %02d:%02d:%02d",
           dt.year(), 
           dt.month(), 
           dt.day(),
           dt.hour(), 
           dt.minute(), 
           dt.second());
  Serial.println(formattedDateTime);
}

void moveServoTo(int newPosition) {
  newPosition = constrain(newPosition, 0, 180);

  // Check if the servo is properly initialized.
  if (!servo.attached()) {
    Serial.println(F("moveServoTo: Servo cannot move, because it is not attached!"));
    return;
  }

  // Get current servo position (0-180).
  int currentPosition = servo.read();

  Serial.println(String(F("moveServoTo: Moving servo from position ")) + String(currentPosition) +
                 String(F(" to position ")) + String(newPosition));

  // Unknown current position -> write target directly
  if (currentPosition < 0 || currentPosition > 180) {
    servo.write(newPosition);
    return;
  }

  // Do not move if already in position.
  if (currentPosition == newPosition) {
    return;
  }

  // Determine moving direction.
  int step = (newPosition > currentPosition) ? 1 : -1;

  for (int pos = currentPosition; pos != newPosition; pos += step) {
    servo.write(pos); 
    delay(2);
  }

  // Ensure final position exactly set.
  servo.write(newPosition);
}
