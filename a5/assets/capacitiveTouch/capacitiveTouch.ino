/*
  Touch sensor LED strip light

  Parts required:
  - 2 megohm resistor
  - apple and banana
  - LED strip lights
  - N-MOSFET transistor
  - external power supply

  Software required :
  - CapacitiveSensor library by Paul Badger
    https://www.arduino.cc/reference/en/libraries/capacitivesensor/
*/

// import the library (must be located in the Arduino/libraries directory)
#include <CapacitiveSensor.h>

// create instances of the library
CapacitiveSensor capSensorApple = CapacitiveSensor(3, 2);
CapacitiveSensor capSensorBanana = CapacitiveSensor(5, 4);

// thresholds for sensing touch on fruits
int thresholdApple = 500;
int thresholdBanana = 1000;

// pin the LED strip light is connected to
const int ledPin = 9;

// variables to control brightness and fade amount of the LED
int brightness = 0;         // how bright the LED is
int fadeAmount = 1;         // how many points to fade the LED by

void setup() {
  // open a serial connection
  Serial.begin(9600);
  // set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // store the values reported by the sensor in a variable
  long sensorValueApple = capSensorApple.capacitiveSensor(30);
  long sensorValueBanana = capSensorBanana.capacitiveSensor(30);

  // // print out the sensor values and brightness
  // Serial.print("Apple: ");
  // Serial.print(sensorValueApple);
  // Serial.print("\t Banana: ");
  // Serial.print(sensorValueBanana);
  // Serial.print("\t Brightness: ");
  // Serial.println(brightness);

  // set the brightness of pin 9:
  analogWrite(ledPin, brightness);

  // if the apple is touched, fade the LED on until max brightness
  if (sensorValueApple > thresholdApple) {
    if (brightness < 255) {
      brightness = brightness + fadeAmount;
    }
  }

  // if the banana is touched, fade the LED off until there is no brightness
  if (sensorValueBanana > thresholdBanana) {
    // fade the LED off
    if (brightness > 0) {
      brightness = brightness - fadeAmount;
    }
  }

  // if the apple and banana are touched at the same time, flash the LED on and off
  if (sensorValueApple > thresholdApple && sensorValueBanana > thresholdBanana) {
    analogWrite(ledPin, 0);
    delay(100);
    analogWrite(ledPin, brightness);
    delay(100);
  }
}