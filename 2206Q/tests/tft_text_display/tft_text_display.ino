//***************************************************
//***************************************************
//Property of: www.microcontroller-project.com     **
//Date       : 30-October-2015                     **
//By         : Usman Ali Butt                      **
//***************************************************
//***************************************************



void IndexRegister(char Com);//Specifying Index of register
void CommandData(char Com);//Sending Commands and Data to TFT
void fastDisplay(char Com);//Displaying Fast Data on TFT
void Char_Display(int width,int index, int height,int color);
void InitializeTFT();//Initializing TFT

int Lcd_RD=A0;
int Lcd_WR=A1;
int Lcd_RS=A2;    //TFT Controlling Pins
int Lcd_CS=A3;
int Lcd_RST=A4;

char arialNarrow_10p[][12] = 
{
  // @0 '-' (3 pixels wide)
  {0x00, //    
  0x00, //    
  0x00, //    
  0x00, //    
  0x00, //    
  0xE0, // ###
  0x00, //    
  0x00, //    
  0x00, //    
  0x00, //    
  0x00, //    
  0x00}, //    

  // @12 '.' (1 pixels wide)
  {0x00, //  
  0x00, //  
  0x00, //  
  0x00, //  
  0x00, //  
  0x00, //  
  0x00, //  
  0x00, //  
  0x80, // #
  0x00, //  
  0x00, //  
  0x00}, //  

  // @24 'c' (4 pixels wide)
  {0x00, //     
  0x00, //     
  0x60, //  ## 
  0x90, // #  #
  0x80, // #   
  0x80, // #   
  0x80, // #   
  0x90, // #  #
  0x60, //  ## 
  0x00, //     
  0x00, //     
  0x00}, //     

  // @36 'e' (5 pixels wide)
  {0x00, //      
  0x00, //      
  0x70, //  ### 
  0x88, // #   #
  0x88, // #   #
  0xF8, // #####
  0x80, // #    
  0x88, // #   #
  0x70, //  ### 
  0x00, //      
  0x00, //      
  0x00}, //      

  // @48 'i' (1 pixels wide)
  {0x80, // #
  0x00, //  
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x00, //  
  0x00, //  
  0x00}, //  

  // @60 'j' (2 pixels wide)
  {0x40, //  #
  0x00, //   
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0x40, //  #
  0xC0}, // ##

  // @72 'l' (1 pixels wide)
  {0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x80, // #
  0x00, //  
  0x00, //  
  0x00}, //  

  // @84 'm' (7 pixels wide)
  {0x00, //        
  0x00, //        
  0xA4, // # #  # 
  0xDA, // ## ## #
  0x92, // #  #  #
  0x92, // #  #  #
  0x92, // #  #  #
  0x92, // #  #  #
  0x92, // #  #  #
  0x00, //        
  0x00, //        
  0x00}, //        

  // @96 'n' (5 pixels wide)
  {0x00, //      
  0x00, //      
  0xB0, // # ## 
  0xC8, // ##  #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x00, //      
  0x00, //      
  0x00}, //      

  // @108 'o' (5 pixels wide)
  {0x00, //      
  0x00, //      
  0x70, //  ### 
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0x70, //  ### 
  0x00, //      
  0x00, //      
  0x00}, //      

  // @120 'p' (5 pixels wide)
  {0x00, //      
  0x00, //      
  0xB0, // # ## 
  0xC8, // ##  #
  0x88, // #   #
  0x88, // #   #
  0x88, // #   #
  0xC8, // ##  #
  0xB0, // # ## 
  0x80, // #    
  0x80, // #    
  0x80}, // #    

  // @132 'r' (3 pixels wide)
  {0x00, //    
  0x00, //    
  0xA0, // # #
  0xC0, // ## 
  0x80, // #  
  0x80, // #  
  0x80, // #  
  0x80, // #  
  0x80, // #  
  0x00, //    
  0x00, //    
  0x00}, //    

  // @144 't' (3 pixels wide)
  {0x40, //  # 
  0x40, //  # 
  0xE0, // ###
  0x40, //  # 
  0x40, //  # 
  0x40, //  # 
  0x40, //  # 
  0x40, //  # 
  0x60, //  ##
  0x00, //    
  0x00, //    
  0x00}, //    

  // @156 'w' (7 pixels wide)
  {0x00, //        
  0x00, //        
  0x92, // #  #  #
  0x92, // #  #  #
  0xAA, // # # # #
  0xAA, // # # # #
  0xAA, // # # # #
  0xAA, // # # # #
  0x44, //  #   # 
  0x00, //        
  0x00, //        
  0x00} //        
};

