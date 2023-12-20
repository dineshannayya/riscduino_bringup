int led1 = 3;           // the PWM pin the LED is attached to
int led2 = 5;           // the PWM pin the LED is attached to
int led3 = 6;           // the PWM pin the LED is attached to
int led4 = 9;           // the PWM pin the LED is attached to
int led5 = 10;           // the PWM pin the LED is attached to
int led6 = 11;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


void setup() {
  pinMode(led1, OUTPUT); // declare pwm pin to be an output:
  pinMode(led2, OUTPUT); // declare pwm pin to be an output:
  pinMode(led3, OUTPUT); // declare pwm pin to be an output:
  pinMode(led4, OUTPUT); // declare pwm pin to be an output:
  pinMode(led5, OUTPUT); // declare pwm pin to be an output:
  pinMode(led6, OUTPUT); // declare pwm pin to be an output:


}

void loop() {
  analogWrite(led1, brightness); // set the brightness of led
  analogWrite(led2, brightness+1); // set the brightness of led
  analogWrite(led3, brightness+2); // set the brightness of led
  analogWrite(led4, brightness+3); // set the brightness of led
  analogWrite(led5, brightness+4); // set the brightness of led
  analogWrite(led6, brightness+5); // set the brightness of led
  

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }  
  delay(100);  // wait for 30 milliseconds to see the dimming effect
}