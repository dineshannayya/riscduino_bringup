// adapted from LCD_ID_Reader from http://misc.ws/lcd_information
// controllers either read as 16-bit or as a sequence of 8-bit values

//-- Arduino UNO or Mega 2560 Plugged as shield
#define LCD_RST A4
#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_D0 8
#define LCD_D1 9
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

   //LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
   //AVR   pin |PD7|PD6|PD5|PD4|PD3|PD2|PB1|PB0| |PC0|PC1|PC2|PC3|PC4|
   //UNO pins  |7  |6  |5  |4  |3  |2  |9  |8  | |A0 |A1 |A2 |A3 |A4 |
   #define RD_PORT PORTC
   #define RD_PIN  0
   #define WR_PORT PORTC
   #define WR_PIN  1
   #define CD_PORT PORTC
   #define CD_PIN  2
   #define CS_PORT PORTC
   #define CS_PIN  3
   #define RESET_PORT PORTC
   #define RESET_PIN  4
   
   #define BMASK         0x03              //more intuitive style for mixed Ports
   #define DMASK         0xFC              //does exactly the same as previous
   #define write_8(x)    { PORTB = (PORTB & ~BMASK) | ((x) & BMASK); PORTD = (PORTD & ~DMASK) | ((x) & DMASK); }
   #define read_8()      ( (PINB & BMASK) | (PIND & DMASK) )
   #define setWriteDir() { DDRB |=  BMASK; DDRD |=  DMASK; }
   #define setReadDir()  { DDRB &= ~BMASK; DDRD &= ~DMASK; }
   #define write8(x)     { write_8(x); WR_STROBE; }
   #define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
   #define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
   #define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
   
   #define PIN_LOW(p, b)        (p) &= ~(1<<(b))
   #define PIN_HIGH(p, b)       (p) |= (1<<(b))
   #define PIN_OUTPUT(p, b)     (p) |= (1<<(b))



#define RD_ACTIVE  PIN_LOW(RD_PORT, RD_PIN)
#define RD_IDLE    PIN_HIGH(RD_PORT, RD_PIN)
#define RD_OUTPUT  PIN_OUTPUT(DDRC, RD_PIN)
#define WR_ACTIVE  PIN_LOW(WR_PORT, WR_PIN)
#define WR_IDLE    PIN_HIGH(WR_PORT, WR_PIN)
#define WR_OUTPUT  PIN_OUTPUT(DDRC, WR_PIN)
#define CD_IDLE  PIN_HIGH(CD_PORT, CD_PIN)
#define CD_COMMAND PIN_LOW(CD_PORT, CD_PIN)
#define CD_DATA    PIN_HIGH(CD_PORT, CD_PIN)
#define CD_OUTPUT  PIN_OUTPUT(DDRC, CD_PIN)
#define CS_ACTIVE  PIN_LOW(CS_PORT, CS_PIN)
#define CS_IDLE    PIN_HIGH(CS_PORT, CS_PIN)
#define CS_OUTPUT  PIN_OUTPUT(DDRC, CS_PIN)
#define RESET_ACTIVE  PIN_LOW(RESET_PORT, RESET_PIN)
#define RESET_IDLE    PIN_HIGH(RESET_PORT, RESET_PIN)
#define RESET_OUTPUT  PIN_OUTPUT(DDRC, RESET_PIN)

 // General macros.   IOCLR registers are 1 cycle when optimised.
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }       //PWLW=TWRL=50ns
#define RD_STROBE RD_IDLE, RD_ACTIVE, RD_ACTIVE, RD_ACTIVE      //PWLR=TRDL=150ns, tDDR=100ns

#define CTL_IDLE()   { RD_IDLE; WR_IDLE; CD_IDLE; CS_IDLE; RESET_IDLE; }
#define CTL_INIT()   { RD_OUTPUT; WR_OUTPUT; CD_OUTPUT; CS_OUTPUT; RESET_OUTPUT; }
#define WriteCmd(x)  { CD_COMMAND; write16(x); CD_DATA; }
#define WriteData(x) { write16(x); }

