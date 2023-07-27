#define int_reg_tcm            (*(volatile uint32_t*)0x0C480000)    // TCM Register
#define char_reg_tcm           (*(volatile uint8_t*)0x0C480000)    // TCM Register

#define reg_uart0_ctrl         (*(volatile uint32_t*)0x10010000)  // Reg-0
#define reg_uart0_intr_stat    (*(volatile uint32_t*)0x10010004)  // Reg-1
#define reg_uart0_baud_ctrl1   (*(volatile uint32_t*)0x10010008)  // Reg-2
#define reg_uart0_baud_ctrl2   (*(volatile uint32_t*)0x1001000C)  // Reg-3
#define reg_uart0_status       (*(volatile uint32_t*)0x10010010)  // Reg-4
#define reg_uart0_txdata       (*(volatile uint32_t*)0x10010014)  // Reg-5
#define reg_uart0_rxdata       (*(volatile uint32_t*)0x10010018)  // Reg-6
#define reg_uart0_txfifo_stat  (*(volatile uint32_t*)0x1001001C)  // Reg-7
#define reg_uart0_rxfifo_stat  (*(volatile uint32_t*)0x10010020)  // Reg-8

#define BIST_DATA_PAT_TYPE1 0x55555555
#define BIST_DATA_PAT_TYPE2 0x33333333
#define BIST_DATA_PAT_TYPE3 0x0F0F0F0F
#define BIST_DATA_PAT_TYPE4 0x00FF00FF
#define BIST_DATA_PAT_TYPE5 0x0000FFFF
#define BIST_DATA_PAT_TYPE6 0xFFFFFFFF
#define BIST_DATA_PAT_TYPE7 0x01010101
#define BIST_DATA_PAT_TYPE8 0x00000000


int hextochar(char iData){

switch(iData) {
case 0 : return '0';
case 1 : return '1';
case 2 : return '2';
case 3 : return '3';
case 4 : return '4';
case 5 : return '5';
case 6 : return '6';
case 7 : return '7';
case 8 : return '8';
case 9 : return '9';
case 0xA : return 'A';
case 0xB : return 'B';
case 0xC : return 'C';
case 0xD : return 'D';
case 0xE : return 'E';
case 0xF : return 'F';
}

return ' ';

}
void print_var(int iData) {

	   Serial.write(hextochar((iData >> 28) & 0xF));
	   Serial.write(hextochar((iData >> 24) & 0xF));
	   Serial.write(hextochar((iData >> 20) & 0xF));
	   Serial.write(hextochar((iData >> 16) & 0xF));
	   Serial.write(hextochar((iData >> 12) & 0xF));
	   Serial.write(hextochar((iData >> 8) & 0xF));
	   Serial.write(hextochar((iData >> 4) & 0xF));
	   Serial.write(hextochar((iData ) & 0xF));
  }

void run_tcm_mem_check(int iPattern,int iMemSize) {

  // put your main code here, to run repeatedly:
int *int_ptr, *int_addr;

int iSum;
int i,j;
int iTxData;
int iRxData;

int_ptr = &int_reg_tcm;

// Write 2K Location in 32 Bit Aligned write and Read
Serial.print("########### Testing TCM Memory in 32 Bit Aligned Write ###########");
Serial.println();

for(j=0; j < iMemSize; j++) {

    for(i=0; i < 32; i++){
      iTxData = iPattern;
      int_addr = int_ptr + (j*32 + i);
      *int_addr = iTxData;
      Serial.print("Writing TCM Reg Addr:");
      print_var(int_addr);
      Serial.print("=> Val:");
      print_var(iTxData);
      Serial.println();
    }
}
Serial.print("########### Testing TCM Memory in 32 Bit Aligned Read Back and Verify-1 ###########");
Serial.println();
for(j=0; j < iMemSize; j++) {
    for(i=0; i < 32; i++){
      iTxData = iPattern;
      int_addr = int_ptr + (j*32 + i);
      iRxData = *int_addr;
      Serial.print("Reading TCM Reg Addr:");
      print_var(int_addr);
      Serial.print("=> TxData:");
      print_var(iTxData);
      Serial.print("=> RxData:");
      print_var(iRxData);      
      if(iTxData == iRxData) Serial.print("=> Matched");
      else Serial.print("=> FAIL");
      Serial.println();
    }
}

Serial.print("########### Testing TCM Memory in 32 Bit Aligned Read Back and Verify-2 ###########");
Serial.println();
for(j=0; j < iMemSize; j++) {
    for(i=0; i < 32; i++){
      iTxData = iPattern;
      int_addr = int_ptr + (j*32 + i);
      iRxData = *int_addr;
      Serial.print("Reading TCM Reg Addr:");
      print_var(int_addr);
      Serial.print("=> TxData:");
      print_var(iTxData);
      Serial.print("=> RxData:");
      print_var(iRxData);      
      if(iTxData == iRxData) Serial.print("=> Matched");
      else Serial.print("=> FAIL");
      Serial.println();
    }
}


}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  run_tcm_mem_check(BIST_DATA_PAT_TYPE1,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE2,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE3,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE4,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE5,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE6,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE7,1);
  run_tcm_mem_check(BIST_DATA_PAT_TYPE8,1);
  
}



void loop() {

/**
Serial.print("########### Testing TCM Memory in 8 Bit Aligned Write and Read ###########");
char_ptr = &char_reg_tcm;
for(j=0; j < 16; j++) {

    for(i=0; i < 32; i++){
      iTxData = 1 << i;
      char_addr = char_ptr + (j*32 + i);
      *char_addr = iTxData;
      Serial.print("Writing TCM Reg Addr:");
      print_var(char_addr);
      Serial.print("=> Val:");
      print_var(iTxData);
      Serial.println();
    }
}
**/
 /***

for(i=0; i < 32; i++){
  reg_tcm_0 = 1 << i;
  Serial.print("Reading TCM Reg-0:");
  print_var(reg_tcm_0);
  if(reg_tcm_0 == 1 << i) Serial.print("=> PASS");
  else Serial.print("=> FAIL");
  Serial.println();

  reg_tcm_1 = 0x80000000 >> i;
  Serial.print("Reading TCM Reg-1:");
  print_var(reg_tcm_1);
  if(reg_tcm_1 == 0x80000000 >> i) Serial.print("=> PASS");
  else Serial.print("=> FAIL");
  Serial.println();
}
**/

}
