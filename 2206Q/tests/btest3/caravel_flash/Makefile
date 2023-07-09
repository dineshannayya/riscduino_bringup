
#TOOLCHAIN_PATH=/usr/bin/
#TOOLCHAIN_PATH=/usr/local/bin/
#TOOLCHAIN_PATH=/opt/riscv32imc/bin/
# TOOLCHAIN_PATH=/ef/apps/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
TOOLCHAIN_PREFIX=riscv64-unknown-elf
#TOOLCHAIN_PREFIX=riscv32

# ---- Test patterns for project raven ----

CARAVEL_MGMT_FIRMWAVE = ../../common/firmware/caravel_mgmt_core

.SUFFIXES:

PATTERN = hello_world

hex:  ${PATTERN:=.hex}

%.elf: %.c $(CARAVEL_MGMT_FIRMWAVE)/sections.lds $(CARAVEL_MGMT_FIRMWAVE)/crt0_vex.S
	#$(TOOLCHAIN_PATH)riscv32-unknown-elf-gcc -O0 -march=rv32i -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../start.s ../print_io.c $<
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I./ -I$(CARAVEL_MGMT_FIRMWAVE)/ -I$(CARAVEL_MGMT_FIRMWAVE)/generated/ -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,$(CARAVEL_MGMT_FIRMWAVE)/sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ $(CARAVEL_MGMT_FIRMWAVE)/crt0_vex.S $(CARAVEL_MGMT_FIRMWAVE)/isr.c $(CARAVEL_MGMT_FIRMWAVE)/stub.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -D ${PATTERN}.elf > ${PATTERN}.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: ${PATTERN}.hex
	python3 $(CARAVEL_MGMT_FIRMWAVE)/util/caravel_hkflash.py ${PATTERN}.hex

flash2: ${PATTERN}.hex
	python3 $(CARAVEL_MGMT_FIRMWAVE)/util/caravel_flash.py ${PATTERN}.hex

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.vcd *.lst *.hexe

.PHONY: clean hex all flash

