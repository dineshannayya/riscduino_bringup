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

int  iSkipFlag1 = 0x0; // Chain No - 0 to 18 , i.e bit[0] = chain-0, bit[18] = chain-18
int  iSkipFlag2 = 0x0; // Chain No - 37 to 19, i.e bit[0] = chain-37,bit[18] = chain-19


//-------------------------------------------------------------------------
// iSkipCnt = Indicate total number of cycle need to be skiped
//  
//   1. Initially, we will add iSkipCnt number of dummy shift cycle without data bit
//   2. In Actial Chain Bit Shift cycle 0 time, we will drop/skip first bit 
//      for corresponding chain as indicated by iSkipFlag
//-------------------------------------------------------------------------

char iSkipCnt1 = 0x0; // How Many Cycle need to Skip for chain-1
char iSkipCnt2 = 0x0; // How Many Cycle need to Skip for chain-2

#define GPIO_MODE_USER_STD_BIDIRECTIONAL          0x0800
int iCfg1 = GPIO_MODE_USER_STD_BIDIRECTIONAL; // 0x1801;
int iCfg2 = GPIO_MODE_USER_STD_BIDIRECTIONAL; // 0x1801;

int TotalShiftCnt = 0;
char Bcnt1        = 0; // Actual bit count, without account dummy cycle
char Bcnt2        = 0; // Actual bit count, without account dummy cycle
char ChainNum1    = 0;
char ChainNum2    = 0;

#define TOTAL_PADS_PER_CHAIN 19

#define reg_mprj_wbhost_reg0      (*(volatile uint32_t*)0x30800000)
#define reg_mprj_wbhost_reg1      (*(volatile uint32_t*)0x30800004)
#define reg_mprj_wbhost_clk_ctrl1 (*(volatile uint32_t*)0x30800008)
#define reg_mprj_wbhost_clk_ctrl2 (*(volatile uint32_t*)0x3080000C)

//assign cfg_cska_wi    = cfg_clk_ctrl1[3:0];     - 0x2
//assign cfg_cska_riscv = cfg_clk_ctrl1[7:4];     - 0xc
//assign cfg_cska_uart  = cfg_clk_ctrl1[11:8];    - 0x8
//assign cfg_cska_spi   = cfg_clk_ctrl1[15:12];   - 0x6
//assign cfg_cska_sdram = cfg_clk_ctrl1[19:16];   - 0x8
//assign cfg_cska_glbl  = cfg_clk_ctrl1[23:20];   - 0x4
//assign cfg_cska_wh    = cfg_clk_ctrl1[27:24];   - 0x8

//assign cfg_cska_sd_co = cfg_clk_ctrl2[3:0]; // SDRAM clock out control
//assign cfg_cska_sd_ci = cfg_clk_ctrl2[7:4]; // SDRAM clock in control
//assign cfg_cska_sp_co = cfg_clk_ctrl2[11:8];// SPI clock out control

void main()
{
	int i,j;
    int num_pulses = 4;

    reg_hkspi_disable = 1;
    reg_spi_enable = 0;
    reg_wb_enable = 1;

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    reg_mprj_datah = 0;
    reg_mprj_datal = 0;
    shift_all();

    reg_gpio_out = 1; // OFF


    reg_mprj_wbhost_clk_ctrl1 = 0x084868c2;

    reg_mprj_wbhost_clk_ctrl2 = 0x00;
    // Remove All Reset
    reg_mprj_wbhost_reg0 = 0x1F;

    delay(4000000);
    reg_gpio_out = 0; // ON

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
