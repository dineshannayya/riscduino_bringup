/*************************************************************
  Connection Setting of RoboMart Line Follower Development Kit
  Reference: https://www.scribd.com/document/238827643/User-Manual-IBOT-Mini-V3#

LEDs  ---@----------------> PB1  - D9   -->  Output
LEDs  ---@----------------> PB2  - D10  -->  Output
LEDs  ---@----------------> PB3  - D11  -->  Output
LEDs  ---@----------------> PB4  - D12  -->  Output
Left Sensor  -------------> PC3 -  A3/D17   -->  Input
Right Sensor -------------> PC0 -  A0/D14   -->  Input
Buzzer       -------------> PD4 -  D4   ---> Output
Right Motor (+) ----------> PB1  - D9   ---> Output
Right Motor (-) ----------> PB2  - D10  ---> Output
Left Motor (-) ----------> PB3  - D11  ---> Output
Left Motor (+) ----------> PB4  - D12  ---> Output
Buzzer          ----------> PD4  - D4   ---> Output
RESET --------------------> PC6  - RESET
Crystall Oscialltor (12Mhz) --> PB6 and PB7
VB = Battery Supply
VCC = Regulated 5V+
Gnd = Gnd (0V)
*************************************************************/
//#include "wiring_digital.h"

#define RIGHT_MOTOR_P 9
#define RIGHT_MOTOR_N 10
#define LEFT_MOTOR_N 11
#define LEFT_MOTOR_P 12
#define LEFT_SENSOR 17
#define RIGHT_SENSOR 14
#define BUZZER 4

int BuzzerValue = 0x00;
/**
// To avoid cycle gap between each motor config bit
// We are wtite all the bit in one cycle
void Motor_Write(uint32_t right_motor_p, 
                 uint32_t right_motor_n,
                 uint32_t left_motor_p, 
                 uint32_t left_motor_n)
{
   
    int Gpio_oData = gpioRead();

  if (right_motor_p)
    Gpio_oData |=  digitalPinToBitMask(RIGHT_MOTOR_P);
  else
    Gpio_oData &= ~digitalPinToBitMask(RIGHT_MOTOR_P);

  if (right_motor_n)
    Gpio_oData |=  digitalPinToBitMask(RIGHT_MOTOR_N);
  else
    Gpio_oData &= ~digitalPinToBitMask(RIGHT_MOTOR_N);

  if (left_motor_p)
    Gpio_oData |=  digitalPinToBitMask(LEFT_MOTOR_P);
  else
    Gpio_oData &= ~digitalPinToBitMask(LEFT_MOTOR_P);

  if (left_motor_n)
    Gpio_oData |=  digitalPinToBitMask(LEFT_MOTOR_N);
  else
    Gpio_oData &= ~digitalPinToBitMask(LEFT_MOTOR_N);

    gpioWrite(Gpio_oData);

}
**/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Motor
  pinMode(RIGHT_MOTOR_P, OUTPUT);
  pinMode(RIGHT_MOTOR_N, OUTPUT);
  pinMode(LEFT_MOTOR_N, OUTPUT);
  pinMode(LEFT_MOTOR_P, OUTPUT);

  // Buzer
  pinMode(BUZZER, OUTPUT);
  // Sensor
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // Stop Motor
  digitalWrite(RIGHT_MOTOR_P, HIGH);
  digitalWrite(RIGHT_MOTOR_N, HIGH);
  digitalWrite(LEFT_MOTOR_N, HIGH);
  digitalWrite(LEFT_MOTOR_P, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int LeftSensorVal = digitalRead(LEFT_SENSOR);
  int RightSensorVal = digitalRead(RIGHT_SENSOR);

  // When both Sensor Off , Then Stop Motor
  if (LeftSensorVal == 0 && RightSensorVal == 1) {
    digitalWrite(RIGHT_MOTOR_P, HIGH);
    digitalWrite(RIGHT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_P, HIGH);
    // Motor_Write(HIGH,HIGH,HIGH,HIGH);
    //BuzzerValue = LOW;
    //Serial.print("Right Sensor On\n");
  }

  // Turn Right
  if (LeftSensorVal == 0 && RightSensorVal == 0) {
    digitalWrite(RIGHT_MOTOR_P, LOW);
    digitalWrite(RIGHT_MOTOR_N, LOW);
    digitalWrite(LEFT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_P, LOW);
    // Motor_Write(LOW,LOW,LOW,HIGH);
    // BuzzerValue = HIGH;
    //Serial.print("Left & Right Sensor On\n");
  }

  // Turn Left
  if (LeftSensorVal == 1 && RightSensorVal == 1) {
    digitalWrite(RIGHT_MOTOR_P, LOW);
    digitalWrite(RIGHT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_N, LOW);
    digitalWrite(LEFT_MOTOR_P, LOW);
    //Motor_Write(LOW,HIGH,LOW,LOW);
    //Serial.print("Left & Right Sensor Off\n");
    // BuzzerValue = HIGH;
  }

  // Turn Move Forward
  if (LeftSensorVal == 1 && RightSensorVal == 0) {
    digitalWrite(RIGHT_MOTOR_P, LOW);
    digitalWrite(RIGHT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_N, HIGH);
    digitalWrite(LEFT_MOTOR_P, LOW);
    // Motor_Write(LOW,HIGH,LOW,HIGH);
    // BuzzerValue = ~BuzzerValue;
    //Serial.print("Left Sensor On\n");
  }
  BuzzerValue = ~BuzzerValue;
  digitalWrite(BUZZER, BuzzerValue);
}
