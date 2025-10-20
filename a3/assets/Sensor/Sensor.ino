// constants that are used to set pin numbers:
const int analogPin = A0;     // the number of the thermistor pin
const int redPin = 13;        // the number of the RGB LED red pin
const int greenPin = 12;      // the number of the RGB LED green pin
const int bluePin = 11;       // the number of the RGB LED blue pin

// variables that will change:
int sensorValue;              // int variable for the value measured by the thermistor
int lowValue;                 // int variable for the lowest measured value 
int highValue;                // int variable for the highest measured value
int mappedValue;              // int variable for the mapped value

void setup() {
  // initialize the RGB LED pins as an output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // initialize the serial monitor:
  Serial.begin(9600);
}

void loop() {
  // the value measured by the thermistor is stored in sensorValue
  // the sensorValue is constrained to the lowest and highest measured values
  sensorValue = analogRead(analogPin);
  lowValue = 475;
  highValue = 575;
  sensorValue = constrain(sensorValue, lowValue, highValue);

  // the sensorValue is mapped with the lowValue to 0 and highValue to 0 and stored in mappedValue
  // the red, green, and blue values in the RGB LED are set according to the mappedValue
  mappedValue = map(sensorValue, lowValue, highValue, 0, 255);
  int redValue = mappedValue;
  int greenValue = 0; // -(mappedValue/63.75)*(mappedValue-255);
  int blueValue = 255 - mappedValue;
  setColor(redValue, greenValue, blueValue);

  // if the mappedValue is at the lowest or highest value, the LED will flash on and off
  if (mappedValue == 0 || mappedValue == 255) {
    setColor(0, 0, 0);
    delay(200);
    setColor(redValue, greenValue, blueValue);
    delay(200);
  }

  // sensorValue, mappedValue, and color is written to the serial monitor
  Serial.print("Sensor value: ");
  Serial.print(sensorValue);

  Serial.print("\t Mapped value: ");
  Serial.print(mappedValue);

  Serial.print("\t Color: ");
  Serial.print(redValue);
  Serial.print(", ");
  Serial.print(greenValue);
  Serial.print(", ");
  Serial.println(blueValue);
}

// function that sets the RGB LED at the given red, green, and blue values
// code from https://projecthub.arduino.cc/semsemharaz/interfacing-rgb-led-with-arduino-b59902
void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
