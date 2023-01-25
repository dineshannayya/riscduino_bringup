#include "defs.h"
#include "gpio_config_io.c"
#include "send_packet.c"

// --------------------------------------------------------

/*
 *	User Project IO Control by Bit-bang Method Test
 */



void shift_all();
void shift_data();
char shift_bit(bool,bool );
void shift_load();
void shift_clk(char iCmd);

//---------------------------------------------------------------------------------------------
//iSkipFlag = Individual bit high indicate, we need to skip one cycle for corresponding chain
//  Valid Range = 0x00000 to 3FFFF  (Each chain is 19 bit Long) 
//  Each bit High indicate which chain-no need to be skiped
//  Example = 
//     0x00002  - Chain-1 Need to Skeped
//     0x00042  - Chain-6 & Chain-1 Need to Skeped
//     0x00042  - Chain-16 & Chain-6 & Chain-1 Need to Skeped
//---------------------------------------------------------------------------

int  iSkipFlag1 = 0x42112; // Chain No - 0 to 18 , i.e bit[0] = chain-0, bit[18] = chain-18
int  iSkipFlag2 = 0x14884; // Chain No - 37 to 19, i.e bit[0] = chain-37,bit[18] = chain-19


//-------------------------------------------------------------------------
// iSkipCnt = Indicate total number of cycle need to be skiped
//  
//   1. Initially, we will add iSkipCnt number of dummy shift cycle without data bit
//   2. In Actial Chain Bit Shift cycle 0 time, we will drop/skip first bit 
//      for corresponding chain as indicated by iSkipFlag
//-------------------------------------------------------------------------

char iSkipCnt1 = 0x5; // How Many Cycle need to Skip for chain-1
char iSkipCnt2 = 0x5; // How Many Cycle need to Skip for chain-2

int iCfg1 = 0x1801;
int iCfg2 = 0x1801;

int TotalShiftCnt = 0;
char Bcnt1        = 0; // Actual bit count, without account dummy cycle
char Bcnt2        = 0; // Actual bit count, without account dummy cycle
char ChainNum1    = 0;
char ChainNum2    = 0;

#define TOTAL_PADS_PER_CHAIN 19

void set_registers() {

    reg_mprj_io_0 = GPIO_MODE_MGMT_STD_ANALOG;
    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_7 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
//    reg_mprj_io_34 = 0x0403;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
//    reg_mprj_io_37 = 0x0403;

}
/*

@ start of test  after configuration
    send packet with size = 1
@ send 4 pulses at gpio[0]  
    send packet with size = 2
@ send 4 pulses at gpio[1]  
    send packet with size = 3
@ send 4 pulses at gpio[2]  
    send packet with size = 4
@ send 4 pulses at gpio[3]  
    send packet with size = 5
@ send 4 pulses at gpio[4]  
    send packet with size = 6
@ send 4 pulses at gpio[5]  
    send packet with size = 7
@ send 4 pulses at gpio[6]  
    send packet with size = 8
@ send 4 pulses at gpio[7]  
    send packet with size = 9
@ send 4 pulses at gpio[8]  
    send packet with size = 10


@ reset pulses
    send packet with size = 1
@ send 4 pulses at gpio[9]  
    send packet with size = 2
@ send 4 pulses at gpio[10]  
    send packet with size = 3
@ send 4 pulses at gpio[11]  
    send packet with size = 4
@ send 4 pulses at gpio[12]  
    send packet with size = 5
@ send 4 pulses at gpio[13]  
    send packet with size = 6
@ send 4 pulses at gpio[14]  
    send packet with size = 7
@ send 4 pulses at gpio[15]  
    send packet with size = 8
@ send 4 pulses at gpio[16]  
    send packet with size = 9
@ send 4 pulses at gpio[17]  
    send packet with size = 10
@ send 4 pulses at gpio[18]  
    send packet with size = 11

@ test finish 
    send packet with size = 1
    send packet with size = 1
    send packet with size = 1


*/
void main()
{
	int i,j;
    int num_pulses = 4;

    reg_hkspi_disable = 1;
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    set_registers();
    reg_mprj_datah = 0;
    reg_mprj_datal = 0;
    shift_all();

    reg_gpio_out = 1; // OFF

    while (1){
        reg_gpio_out = 0; // ON
        send_packet_io0(2); // send 4 pulses at gpio[j]
        for (i = 0; i < num_pulses; i++){
            reg_mprj_datal = 0xFFFFFFFF;
            reg_mprj_datah = 0x3F;
            count_down(PULSE_WIDTH);  
            reg_mprj_datah = 0x0;
            reg_mprj_datal = 0x0;  
            count_down(PULSE_WIDTH); 
        }
        reg_gpio_out = 1; // OFF
        delay(4000000);
    }

}


