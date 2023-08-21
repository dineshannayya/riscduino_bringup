/* @file CustomKeypad.pde
@Author: Dinesh A
@Project: Riscduiono
@In Caravel flow, IO pad Pull/Down are controlled by caravel. We have modified caravel flash with 
@digitial io[16:13] as input with pull. user can use only use these port for row port
@Date: 19th Aug 2023
@Revision: 0.1

Dependency: Make Sure that you have installed KeyPad Library by MarkStanley,Alexander Brevig. Test for 3.1.1 Version
*/


#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { 'A', '3', '2', '1' },
  { 'B', '6', '5', '4' },
  { 'C', '9', '8', '7' },
  { 'D', '#', '0', '*' }
};
byte rowPins[ROWS] = { 6, 5, 4, 3 };    //connect to the row pinouts of the keypad
byte colPins[COLS] = { 11, 10, 8, 7 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  customKeypad.setDebounceTime(10);
  customKeypad.setHoldTime(400);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print(customKey);
    Serial.print(' ');
  }
}
