/*
  This sketch uses a LCD display, joystick, and servo motor to create a game of "Find the Hidden Smiley".
  Push the joystick button to start the game. A blinking cursor will appear and can be moved around by the joystick. 
  The servo will point towards the direction of the hidden smiley. Push the joystick button again to check your answer.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 1K resistor:
 * LCD V0 pin to ground
 * LCD A pin to 5V

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 modified 27 Oct 2025
 by Katherine Kang

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to:
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// set up the pins connected to the joystick:
const int x = A0;
const int y = A1;
const int button = 7;

// create Servo object to control a servo:
Servo myservo;

// these constants won't change:
const int numRows = 2;    // the number of rows on the LCD display
const int numCols = 16;   // the number of columns on the LCD display

// these variables will change:
int xval = 0;             // the x value of the joystick
int yval = 0;             // the y value of the joystick
int cursorRow = 0;        // the current row the curser is on
int cursorCol = 0;        // the current column the curser is on
int smileyRow = 0;        // the row that the hidden smiley is on
int smileyCol = 0;        // the column that the hidden smiley is on
int pos = 0;              // variable to store the servo position
bool playGame = false;    // boolean that is true when the game is in progress

// make a custom smiley face character:
byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

// make a custom frownie face character:
byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

void setup() {
  lcd.begin(numCols, numRows);      // set up the LCD's number of columns and rows
  lcd.createChar(0, smiley);        // create the smiley character
  lcd.createChar(1, frownie);       // create the frownie character
  myservo.attach(9);                // attaches the servo on pin 9 to the Servo object
  pinMode(x, INPUT);                // takes the x value of the joystick as an input
  pinMode(y, INPUT);                // takes the y value of the joystick as an input
  pinMode(button, INPUT_PULLUP);    // takes the button state of the joystick as an input
  Serial.begin(9600);               // initializes the serial monitor
}

void loop() {
  int buttonState = digitalRead(button);        // reads the joystick button state (0 when pushed)
  if (buttonState == 0) {                       // when the joystick button is pushed...
    if (playGame == false) {                    // if the game is not in progress,
      lcd.clear();                              // clear the LCD display
      lcd.setCursor(cursorRow, cursorCol);      // set the cursor to its position before the clear
      setSmiley();                              // and set the hidden smiley at a random position.
    } else if (playGame == true) {              // if the game is in progress,
      endGame();                                // the game ends and checks the player's answer
    }
    playGame = !playGame;                       // toggle the gameStart boolean true/false
    delay(1000);                                // wait a second
  }

  if (playGame == true) {                       // while the game is in progress,
    lcd.blink();                                // the cursor blinks at its current position.
    xval = analogRead(x);                       // reads the x value of the joystick and saves it to xval
    yval = analogRead(y);                       // reads the y value of the joystick and saves it to yval  
    if (xval == 0) {                            // if the joystick moves right,
      // Serial.println("right");
      if (cursorRow < 15) {                     // the cursor will move right one position if there is space
        cursorRow++;
      }
      delay(250);
    } else if (xval == 1023) {                  // if the joystick moves left,
      // Serial.println("left");
      if (cursorRow > 0) {                      // the cursor will move left one position if there is space
        cursorRow--;
      }
      delay(250);
    } else if (yval == 0) {                     // if the joystick moves up,
      // Serial.println("up");
      if (cursorCol > 0) {                      // the cursor will move up one position if there is space
        cursorCol--;
      }
      delay(250);
    } else if (yval == 1023) {                  // if the joystick moves down,
      // Serial.println("down");
      if (cursorCol < 1) {                      // the cursor will move down one position if there is space
        cursorCol++;
      }
      delay(250);
    }
    lcd.setCursor(cursorRow, cursorCol);        // sets the cursor to its current position
    servoDirect();                              // directs the servo to the position of the hidden smiley
  }
}

// function that directs the servo to the position of the hidden smiley
void servoDirect() {
  if (cursorRow < smileyRow) {                  // if the cursor is to the left of the smiley,
    myservo.write(20);                          // the servo points right.
  } else if (cursorRow > smileyRow) {           // if the cursor is to the right of the smiley,
    myservo.write(160);                         // the servo points left.
  } else if (cursorCol != smileyCol) {          // if the cursor is on the wrong row,
    myservo.write(90);                          // the servo points down.
  } else {                                      // if the cursor has found the smiley,
    for (pos = 70; pos <= 110; pos += 1) {      // the servo goes from 80 degrees to 120 degrees...
      myservo.write(pos);
      xval = analogRead(x);
      yval = analogRead(y);
      delay(5);
    }
    for (pos = 110; pos >= 70; pos -= 1) {      // and back from 120 degrees to 80 degrees!
      myservo.write(pos);
      xval = analogRead(x);
      yval = analogRead(y);
      delay(5);
    }
  }
}

// function that sets the hidden smiley at a random position on the LCD display
void setSmiley() {
  smileyRow = random(0, 16);
  smileyCol = random(0, 2);
  // Serial.print("Psst! The smiley is hidding at ");
  // Serial.print(smileyRow);
  // Serial.print(", ");
  // Serial.println(smileyCol);
}

// function that ends the game and checks the player's answer
void endGame() {
  if (cursorRow == smileyRow && cursorCol == smileyCol) {     // if the cursor matches the position of the hidden smiley,
    lcd.write((byte)0);                                       // write a smiley face.
  } else {                                                    // if the answer is wrong,
    lcd.setCursor(smileyRow, smileyCol);                      // moves the cursor to correct position
    lcd.write((byte)1);                                       // and writes a frownie face.
  }
  lcd.setCursor(cursorRow, cursorCol);                        // sets the cursor back to the answered position
}