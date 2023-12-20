/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */


#define SC_SIM_OUTPORT (0xf0000000)
#include "int_reg_map.h"
#include "common_misc.h"
#include "common_bthread.h"

// -------------------------------------------------------------------------
// Test copying code into SRAM and running it from there.
// -------------------------------------------------------------------------

  print_message(const char *fmt) {
      char ch;
     // Wait for Semaphore-lock=0
     while((reg_sema_lock0 & 0x1) == 0x0);
     while(ch = *(unsigned char *)fmt) {

        while((reg_uart0_status & 0x1) == 0x1);

	    reg_uart0_txdata = ch;
        ++fmt;
     }
     // Release Semaphore Lock
     reg_sema_lock0 = 0x1;

    // Added nop to Semaphore to acquire by other core
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");


  }

void test_function()
{
    print_message("UART command-0 from core-0\n");

    return;
}

void main()
{
    uint16_t func[&main - &test_function];
    uint16_t *src_ptr;
    uint16_t *dst_ptr;

    reg_glbl_cfg0 |= 0x1F;       // Remove Reset for UART
    reg_glbl_multi_func &=0x7FFFFFFF; // Disable UART Master Bit[31] = 0
    reg_glbl_multi_func |=0x100; // Enable UART Multi func
    reg_uart0_baud_ctrl1 = 0x3F;       // Setting User Baud to 9600 with system clock 10Mhz = (10,000,000/(16 * (63+2))
    reg_uart0_ctrl = 0x07;       // Enable Uart Access {3'h0,2'b00,1'b1,1'b1,1'b1}

   // GLBL_CFG_MAIL_BOX used as mail box, each core update boot up handshake at 8 bit
   // bit[7:0]   - core-0
   // bit[15:8]  - core-1
   // bit[23:16] - core-2
   // bit[31:24] - core-3

   reg_glbl_mail_box = 0x1 << (bthread_get_core_id() * 8); // Start of Main 

    src_ptr = &test_function;
    dst_ptr = func;

    while (src_ptr < &main) {
	*(dst_ptr++) = *(src_ptr++);
    }

    ((void(*)())func)();

    // Signal end of test
}

