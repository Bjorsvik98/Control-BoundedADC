USE_MYSTDLIB = 1

CC = riscv32-unknown-elf-gcc
TOOLCHAIN_PREFIX = /opt/riscv32i/bin/riscv32-unknown-elf-
CFLAGS = -O3 -mabi=ilp32e -march=rv32em -DTIME -DRISCV #-MD
OBJS = fir.o boot.o stdlib.o #filter.o fillData.o 
LDLIBS = -lstdc++

ifeq ($(USE_MYSTDLIB),1)
CFLAGS += -DUSE_MYSTDLIB -ffreestanding -nostdlib -g
OBJS += start.o
else

endif


all: firPython.o
	gcc firPython.c -o out 

clean:
	rm -f *.o out *.d *.elf *.bin *.map

run: clean all 
	./out

fir.hex: fir.elf assembly
	$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@
	python3 hex8tohex32.py fir.hex > fir32.hex

fir.elf: $(OBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc $(CFLAGS) -Wl,-Bstatic,-T,sections.lds,-Map,fir.map,--strip-debug -o $@ $(OBJS) -lgcc
	chmod -x $@

%.o: %.c
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

%.o: %.S
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<


# debug: all
# 	qemu-riscv32-static -g 1236 out 

# gdb:
# 	gdb-multiarch
# 	# target remote :1234

# out.bin : out.elf
# 	$(OBJCOPY) -O binary -j .memory $< $@

# out.elf: $(OBJS) sectionsQemu.lds
# 	$(CC) $(CFLAGS) -o $@ -Wl,-T,sectionsQemu.lds $(OBJS) -lgcc
# # gcc -O3 -mabi=ilp32e -march=rv32em -DTIME -DRISCV -DUSE_MYSTDLIB -ffreestanding -nostdlib -o out.elf -Wl,-T,sectionsQemu.lds out.o -lgcc

# out.o: $(OBJS) sectionsQemu.lds
# 	$(CC) $(CFLAGS) -o $@ -Wl,-T,sectionsQemu.lds $(OBJS) -lgcc

# hex: out.elf
# 	$(RISCV_TOOLS_PREFIX)objcopy -O verilog out.elf out.hex


assembly:
	$(TOOLCHAIN_PREFIX)objdump -d fir.elf > assembly.txt	

copy:
	scp fir32.hex anbjors@leda.tele.ntnu.no:~/pro/fall2022/picoRV32/an_single_core/sim/ 

