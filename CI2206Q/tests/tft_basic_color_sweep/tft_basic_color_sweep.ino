
//***************************************************
//***************************************************
//Property of: www.microcontroller-project.com     **
//Date       : 6-October-2015                      **
//By         : Usman Ali Butt                      **
//***************************************************
//***************************************************
// Reference: https://www.engineersgarage.com/displaying-text-on-tft-lcd/

//#include <MCUFRIEND_kbv.h>
void IndexRegister(char Com);//Specifying Index of register
void InitializeTFT();//Initializing TFT

int Lcd_RD=A0;
int Lcd_WR=A1;
int Lcd_RS=A2;    //TFT Controlling Pins
int Lcd_CS=A3;
int Lcd_RST=A4;

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

//MCUFRIEND_kbv tft;

#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFC9F


void setup()
{


Serial.begin(9600);
//Serial.print("TFT size is ");
//Serial.print(tft.width());
//Serial.print("x");
//Serial.println(tft.height());

DDRD=B11111111;//Port-D as Output
DDRB=B11111111;//Port-B as Output
pinMode(Lcd_RD,OUTPUT);
pinMode(Lcd_WR,OUTPUT);
pinMode(Lcd_RS,OUTPUT);
pinMode(Lcd_CS,OUTPUT);
pinMode(Lcd_RST,OUTPUT);

//tft.reset();
//uint16_t identifier = tft.readID();
//Serial.print("TFT Identifer ");
//Serial.println(identifier);




digitalWrite(Lcd_WR,HIGH);
digitalWrite(Lcd_RD,HIGH);//In Write Mode
digitalWrite(Lcd_RST,HIGH);//No Reset, For reseting Lcd, make LOW
digitalWrite(Lcd_CS,LOW);//Select Lcd
InitializeTFT();//Initialize TFT
}

void IndexRegister(char Com)
{
PORTD=Com;
PORTB=Com;
//digitalWrite(Lcd_RD,HIGH);//In Write Mode
digitalWrite(Lcd_RS,LOW);//Data on Bus is Register-Index
digitalWrite(Lcd_WR,LOW);//Enable High for some tim
digitalWrite(Lcd_WR,HIGH);
}

void CommandData(char Com){
PORTD=Com;
PORTB=Com;
//digitalWrite(Lcd_RD,HIGH);//In Write Mode
digitalWrite(Lcd_RS,HIGH);//Data on Bus is Command/Data
digitalWrite(Lcd_WR,LOW);//Enable High for some time
digitalWrite(Lcd_WR,HIGH);
}

void fastDisplay(char Com){
PORTD=Com;
PORTB=Com;
digitalWrite(Lcd_WR,LOW);//Enable High for some time
digitalWrite(Lcd_WR,HIGH);
}


