#line 1 "/home/dinesha/workarea/opencore/git/riscduino_bringup/2206Q/tests/gpio_output/gpio_output.ino"
// Make Sure that Pull up added for Column pins
#include <Arduino.h>
const int numRows = 24;
const int numCols = 0;

// Defining the row and column pins
const int colPins [numCols] = {};
const int rowPins [numRows] = {25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5, 4, 3, 2};

#line 10 "/home/dinesha/workarea/opencore/git/riscduino_bringup/2206Q/tests/gpio_output/gpio_output.ino"
void setup();
#line 24 "/home/dinesha/workarea/opencore/git/riscduino_bringup/2206Q/tests/gpio_output/gpio_output.ino"
void loop();
#line 10 "/home/dinesha/workarea/opencore/git/riscduino_bringup/2206Q/tests/gpio_output/gpio_output.ino"
void setup() {
  // put your setup code here, to run once:
   for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for (int i = 0; i < numCols; i++) {
    pinMode(colPins[i], INPUT);
  }
 
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int row = 0; row < numRows; row++) {
      
        digitalWrite(rowPins[row], LOW);
        digitalWrite(rowPins[row], HIGH);
       
      }


}

