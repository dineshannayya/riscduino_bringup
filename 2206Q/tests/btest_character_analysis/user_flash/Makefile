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


 
# ---- Include Partitioned Makefiles ----
#clone Riscduino Arduino Board from:  github.com/dineshannayya/riscduino_board/
export RISCDUINO_BOARD ?=  /home/dinesha/workarea/opencore/git/riscduino_firmware/custom_board/riscduino
#export RISCDUINO_BOARD ?=  D:\vlsi\github\riscduino_firmware\custom_board\riscduino

#######################################################################
## Compiler Information 
#######################################################################
GCC_PREFIX?=riscv32-unknown-elf
GCC64_PREFIX?=riscv64-unknown-elf



.SUFFIXES:

PATTERN = arduino_character_analysis
GCC64_PREFIX?=riscv64-unknown-elf

hex:  ${PATTERN:=.hex}

#.SUFFIXES:

	
%.hex: 
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${PATTERN}.ino.cpp -o ${PATTERN}.ino.cpp.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/Print.cpp -o Print.cpp.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/WMath.cpp -o WMath.cpp.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/ -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/WString.cpp -o WString.cpp.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/WInterrupts.c -o WInterrupts.c.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/drivers/fe300prci/fe300prci_driver.c -o fe300prci_driver.c.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/abi.cpp -o abi.cpp.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/drivers/plic/plic_driver.c -o plic_driver.c.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/UARTClass.cpp -o UARTClass.cpp.o
	${GCC64_PREFIX}-gcc -c -march=rv32im -mabi=ilp32 -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/entry.S -o entry.S.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/hooks.c -o hooks.c.o
	${GCC64_PREFIX}-gcc -c -march=rv32im -mabi=ilp32 -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/init.S -o init.S.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/itoa.c -o itoa.c.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/main.cpp -o main.cpp.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/malloc.c -o malloc.c.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/new.cpp -o new.cpp.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/sbrk.c -o sbrk.c.o
	${GCC64_PREFIX}-gcc -c -march=rv32im -mabi=ilp32 -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/start.S -o start.S.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/wiring.c -o wiring.c.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/wiring_analog.c -o wiring_analog.c.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/wiring_digital.c -o wiring_digital.c.o
	${GCC64_PREFIX}-g++ -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -fpermissive -Wall -fno-rtti -fno-exceptions -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/wiring_pulse.cpp -o wiring_pulse.cpp.o
	${GCC64_PREFIX}-gcc -c -O3 -march=rv32im -mabi=ilp32 -fpeel-loops -ffreestanding -ffunction-sections -fdata-sections -Wall -I${RISCDUINO_BOARD}/system/include -I${RISCDUINO_BOARD}/sdk/bsp/include -I${RISCDUINO_BOARD}/sdk/bsp/env -I${RISCDUINO_BOARD}/sdk/bsp/drivers -I${RISCDUINO_BOARD}/sdk/bsp/env/uncache -include sys/cdefs.h -g -DARDUINO=10607 -DF_CPU=10000000LL -DRISCDUINO_DEVKIT -I${RISCDUINO_BOARD}/cores/ycr -I${RISCDUINO_BOARD}/variants/standard ${RISCDUINO_BOARD}/cores/ycr/wiring_shift.c -o wiring_shift.c.o
	${GCC64_PREFIX}-ar rcs core.a Print.cpp.o
	${GCC64_PREFIX}-ar rcs core.a UARTClass.cpp.o
	${GCC64_PREFIX}-ar rcs core.a WInterrupts.c.o
	${GCC64_PREFIX}-ar rcs core.a WMath.cpp.o
	${GCC64_PREFIX}-ar rcs core.a WString.cpp.o
	${GCC64_PREFIX}-ar rcs core.a abi.cpp.o
	${GCC64_PREFIX}-ar rcs core.a fe300prci_driver.c.o
	${GCC64_PREFIX}-ar rcs core.a plic_driver.c.o
	${GCC64_PREFIX}-ar rcs core.a entry.S.o
	${GCC64_PREFIX}-ar rcs core.a hooks.c.o
	${GCC64_PREFIX}-ar rcs core.a init.S.o
	${GCC64_PREFIX}-ar rcs core.a itoa.c.o
	${GCC64_PREFIX}-ar rcs core.a main.cpp.o
	${GCC64_PREFIX}-ar rcs core.a malloc.c.o
	${GCC64_PREFIX}-ar rcs core.a new.cpp.o
	${GCC64_PREFIX}-ar rcs core.a sbrk.c.o
	${GCC64_PREFIX}-ar rcs core.a start.S.o
	${GCC64_PREFIX}-ar rcs core.a wiring.c.o
	${GCC64_PREFIX}-ar rcs core.a wiring_analog.c.o
	${GCC64_PREFIX}-ar rcs core.a wiring_digital.c.o
	${GCC64_PREFIX}-ar rcs core.a wiring_pulse.cpp.o
	${GCC64_PREFIX}-ar rcs core.a wiring_shift.c.o
	${GCC64_PREFIX}-g++ -march=rv32im -mabi=ilp32 -T ${RISCDUINO_BOARD}/sdk/bsp/env/uncache/link.lds -nostartfiles -Wl,-N -Wl,--gc-sections -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=sbrk ${PATTERN}.ino.cpp.o -nostdlib -Wl,--start-group core.a -lm -lstdc++ -lc -lgloss -Wl,--end-group -lgcc -o ${PATTERN}.elf
	${GCC64_PREFIX}-objcopy -R .rel.dyn -O binary ${PATTERN}.elf ${PATTERN}.bin
	${GCC64_PREFIX}-objcopy -R .rel.dyn -O verilog ${PATTERN}.elf ${PATTERN}.hex
	${GCC64_PREFIX}-objdump -D  ${PATTERN}.elf >   ${PATTERN}.dump
	rm *.o *.a

flash: %.hex
	python3 ../../common/firmware/riscduino/util/riscduino_flash.py ${PATTERN}.hex

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.log *.dump *.vvp

.PHONY: clean hex all