#define reg_gpio_dsel         (*(volatile uint32_t*)0x10020080)  // reg_0  - GPIO Direction Select
#define reg_gpio_type         (*(volatile uint32_t*)0x10020084)  // reg_1  - GPIO TYPE - Static/Waveform
#define reg_gpio_idata        (*(volatile uint32_t*)0x10020088)  // reg_2  - GPIO Data In
#define reg_gpio_odata        (*(volatile uint32_t*)0x1002008C)  // reg_3  - GPIO Data Out
#define reg_gpio_intr_stat    (*(volatile uint32_t*)0x10020090)  // reg_4  - GPIO Interrupt status
#define reg_gpio_intr_clr     (*(volatile uint32_t*)0x10020090)  // reg_5  - GPIO Interrupt Clear
#define reg_gpio_intr_set     (*(volatile uint32_t*)0x10020094)  // reg_6 - GPIO Interrupt Set
#define reg_gpio_intr_mask    (*(volatile uint32_t*)0x10020098)  // reg_7 - GPIO Interrupt Mask
#define reg_gpio_pos_intr     (*(volatile uint32_t*)0x1002009C)  // reg_8 - GPIO Posedge Interrupt
#define reg_gpio_neg_intr     (*(volatile uint32_t*)0x100200A0)  // reg_9 - GPIO Neg Interrupt


void setup()
{
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("Read Registers on MCUFRIEND UNO shield");
    Serial.println("controllers either read as single 16-bit");
    Serial.println("e.g. the ID is at readReg(0)");
    Serial.println("or as a sequence of 8-bit values");
    Serial.println("in special locations (first is dummy)");
    Serial.println("");
    lcdInit();
    lcdReset();      //ensures that controller is in default state
//    for (uint16_t i = 0; i < 256; i++) readReg(i, 7, "f.k"); 
    readReg(0x00, 2, "ID: ILI9320, ILI9325, ILI9335, ...");
    readReg(0x04, 4, "Manufacturer ID");
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Power Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x61, 2, "RDID1 HX8347-G");
    readReg(0x62, 2, "RDID2 HX8347-G");
    readReg(0x63, 2, "RDID3 HX8347-G");
    readReg(0x64, 2, "RDID1 HX8347-A");
    readReg(0x65, 2, "RDID2 HX8347-A");
    readReg(0x66, 2, "RDID3 HX8347-A");
    readReg(0x67, 2, "RDID Himax HX8347-A");
    readReg(0x70, 2, "Panel Himax HX8347-A");
    readReg(0xA1, 5, "RD_DDB SSD1963");
    readReg(0xB0, 2, "RGB Interface Signal Control");
    readReg(0xB4, 2, "Inversion Control");
    readReg(0xB6, 5, "Display Control");
    readReg(0xB7, 2, "Entry Mode Set");
    readReg(0xBF, 6, "ILI9481, HX8357-B");
    readReg(0xC0, 9, "Panel Control");
    readReg(0xC8, 13, "GAMMA");
    readReg(0xCC, 2, "Panel Control");
    readReg(0xD0, 3, "Power Control");
    readReg(0xD2, 5, "NVM Read");
    readReg(0xD3, 4, "ILI9341, ILI9488");
    readReg(0xD4, 4, "Novatek ID");
    readReg(0xDA, 2, "RDID1");
    readReg(0xDB, 2, "RDID2");
    readReg(0xDC, 2, "RDID3");
    readReg(0xE0, 16, "GAMMA-P");
    readReg(0xE1, 16, "GAMMA-N");
    readReg(0xEF, 6, "ILI9327");
    readReg(0xF2, 12, "Adjust Control 2");
    readReg(0xF6, 4, "Interface Control");
}

void loop() 
{
    // put your main code here, to run repeatedly:

}

void printhex(uint8_t val)
{
    if (val < 0x10) Serial.print("0");
    Serial.print(val, HEX);
}

void readReg(uint16_t reg, uint8_t n, const char *msg)
{
    uint8_t val8;
    lcdReset();
    lcdSetWriteDir();
    lcdWriteCommand(0xB0);     //Command Access Protect
    lcdWriteData(0x00);        //looks wrong
/*
    lcdWriteCommand(0xF6);
    lcdWriteData(0x01);
    lcdWriteData(0x01);
    lcdWriteData(0x03);
*/
    lcdWriteCommand(reg);
    Serial.print("reg(0x");
    printhex(reg >> 8);
    printhex(reg);
    Serial.print(")");
    lcdSetReadDir();
    while (n--) {
        val8 = lcdReadData8();
        Serial.print(" ");
        printhex(val8);
    }
    lcdSetWriteDir();
    Serial.print("\t");
    Serial.println(msg);
}

