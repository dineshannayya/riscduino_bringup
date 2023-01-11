
//////////////////////////////////////////////////////////////////////
////                                                              ////
////  UART2SPI  Top Module                                        ////
////                                                              ////
////  This file is part of the uart2spi  cores project            ////
////  http://www.opencores.org/cores/uart2spi/                    ////
////                                                              ////
////  Description                                                 ////
////  Uart2SPI top level integration.                             ////
////    1. spi_core                                               ////
////    2. uart_core                                              ////
////    3. uart_msg_handler                                       ////
////                                                              ////
////  To Do:                                                      ////
////    nothing                                                   ////
////                                                              ////
////  Author(s):                                                  ////
////      - Dinesh Annayya, dinesha@opencores.org                 ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2000 Authors and OPENCORES.ORG                 ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE.  See the GNU Lesser General Public License for more ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not, download it   ////
//// from http://www.opencores.org/lgpl.shtml                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////

module top (  
        line_reset_n ,
        line_clk ,


       // Line Interface
        uart_rxd,
        uart_txd,

      // Spi I/F
        spi_sck,
        spi_so,
        spi_si,
        spi_csn  

     );



//---------------------------------
// Global Dec
// ---------------------------------

input        line_reset_n         ; // line reset
input        line_clk             ; // line clock

//-------------------------------------
// Line Interface
// -------------------------------------
input         uart_rxd                  ; // uart rxd
output        uart_txd                  ; // uart txd

//-------------------------------------
// Spi I/F
//-------------------------------------
output              spi_sck            ; // clock out
output              spi_so             ; // serial data out
input               spi_si             ; // serial data in
output [3:0]        spi_csn            ; // cs_n
//---------------------------------------
// Control Unit interface
// --------------------------------------

wire  [15:0]       reg_addr        ; // Register Address
wire  [31:0]       reg_wdata       ; // Register Wdata
wire               reg_req         ; // Register Request
wire               reg_wr          ; // 1 -> write; 0 -> read
wire               reg_ack         ; // Register Ack
wire   [31:0]      reg_rdata       ;
//--------------------------------------
// TXD Path
// -------------------------------------
wire               tx_data_avail   ; // Indicate valid TXD Data 
wire [7:0]         tx_data         ; // TXD Data to be transmited
wire               tx_rd           ; // Indicate TXD Data Been Read


//--------------------------------------
// RXD Path
// -------------------------------------
wire         rx_ready           ; // Indicate Ready to accept the Read Data
wire [7:0]  rx_data             ; // RXD Data 
wire        rx_wr               ; // Valid RXD Data

//-------------------------------------
// Configuration 
// -------------------------------------
wire         cfg_tx_enable        ; // Tx Enable
wire         cfg_rx_enable        ; // Rx Enable
wire         cfg_stop_bit         ; // 0 -> 1 Stop, 1 -> 2 Stop
wire   [1:0] cfg_pri_mod          ; // priority mode, 0 -> nop, 1 -> Even, 2 -> Odd
wire   [11:0] cfg_baud_16x        ; // 16x Baud clock generation

//--------------------------------------
// ERROR Indication
// -------------------------------------
wire        frm_error            ; // framing error
wire        par_error            ; // par error

wire        baud_clk_16x         ; // 16x Baud clock
// configuration control
assign  cfg_tx_enable  = 1'b1; // Enable Transmit Path
assign  cfg_rx_enable  = 1'b1; // Enable Received Path
assign  cfg_stop_bit   = 1'b1; // 0 -> 1 Start , 1 -> 2 Stop Bits
assign  cfg_pri_mod    = 2'b0; // priority mode, 0 -> nop, 1 -> Even, 2 -> Odd
assign 	cfg_baud_16x   = 'h0;

spi_core  u_spi (

             .clk                (baud_clk_16x),
             .reset_n            (line_reset_n),
               
        // Reg Bus Interface Signal
             .reg_cs             (reg_req      ),
             .reg_wr             (reg_wr       ),
             .reg_addr           (reg_addr[5:2]),
             .reg_wdata          (reg_wdata    ),
             .reg_be             (4'b1111      ),

            // Outputs
            .reg_rdata           (reg_rdata    ),
            .reg_ack             (reg_ack      ),

          // line interface
               .sck              (spi_sck      ),
               .so               (spi_so       ),
               .si               (spi_si       ),
               .cs_n             (spi_csn      ) 

           );

 uart_core u_core (  
          .line_reset_n       (line_reset_n) ,
          .line_clk           (line_clk) ,

	// configuration control
          .cfg_tx_enable      (cfg_tx_enable) , 
          .cfg_rx_enable      (cfg_rx_enable) , 
          .cfg_stop_bit       (cfg_stop_bit) , 
          .cfg_pri_mod        (cfg_pri_mod) , 
	  .cfg_baud_16x       (cfg_baud_16x) ,

    // TXD Information
          .tx_data_avail      (tx_data_avail) ,
          .tx_rd              (tx_rd) ,
          .tx_data            (tx_data) ,
         

    // RXD Information
          .rx_ready           (rx_ready) ,
          .rx_wr              (rx_wr) ,
          .rx_data            (rx_data) ,

       // Status information
          .frm_error          (frm_error) ,
	  .par_error          (par_error) ,

	  .baud_clk_16x       (baud_clk_16x) ,

       // Line Interface
          .rxd                (uart_rxd) ,
          .txd                (uart_txd) 

     );



uart_msg_handler u_msg (  
          .reset_n            (line_reset_n ) ,
          .sys_clk            (baud_clk_16x ) ,


    // UART-TX Information
          .tx_data_avail      (tx_data_avail) ,
          .tx_rd              (tx_rd) ,
          .tx_data            (tx_data) ,
         

    // UART-RX Information
          .rx_ready           (rx_ready) ,
          .rx_wr              (rx_wr) ,
          .rx_data            (rx_data) ,

      // Towards Control Unit
          .reg_addr          (reg_addr),
          .reg_wr            (reg_wr),
          .reg_wdata         (reg_wdata),
          .reg_req           (reg_req),
          .reg_ack           (reg_ack),
	  .reg_rdata         (reg_rdata) 

     );

endmodule
