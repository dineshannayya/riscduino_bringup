int led = 3;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


#define reg_pwm0_low_cfg   (*(volatile uint16_t*)0x10020104)
#define reg_pwm0_high_cfg  (*(volatile uint16_t*)0x10020106)

#define reg_pwm1_low_cfg   (*(volatile uint16_t*)0x10020108)
#define reg_pwm1_high_cfg  (*(volatile uint16_t*)0x1002010A)

#define reg_pwm2_low_cfg   (*(volatile uint16_t*)0x1002010C)
#define reg_pwm2_high_cfg  (*(volatile uint16_t*)0x1002010E)

#define reg_pwm3_low_cfg   (*(volatile uint16_t*)0x10020110)
#define reg_pwm3_high_cfg  (*(volatile uint16_t*)0x10020112)

#define reg_pwm4_low_cfg   (*(volatile uint16_t*)0x10020114)
#define reg_pwm4_high_cfg  (*(volatile uint16_t*)0x10020116)

#define reg_pwm5_low_cfg   (*(volatile uint16_t*)0x10020118)
#define reg_pwm5_high_cfg  (*(volatile uint16_t*)0x1002011A)


#define reg_timer_cfg      (*(volatile uint32_t*)0x10020180)


#define reg_glbl_multi_func (*(volatile uint32_t*)0x10020014)

void setup() {
  //pinMode(led, OUTPUT); // declare pwm pin to be an output:
  //Serial.begin(9600);

  //Serial.println("PWN Test Started");

  		// config 1us based on system clock - 1000/100ns = 10 
        reg_timer_cfg = 1;
      // Enable PWM Multi Functional Ports
        reg_glbl_multi_func |= 0x03F;
        //Serial.print("Glbl Multi Func:");
        //Serial.println(reg_glbl_multi_func);

        reg_pwm0_low_cfg  = 0x0001;
        reg_pwm0_high_cfg = 0x0001;
        reg_pwm1_low_cfg  = 0x0000;
        reg_pwm1_high_cfg = 0x0000;
        reg_pwm2_low_cfg  = 0x0000;
        reg_pwm2_high_cfg = 0x0000;
        reg_pwm3_low_cfg  = 0x0000;
        reg_pwm3_high_cfg = 0x0000;
        reg_pwm4_low_cfg  = 0x0000;
        reg_pwm4_high_cfg = 0x0000;
        reg_pwm5_low_cfg  = 0x0000;
        reg_pwm5_high_cfg = 0x0000;

        

}

void loop() {
  //analogWrite(led, brightness); // set the brightness of led
  reg_pwm0_high_cfg = brightness;
  reg_pwm0_low_cfg = (255-brightness-1) & 0xFF;
  //Serial.print("pwm0 High Value:");
  //Serial.println(reg_pwm0_high_cfg);
  //Serial.print("pwm0 High Value:");
  //Serial.println(reg_pwm0_low_cfg);
  

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }  
  delay(100);  // wait for 30 milliseconds to see the dimming effect
}