void InitializeTFT(){
int i=0,j=0;

char IR_Command[270]={     //Partial Image display commands are not included in this initialization
0x00,0x01,0x01,0x00,    
0x00,0x02,0x07,0x00,    
0x00,0x03,0x10,0x30,//Sets the direction of display    
0x00,0x08,0x03,0x02,    
0x00,0x09,0x00,0x00,   
0x00,0x0A,0x00,0x08,    
//*******POWER CONTROL REGISTER INITIAL*******//    
0x00,0x10,0x07,0x90,    
0x00,0x11,0x00,0x05,    
0x00,0x12,0x00,0x00,   
0x00,0x13,0x00,0x00,     
//********POWER SUPPPLY STARTUP 1 SETTING*******//    
0x00,0x10,0x12,0xB0,    
0x00,0x11,0x00,0x07,      
//********POWER SUPPLY STARTUP 2 SETTING******//    
0x00,0x12,0x00,0x8C,    
0x00,0x13,0x17,0x00,    
0x00,0x29,0x00,0x22,       
//******GAMMA CLUSTER SETTING******//    
0x00,0x30,0x00,0x00,    
0x00,0x31,0x05,0x05,    
0x00,0x32,0x02,0x05,    
0x00,0x35,0x02,0x06,    
0x00,0x36,0x04,0x08,    
0x00,0x37,0x00,0x00,    
0x00,0x38,0x05,0x04,
0x00,0x39,0x02,0x06,    
0x00,0x3C,0x02,0x06,    
0x00,0x3D,0x04,0x08, 
// -----------DISPLAY WINDOWS 240*320-------------//    
0x00,0x50,0x00,0x00,
0x00,0x51,0x00,0xEF,   
0x00,0x52,0x00,0x01,   
0x00,0x53,0x01,0x3F,   
//-----FRAME RATE SETTING-------//    
0x00,0x60,0xA7,0x00,   
0x00,0x61,0x00,0x01,   
0x00,0x90,0x00,0x33, //RTNI setting
//-------DISPLAY ON------//    
0x00,0x07,0x01,0x33,  0x00,0x01,0x01,0x00,      
0x00,0x02,0x07,0x00,    
0x00,0x03,0x10,0x30,    
0x00,0x08,0x03,0x02,    
0x00,0x09,0x00,0x00,   
0x00,0x0A,0x00,0x08,    
//*******POWER CONTROL REGISTER INITIAL*******//    
0x00,0x10,0x07,0x90,    
0x00,0x11,0x00,0x05,    
0x00,0x12,0x00,0x00,   
0x00,0x13,0x00,0x00,   
//********POWER SUPPPLY STARTUP 1 SETTING*******//    
0x00,0x10,0x12,0xB0,      
0x00,0x11,0x00,0x07,     
//********POWER SUPPLY STARTUP 2 SETTING******//    
0x00,0x12,0x00,0x8C,    
0x00,0x13,0x17,0x00,    
0x00,0x29,0x00,0x22,       
//******GAMMA CLUSTER SETTING******//    
0x00,0x30,0x00,0x00,    
0x00,0x31,0x05,0x05,    
0x00,0x32,0x02,0x05,    
0x00,0x35,0x02,0x06,    
0x00,0x36,0x04,0x08,    
0x00,0x37,0x00,0x00,    
0x00,0x38,0x05,0x04,
0x00,0x39,0x02,0x06,    
0x00,0x3C,0x02,0x06,    
0x00,0x3D,0x04,0x08,     
// -----------DISPLAY WINDOWS 240*320-------------//    
0x00,0x50,0x00,0x00,//Start of Horizontal adress area
0x00,0x51,0x00,0xEF,//Ends Horizontal adress area   
0x00,0x52,0x00,0x01,//Start of Vertical adress area   
0x00,0x53,0x01,0x3F,//Ends Vertical adress area   
//-----FRAME RATE SETTING-------//    
0x00,0x60,0xA7,0x00,   
0x00,0x61,0x00,0x01,   
0x00,0x90,0x00,0x33, //RTNI setting
//-------DISPLAY ON------//    
0x00,0x07,0x01,0x33
};

  

for(i=0;i<=sizeof(IR_Command);i=i+4){
IndexRegister(IR_Command[i]);
IndexRegister(IR_Command[i+1]);
CommandData(IR_Command[i+2]);
CommandData(IR_Command[i+3]);
}
}

void TftPaint(int color){
  int i=0,j=0;
  IndexRegister(0x00);//Writing Data/Colour To DRAM 
  IndexRegister(0x22);//Writing Data/Colour To DRAM
  CommandData(color>>8);
  CommandData(color);
  
    for(i=0;i<319;i++){
      for(j=0;j<=239;j++){
        fastDisplay(color>>8);
        fastDisplay(color);
                          }
    }
}

void PaintLcd(){
  TftPaint(TFT_BLACK);
  TftPaint(TFT_NAVY);
  TftPaint(TFT_DARKGREEN);
  TftPaint(TFT_DARKCYAN);
  TftPaint(TFT_MAROON);
  TftPaint(TFT_PURPLE);
  TftPaint(TFT_OLIVE);
  TftPaint(TFT_LIGHTGREY);
  TftPaint(TFT_DARKGREY);
  TftPaint(TFT_BLUE);
  TftPaint(TFT_GREEN);
  TftPaint(TFT_CYAN);
  TftPaint(TFT_RED);
  TftPaint(TFT_MAGENTA);
  TftPaint(TFT_YELLOW);
  TftPaint(TFT_WHITE);
  TftPaint(TFT_ORANGE);
  TftPaint(TFT_GREENYELLOW);
  TftPaint(0x07E0);//Green
  TftPaint(0x001F);//Blue
  TftPaint(24567);//PAle Yellow
  }

void loop(){ 
 /*
 IndexRegister(0x00);
 IndexRegister(0x20);
 CommandData(0x00);    // 20 and 21 registers are used when 
 CommandData(0x08);    //  AM=1(REG3h)
 
 IndexRegister(0x00);
 IndexRegister(0x21);
 CommandData(0x00);
 CommandData(0x09);*/
  
///////////////Vertical display////////
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x80);   
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x90);
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0xA0);
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0xB0);
 PaintLcd();
 ///////////////Vertical display////////

///////////////Horizontal display////////
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x08);   
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x19);
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x2A);
 PaintLcd();
 IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display 
 CommandData(0x10);CommandData(0x3B);
 PaintLcd();
///////////////Horizontal display////////
}