# SPDX-FileCopyrightText: 2020 Efabless Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0


 
## SYNTACORE FIRMWARE
YIFIVE_FIRMWARE_PATH =../../common/firmware/riscduino/
GCC64_PREFIX?=riscv64-unknown-elf

########################################################
#include $(MCW_ROOT)/verilog/dv/make/env.makefile
########################################################

#######################################################################
## Compiler Information 
#######################################################################
GCC_PREFIX?=riscv32-unknown-elf



#####################################################
#include $(MCW_ROOT)/verilog/dv/make/sim.makefile
######################################################


.SUFFIXES:

PATTERN = user_mcore_test2

hex:  ${PATTERN:=.hex}

#.SUFFIXES:

	
##############################################################################
# Runing the simulations
##############################################################################

%.hex: 
	${GCC64_PREFIX}-gcc -O2 -funroll-loops -fpeel-loops -fgcse-sm -fgcse-las  -D__RVC_EXT -static -std=gnu99 -fno-common -fno-builtin-printf -DTCM=0 -Wa,-march=rv32im -march=rv32im -mabi=ilp32 -DFLAGS_STR=\""-O2 -funroll-loops -fpeel-loops -fgcse-sm -fgcse-las "\"  -c -I./ -I$(YIFIVE_FIRMWARE_PATH) ${PATTERN}.c -o ${PATTERN}.o
	${GCC64_PREFIX}-gcc -O2 -funroll-loops -fpeel-loops -fgcse-sm -fgcse-las  -D__RVC_EXT -static -std=gnu99 -fno-common -fno-builtin-printf -DTCM=0 -Wa,-march=rv32im -march=rv32im -mabi=ilp32 -DFLAGS_STR=\""-O2 -funroll-loops -fpeel-loops -fgcse-sm -fgcse-las "\"  -D__ASSEMBLY__=1 -c -I./ -I$(YIFIVE_FIRMWARE_PATH)  $(YIFIVE_FIRMWARE_PATH)/crt.S -o crt.o
	${GCC64_PREFIX}-gcc -o ${PATTERN}.elf -T $(YIFIVE_FIRMWARE_PATH)/link.ld ${PATTERN}.o crt.o -nostartfiles -nostdlib -lc -lgcc -march=rv32im -mabi=ilp32 -N
	${GCC64_PREFIX}-objcopy -O verilog ${PATTERN}.elf ${PATTERN}.hex
	${GCC64_PREFIX}-objdump -D ${PATTERN}.elf > ${PATTERN}.dump

flash: %.hex
	python3 ../../common/firmware/riscduino/util/riscduino_flash.py ${PATTERN}.hex


# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.log *.dump *.vvp *.o

.PHONY: clean hex all