void shift_all() {
  int ShiftCnt;
  reg_mprj_xfer = 0x66; // Data = 0x01 (enable bit-bang mode)

  // Chain-0 : 0 to 18
  // Chain-1 : 37 to 19
  for(ShiftCnt =0; ShiftCnt < (TOTAL_PADS_PER_CHAIN * 13); ShiftCnt++) {
     //reg_mprj_io_32 = (TOTAL_PADS_PER_CHAIN * 13);
     //reg_mprj_io_33 = ShiftCnt;
     //reg_mprj_io_34 = Bcnt1;
     //reg_mprj_io_35 = Bcnt2;
     shift_data();
  //
  }


  shift_load();


}

//-------------------------------------------------
// This Chain will Shift 13 bit data a chain
//-------------------------------------------------
void shift_data() {
   char iCmd;
   char Bcnt; // Bit Count
   bool bDummyCycle1,bDummyCycle2;

  // Clock 12 times.  Set data when clock is zero.
  // (NOTE:  Bits moved up by 1 compared to previous caravel version.
  //  the testbench was updated by bit shifting all the data up by 1.)
  // Bits: (0 = serial xfer)
  //	      1 = bit-bang enable
  //	      2 = bit-bang resetn
  //	      3 = bit-bang load
  //	      4 = bit-bang clock
  //	      5 = bit-bang data user 1
  //	      6 = bit-bang data user 2

    bDummyCycle1 = false;
    bDummyCycle2 = false;
    // Chain-1
    // Insert Dummy Shift Cycle
    if(iSkipCnt1 > TotalShiftCnt) {
        bDummyCycle1 = true;
    } else {
        // Skip only for first cycle for failing chain
        if(Bcnt1 == 12) { 
           if(iSkipFlag1 & (1 << (TOTAL_PADS_PER_CHAIN-1-ChainNum1))) {
             // Skip data without Shifting it
             if(iCfg1 & 0x1000)
                iCfg1 = iCfg1 << 1 | 0x01;
             else
                iCfg1 = iCfg1 << 1 ;
             Bcnt1 = 0;
             ChainNum1++;
          }
        }
   }

   // Chain-2
   if(iSkipCnt2 > TotalShiftCnt) {
       bDummyCycle2 = true;
   } else {
        if(Bcnt2 == 12) { 
           if(iSkipFlag2 & (1 << (TOTAL_PADS_PER_CHAIN-1-ChainNum2))) {
              // Skip data without Shifting it
              if(iCfg2 & 0x1000)
                 iCfg2 = iCfg2 << 1 | 0x01;
              else
                 iCfg2 = iCfg2 << 1 ;

              Bcnt2 = 0;
              ChainNum2++;
          }
      }    
   }
   iCmd = shift_bit(bDummyCycle1,bDummyCycle2 );
   shift_clk(iCmd);
   // Increment Shift Cnt
   TotalShiftCnt++;
   // load the currently shifted 13 bit data
   //shift_load();
}

//------------------
// shifted Data bit 
//---------------------
char shift_bit(bool sBypass1, bool sBypass2) {

   char iCmd;
   char iData1,iData2;

   // Chain-1 Data
   if(iCfg1 & 0x1000)
      iData1 = 0x20; // Data = 1
   else
      iData1 = 0x00; // Data = 0

   
   // Chain-2 Data
   if(iCfg2 & 0x1000)
      iData2 = 0x40; // Data = 1
   else
      iData2 = 0x00; // Data = 0
   
   iCmd = 0x06;
   iCmd = iCmd | iData1 | iData2;
      
   reg_mprj_xfer = iCmd ;        // Set Data 
  
   // update data for Next Shift 
   if(sBypass1 == false) {
       if(iCfg1 & 0x1000)
          iCfg1 = iCfg1 << 1 | 0x01;
       else
          iCfg1 = iCfg1 << 1 ;

       if(Bcnt1 == 12) { Bcnt1 = 0; ChainNum1++; }
       else  Bcnt1++;
    }

   if(sBypass2 == false) {
       if(iCfg2 & 0x1000)
          iCfg2 = iCfg2 << 1 | 0x01;
       else
          iCfg2 = iCfg2 << 1;

        if(Bcnt2 == 12) { Bcnt2 = 0; ChainNum2++; }
        else  Bcnt2++;
   }

  return iCmd;

}

//------------------
// Load the shifted Data
//---------------------
void shift_load() {

  reg_mprj_xfer = 0x0e; // Load
  reg_mprj_xfer = 0x06; // 

}

//-----------------------
// Toggle the clock
//-------------------
void shift_clk(char iCmd) {

  reg_mprj_xfer = iCmd | 0x10; // Clock=1
  reg_mprj_xfer = iCmd ;       // Clock=0

}
