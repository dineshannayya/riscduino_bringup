//////////////////////////////////////////////////////////////////////////////
// SPDX-FileCopyrightText: 2021 , Dinesh Annayya                          
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// SPDX-License-Identifier: Apache-2.0
// SPDX-FileContributor: Created by Dinesh Annayya <dinesha@opencores.org>
//
//////////////////////////////////////////////////////////////////////
////                                                              ////
////  SPI With Wishbone                                           ////
////                                                              ////
////  This file is part of the riscduino cores project            ////
////  https://github.com/dineshannayya/riscduino.git              ////
////                                                              ////
////  Description : This module contains SPI interface + WB Master////
////                                                              ////   
////  To Do:                                                      ////
////    nothing                                                   ////
////                                                              ////
////  Author(s):                                                  ////
////      - Dinesh Annayya, dinesh.annayya@gmail.com              ////
////                                                              ////
////  Revision :                                                  ////
////    0.1 - 11th Feb 2023, Dinesh A                            ////
////          Initial version                                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////

module qspis_top (

	 input                sys_clk         ,
	 input                rst_n           ,

         input                sclk            ,
         input                ssn             ,
         input        [3:0]   sdin            ,
         output wire  [3:0]   sdout           ,
         output wire          sdout_oen       ,
			
	// Debug
	output wire [2:0]    spi_if_st       ,
	output wire          sck_toggle      ,
	output wire [5:0]    bitcnt          ,
	output wire          inst_trg        ,
	output wire          addr_trg        ,
	output wire          spi_st_trans    ,
	output wire          spi_trig        ,


         // WB Master Port
         output  wire         wbm_cyc_o       ,  // strobe/request
         output  wire         wbm_stb_o       ,  // strobe/request
         output  wire  [31:0] wbm_adr_o       ,  // address
         output  wire         wbm_we_o        ,  // write
         output  wire  [31:0] wbm_dat_o       ,  // data output
         output  wire  [3:0]  wbm_sel_o       ,  // byte enable
         input         [31:0] wbm_dat_i       ,  // data input
         input                wbm_ack_i       ,  // acknowlegement
         input                wbm_err_i          // error
    );

//-----------------------------------
// Register I/F
//-----------------------------------

wire          reg_wr          ; // write request
wire          reg_rd          ; // read request
wire  [23:0]  reg_addr        ; // address
wire  [3:0]   reg_be          ; // Byte enable
wire  [31:0]  reg_wdata       ; // write data
wire  [31:0]  reg_rdata       ; // read data
wire          reg_ack         ; // read valid

qspis_if u_if (

	     .sys_clk         (sys_clk         ),
	     .rst_n           (rst_n           ),

             .sclk            (sclk            ),
             .ssn             (ssn             ),
             .sdin            (sdin            ),
             .sdout           (sdout           ),
             .sdout_oen       (sdout_oen       ),
				 
				 .spi_if_st       (spi_if_st       ),
				 .sck_toggle      (sck_toggle      ),
				 .bitcnt          (bitcnt          ),
				 .inst_trg        (inst_trg        ),
				 .addr_trg        (addr_trg        ),
				 .spi_st_trans    (spi_st_trans    ),
				 .spi_trig        (spi_trig        ),

             //spi_sm Interface
             .reg_wr          (reg_wr          ), // write request
             .reg_rd          (reg_rd          ), // read request
             .reg_addr        (reg_addr        ), // address
             .reg_be          (reg_be          ), // Byte enable
             .reg_wdata       (reg_wdata       ), // write data
             .reg_rdata       (reg_rdata       ), // read data
             .reg_ack         (reg_ack         )  // read valid
             );

qspis_wb  u_spi2wb (

             //spis_if Interface
             .reg_wr          (reg_wr          ), // write request
             .reg_rd          (reg_rd          ), // read request
             .reg_addr        (reg_addr        ), // address
             .reg_be          (reg_be          ), // Byte enable
             .reg_wdata       (reg_wdata       ), // write data
             .reg_rdata       (reg_rdata       ), // read data
             .reg_ack         (reg_ack         ), // read valid

          // WB Master Port
             .wbm_cyc_o       (wbm_cyc_o       ),  // strobe/request
             .wbm_stb_o       (wbm_stb_o       ),  // strobe/request
             .wbm_adr_o       (wbm_adr_o       ),  // address
             .wbm_we_o        (wbm_we_o        ),  // write
             .wbm_dat_o       (wbm_dat_o       ),  // data output
             .wbm_sel_o       (wbm_sel_o       ),  // byte enable
             .wbm_dat_i       (wbm_dat_i       ),  // data input
             .wbm_ack_i       (wbm_ack_i       ),  // acknowlegement
             .wbm_err_i       (wbm_err_i       )   // error

);

endmodule
