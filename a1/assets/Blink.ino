/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(8, OUTPUT); // red LED
  pinMode(9, OUTPUT); // yellow LED
  pinMode(10, OUTPUT); // green LED
  pinMode(11, OUTPUT); // blue LED
}

// the loop function runs over and over again forever
void loop() {
  // digitalWrite(8, HIGH);    // turn on red LED
  // delay(100);               
  // digitalWrite(9, HIGH);    // turn on yellow LED
  // delay(100);               
  // digitalWrite(10, HIGH);   // turn on green LED
  // delay(100);               
  // digitalWrite(11, HIGH);   // turn on blue LED
  // delay(100);
  // digitalWrite(8, LOW);     // turn off red LED
  // delay(100);               
  // digitalWrite(9, LOW);     // turn off yellow LED
  // delay(100);               
  // digitalWrite(10, LOW);    // turn off green LED
  // delay(100);               
  // digitalWrite(11, LOW);    // turn off blue LED
  // delay(100);

  // turns on each LED from pins 8 to 11 in ascending order with 0.1 second delay
  for (int i = 8; i < 12; i++) {
    digitalWrite(i, HIGH);
    delay(100);
  }

  // turns off each LED from pins 8 to 11 in ascending order with 0.1 second delay
  for (int i = 8; i < 12; i++) {
    digitalWrite(i, LOW);
    delay(100);
  }
}
