/*
  Button

  While the pushbutton attached to pin 2 is pressed, it turns on a RGB LED connected to 
  digital pins 13, 12, and 11 and cycles through random colors.
  When the button is released, the LED stops on the last color and then fades out.

  The circuit:
  - RBG LED red pin attached from pin 13 to ground through 220 ohm resistor
  - RBG LED green pin attached from pin 12 to ground through 220 ohm resistor
  - RBG LED blue pin attached from pin 11 to ground through 100 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe
  modified 8 Oct 2025
  by Katherine Kang

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/digital/Button/
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int redPin = 13;      // the number of the RGB LED red pin
const int greenPin = 12;    // the number of the RGB LED green pin
const int bluePin = 11;     // the number of the RGB LED blue pin

// variables will change:
int buttonState = 0;        // variable for reading the pushbutton status
int randomRed = 0;          // variable for the red LED value
int randomGreen = 0;        // variable for the green LED value
int randomBlue = 0;         // variable for the blue LED value
int maxValue = 0;           // variable for the largest value out of the red, green, and blue values

void setup() {
  // initialize the RGB LED pins as an output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Set up serial monitor
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // generate random integer numbers for the red, green, and blue values
    randomRed = random(0, 255);
    randomGreen = random(0, 255);
    randomBlue = random(0, 255);
    // turn LED on at that random color
    setColor(randomRed, randomGreen, randomBlue);
    // wait 0.025 seconds to see the colors flashing
    delay(25);
  } else {
    // find the max value of red, green, and blue
    maxValue = max(randomRed, randomGreen);
    maxValue = max(maxValue, randomBlue);
    // if LED is on, fade off
    if (maxValue > 0) {
      // print final RGB values to the serial monitor
      Serial.print(randomRed);
      Serial.print(", ");
      Serial.print(randomGreen);
      Serial.print(", ");
      Serial.println(randomBlue);
      // wait 1 second on the final color
      delay(1000);
      // fade the LED off
      for (int i = 0; i < maxValue; i++) {
        randomRed = max(randomRed - 1, 0);
        randomGreen = max(randomGreen - 1, 0);
        randomBlue = max(randomBlue - 2, 0);
        setColor(randomRed, randomGreen, randomBlue);
        delay(5);
      }
      // make sure the LED is turned off
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
    }
  }
}

// function that sets the RGB LED at the given red, green, and blue values
// code from https://projecthub.arduino.cc/semsemharaz/interfacing-rgb-led-with-arduino-b59902
void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
