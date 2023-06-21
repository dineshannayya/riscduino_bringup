//////////////////////////////////////////////////////////////////////////////
// SPDX-FileCopyrightText: 2021, Dinesh Annayya
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
// SPDX-FileContributor: Dinesh Annayya <dinesha@opencores.org>
// //////////////////////////////////////////////////////////////////////////
#define SC_SIM_OUTPORT (0xf0000000)
#include "int_reg_map.h"
#define uint32_t  long


int main()
{

   reg_glbl_cfg0 |= 0x1F; // Remove Reset for UART
   reg_wbi_dcg   = 0x01;  // enable qpsim dynamic clock gating

   reg_glbl_multi_func &=0x7FFFFFFF; // Disable UART Master Bit[31] = 0
   reg_glbl_multi_func |=0x100; // Enable UART Multi func
   reg_uart0_ctrl = 0x07;       // Enable Uart Access {3'h0,2'b00,1'b1,1'b1,1'b1}

    while(1) {
       // Check UART RX fifo has data, if available loop back the data
       if(reg_uart0_txfifo_stat > 12) { 
	   reg_uart0_txdata = 'H';
	   reg_uart0_txdata = 'E';
	   reg_uart0_txdata = 'L';
	   reg_uart0_txdata = 'L';
	   reg_uart0_txdata = 'O';
	   reg_uart0_txdata = ' ';
	   reg_uart0_txdata = 'W';
	   reg_uart0_txdata = 'O';
	   reg_uart0_txdata = 'R';
	   reg_uart0_txdata = 'L';
	   reg_uart0_txdata = 'D';
	   reg_uart0_txdata = '\n';
       }
    }

    return 0;
}
