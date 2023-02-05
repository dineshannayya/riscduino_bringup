
TOOLCHAIN_PATH=
# TOOLCHAIN_PATH=/opt/riscv32imc/bin/
# TOOLCHAIN_PATH=/ef/apps/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
TOOLCHAIN_PREFIX?=riscv32

# ---- Test patterns for project raven ----

.SUFFIXES:

PATTERN = hello

hex:  ${PATTERN:=.hex}

#%.elf: %.c ../sections.lds ../start.s ../print_io.c ../print_io.h
%.elf: %.c ../sections.lds ../start.s ../print_io.c ../print_io.h
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-gcc -O0 -march=rv32i -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../start.s ../print_io.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-unknown-elf-objdump -D hello.elf > hello.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O verilog $< $@
	#sed -i '.orig' -e 's/@10000000/@00000000/g' $@
	sed -ie 's/@10/@00/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-unknown-elf-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: hello.hex
	python3 ../util/caravel_hkflash.py hello.hex

flash2: hello.hex
	python3 ../util/caravel_flash.py $<

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.hexe *.lst *.bin *.vvp *.vcd

.PHONY: clean hex all flash