void lcdInit()
{

    Serial.print("GPIO Direction(Pre):");
    Serial.println(reg_gpio_dsel) ;
    Serial.print("GPIO Type(Pre):");
    Serial.println(reg_gpio_type) ;
    Serial.print("GPIO Output(Pre):");
    Serial.println(reg_gpio_odata) ;
    
    
/*
    digitalWrite(LCD_CS, HIGH);
    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_WR, HIGH);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_RST, HIGH);
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_WR, OUTPUT);
    pinMode(LCD_RD, OUTPUT);
    pinMode(LCD_RST, OUTPUT);
*/  
    CTL_INIT();
    CTL_IDLE();

    Serial.print("GPIO Direction(Post):");
    Serial.println(reg_gpio_dsel) ;
    Serial.print("GPIO Type(Post):");
    Serial.println(reg_gpio_type) ;
    Serial.print("GPIO Output(Post):");
    Serial.println(reg_gpio_odata) ;
    
}

void lcdReset()
{
    digitalWrite(LCD_RST, LOW);
    delay(2);
    digitalWrite(LCD_RST, HIGH);
    delay(10);             //allow controller to re-start
}

void lcdWrite8(uint16_t data)
{
    /**
    digitalWrite(LCD_D0, data & 1);
    digitalWrite(LCD_D1, (data & 2) >> 1);
    digitalWrite(LCD_D2, (data & 4) >> 2);
    digitalWrite(LCD_D3, (data & 8) >> 3);
    digitalWrite(LCD_D4, (data & 16) >> 4);
    digitalWrite(LCD_D5, (data & 32) >> 5);
    digitalWrite(LCD_D6, (data & 64) >> 6);
    digitalWrite(LCD_D7, (data & 128) >> 7);
    **/
    write16(data);
}

uint16_t lcdRead8()
{
    uint16_t result;
    /**
    result = digitalRead(LCD_D7);
    result <<= 1;
    result |= digitalRead(LCD_D6);
    result <<= 1;
    result |= digitalRead(LCD_D5);
    result <<= 1;
    result |= digitalRead(LCD_D4);
    result <<= 1;
    result |= digitalRead(LCD_D3);
    result <<= 1;
    result |= digitalRead(LCD_D2);
    result <<= 1;
    result |= digitalRead(LCD_D1);
    result <<= 1;
    result |= digitalRead(LCD_D0);
    **/
    READ_16(result);

    return result;
}

void lcdSetWriteDir()
{
  
    /**
    pinMode(LCD_D0, OUTPUT);
    pinMode(LCD_D1, OUTPUT);
    pinMode(LCD_D2, OUTPUT);
    pinMode(LCD_D3, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_D7, OUTPUT);
    **/
    setWriteDir();
}


void lcdSetReadDir()
{

    /** 
    pinMode(LCD_D0, INPUT);
    pinMode(LCD_D1, INPUT);
    pinMode(LCD_D2, INPUT);
    pinMode(LCD_D3, INPUT);
    pinMode(LCD_D4, INPUT);
    pinMode(LCD_D5, INPUT);
    pinMode(LCD_D6, INPUT);
    pinMode(LCD_D7, INPUT);
    **/
  
   setReadDir();
}

void lcdWriteData(uint16_t data)
{
    lcdSetWriteDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);

    lcdWrite8(data >> 8);

    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);

    lcdWrite8(data);

    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);

    digitalWrite(LCD_CS, HIGH);
}

void lcdWriteCommand(uint16_t command)
{
    lcdSetWriteDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, LOW);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);
    lcdWrite8(command >> 8);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);
    lcdWrite8(command);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);
    digitalWrite(LCD_CS, HIGH);
}

uint8_t lcdReadData8()
{
    uint8_t result;
   
    lcdSetReadDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);

    digitalWrite(LCD_RD, LOW);
    delayMicroseconds(10);
    result = lcdRead8();
    digitalWrite(LCD_RD, HIGH);

    delayMicroseconds(10);
    digitalWrite(LCD_CS, HIGH);
    
    //READ_8(result);

    return result;
}


uint16_t lcdReadData16()
{
    uint16_t result;
    result = lcdReadData8() << 8;
    result |= lcdReadData8();
    //READ_16(result);
    return result;
}


void lcdWriteRegister(uint16_t addr, uint16_t data)
{
    lcdWriteCommand(addr);
    lcdWriteData(data);
}


