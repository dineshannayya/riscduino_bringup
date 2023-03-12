#include <defs.h>
#include <stub.c>

#include "gpio_config_io.c"
#include "send_packet.c"

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

// --------------------------------------------------------

void print_reg(int iData) {

   putchar((iData) & 0xFF);       // [7:0]
   delay(40000);
   putchar((iData >> 8) & 0xFF);  // [15:0]
   delay(40000);
   putchar((iData >> 16) & 0xFF); // [23:16]
   delay(40000);
   putchar((iData >> 24) & 0xFF); // [31:23]
   delay(40000);


}

void main()
{
	int i,j;
    int clk_ctrl ;
    int delay_adjust = 0x01;
    int num_pulses = 4;

    //reg_hkspi_disable = 1;
    //reg_spi_enable = 0;
    reg_wb_enable = 1;

    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    set_registers();
    reg_mprj_datah = 0;
    reg_mprj_datal = 0;
    gpio_config_io();

    reg_gpio_out = 1; // OFF
    delay(400000);
    reg_uart_enable = 1;

    // Configure LA probes [63:32] and [127:96] as inputs to the cpu 
	// Configure LA probes [31:0] and [63:32] as input from the cpu
    reg_la0_oenb = reg_la0_iena = 0000000000;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0x00000000;    // [63:32]
	reg_la2_oenb = reg_la2_iena = 0x000000000;    // [95:64]
	reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]


    //reg_mprj_wbhost_clk_ctrl1 = 0x084868c2;
    //reg_mprj_wbhost_clk_ctrl1 = 0x08--6-c-;
    // bit[3:0] - Wishbone Interconnect
    // bit[7:4] - Riscv
    // bit[11:8] - Uart
    // bit[15:12] - SPI
    // bit[19:16] - SDRAM
    // bit[23:20] - Global
    // bit[27:24] - Wish host
    clk_ctrl = 0x08480800;

    //reg_mprj_wbhost_clk_ctrl1 =   0x084868C2;
    reg_mprj_wbhost_clk_ctrl1 =   0x0848F8C2;
    //reg_mprj_wbhost_clk_ctrl1 = clk_ctrl |  (delay_adjust & 0xFF) | ((delay_adjust << 4) & 0xF000);

    reg_mprj_wbhost_clk_ctrl2 = 0x00;
    reg_mprj_wbhost_reg0 = 0x00000A00; // WBS Clk/RISCV/SDRAM Div-4
    reg_gpio_out = 1; // OFF

    // Remove All Reset
    reg_mprj_wbhost_reg0 = 0x00000A1F;
    //reg_mprj_wbhost_reg0 = 0x000001F;

   // Apply reset for PC = 0x200 or 0x1C00 
    while ((reg_la0_data_in == 0x04000140  || reg_la0_data_in == 0x03800140 )&& reg_la1_data_in == 0x84000000) {
     reg_mprj_wbhost_reg0 = 0x00000A00; // Apply Reset
     //reg_mprj_wbhost_reg0 = 0x00; // Apply Reset
     delay_adjust++;
     delay_adjust = delay_adjust & 0xFFF; // 12 bit counter 
     reg_mprj_wbhost_clk_ctrl1 = clk_ctrl |  (delay_adjust & 0xFF) | ((delay_adjust << 4) & 0xF000);
     //reg_mprj_wbhost_clk_ctrl1 =   0x084868C2;
     //reg_mprj_wbhost_clk_ctrl1 =   0x0848F882; // 0x0200 - 0x1C0
     //reg_mprj_wbhost_clk_ctrl1 =   0x0848C882; // 0x0200 - 0x1C0
     //print_reg(reg_la0_data_in);
    // Remove All Reset
     reg_mprj_wbhost_reg0 = 0x00000A1F;
     //reg_mprj_wbhost_reg0 = 0x1F;
     delay(40000);

   }

    //while(1) {
    //   reg_gpio_out = 0; // ON
    //   reg_uart_data = 0xAA;
    //   print_reg(delay_adjust);
    //   delay(4000000);
    //   reg_mprj_datal = 0x000FFFFF;
    //   reg_mprj_datah = 0x00;

    //   print_reg(reg_la0_data_in);
    //   print_reg(reg_la1_data_in);
    //   print_reg(reg_la2_data_in);
    //   print_reg(reg_la3_data_in);


    //   delay(4000000);
    //   reg_uart_data = 0x55;
    //   reg_mprj_datal = 0x0;
    //   reg_mprj_datah = 0x0;
    //   reg_gpio_out = 1; // ON
    //   delay(4000000);
    //}

    //while (1){
    //    reg_gpio_out = 0; // ON
    //    send_packet_io0(2); // send 4 pulses at gpio[j]
    //    for (i = 0; i < num_pulses; i++){
    //        reg_mprj_datal = 0xFFFFFFFF;
    //        reg_mprj_datah = 0x3F;
    //        count_down(PULSE_WIDTH);  
    //        reg_mprj_datah = 0x0;
    //        reg_mprj_datal = 0x0;  
    //        count_down(PULSE_WIDTH); 
    //    }
    //    reg_gpio_out = 1; // OFF
    //    delay(4000000);
    //}

}