const char Chars[14]={'-','.','c','e','i','j','l','m','n','o','p','r','t','w'};
const int Char_Width[14]={3,1,4,5,1,2,1,7,5,5,5,3,3,7};
const int Char_Height=12;
int Display_Height=0;
int Display_Width=0;


void setup()
{
DDRD=B11111111;//Port-D as Output
DDRB=B11111111;//Port-B as Output
pinMode(Lcd_RD,OUTPUT);
pinMode(Lcd_WR,OUTPUT);
pinMode(Lcd_RS,OUTPUT);
pinMode(Lcd_CS,OUTPUT);
pinMode(Lcd_RST,OUTPUT);

Serial.begin(9600);
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

for(i=0;i<=sizeof(IR_Command);i=i+4)
{
IndexRegister(IR_Command[i]);IndexRegister(IR_Command[i+1]);
CommandData(IR_Command[i+2]);CommandData(IR_Command[i+3]);
}

}

void TftPaint(int color){
  int i=0,j=0;
  IndexRegister(0x00);IndexRegister(0x22);//Writing Data/Colour To DRAM
  CommandData(color>>8);CommandData(color);
  
    for(i=0;i<=319;i++){
      
      for(j=0;j<=239;j++){
        fastDisplay(color>>8);fastDisplay(color);
                         }
                       }
}



void Char_Display(int width,int index, int height,int color){
  int i=0,j=0;
 IndexRegister(0x00);IndexRegister(0x20);CommandData(0x00);CommandData(Display_Width);                    //X-axis  // 20 and 21 registers 
 IndexRegister(0x00);IndexRegister(0x21);CommandData(Display_Height>>8);CommandData(Display_Height);      //Y-axis
 
 IndexRegister(0x00);IndexRegister(0x50);CommandData(0x00);CommandData(Display_Width);  //Start of Horizontal adress area  
 Display_Width+=width;
 IndexRegister(0x00);IndexRegister(0x51);CommandData(0x00);CommandData(Display_Width);  //Ends Horizontal adress area 

IndexRegister(0x00);IndexRegister(0x22);//Writing Data/Colour To DRAM

for(i=0;i<height;i++){
  
for(j=7;j>=7-width;j--){
 
  if(((arialNarrow_10p[index][i]>>j) & 1)==1)
        {
          CommandData(0x00);CommandData(0x00);
        }
  else  
        {
          CommandData(color>>8);CommandData(color);
        }
  }
}
 Display_Width+=1;
}


void loop(){ 
int i,j,color=0;
char Str[]="www.microcontroller-project.com";
 
IndexRegister(0x00);IndexRegister(0x03);//Sets the direction of display Register
CommandData(0x10);CommandData(0x30);    //Sets the direction of display Command   

TftPaint(65535);//Fill TFT with White Colour

while(1){
i=0;j=0;  
while(strlen(Str)!=i){
  
  for(j=0;j<=13;j++){
          if(Str[i]==Chars[j]){
              Char_Display(Char_Width[j],j,12,color);//Char width,index,height,TFT Back Ground Colour
    }
  }  
  i++;
  }
  
 Display_Height+=12;
 Display_Width=0;
 color+=300;//Changing colour of display
if(Display_Height>=315){Display_Height=0;}

}//End While(1)

}//End Loop