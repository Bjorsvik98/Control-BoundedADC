USE_MYSTDLIB = 1
CORE_NUMBER = 2

CC = riscv32-unknown-elf-gcc
TOOLCHAIN_PREFIX = /opt/riscv32i/bin/riscv32-unknown-elf-
# CFLAGS = -Wall -march=rv32im -mabi=ilp32 -ffreestanding -g --std=c99 -Os -nostdlib 
CFLAGS = -O3 -mabi=ilp32 -march=rv32im -DTIME -DRISCV #-MD
CFLAGS += -DUSE_MYSTDLIB -ffreestanding -nostdlib #-DCORE_NUMBER=$(CORE_NUMBER) 

BatchOBJS = batch.o stdlib.o filter.o start.o boot.o
parallelOBJS = parallel.o stdlib.o  start.o boot.o filter.o #parallel2.o parallel3.o
LDLIBS = -lstdc++


clean:
	rm -f *.o out *.d parallel *.elf *.map batch

%.o: %.c
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

%.o: %.S
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

%.o: %.s
	$(TOOLCHAIN_PREFIX)gcc -c -DUSE_MYSTDLIB -ffreestanding -nostdlib -mabi=ilp32e -march=rv32em -DTIME -DRISCV $<

batch.hex: batch.elf assemblyBatch 
	$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@
	python3 hex8tohex32.py batch.hex > batch32.hex

batch.elf: $(BatchOBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc $(CFLAGS) -Wl,-Bstatic,-T,sections.lds,-Map,batch.map,--strip-debug -o $@ $(BatchOBJS) -lgcc
	chmod -x $@

parallel.hex: parallel.elf assembly assemblyInit
	$(TOOLCHAIN_PREFIX)objcopy -O verilog $< $@
	python3 hex8tohex32.py parallel.hex > parallel32.hex

parallel.elf: $(parallelOBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc $(CFLAGS) -Wl,-Bstatic,-T,sections.lds,-Map,parallel.map,--strip-debug -o $@ $(parallelOBJS) -lgcc
	chmod -x $@

parallel: 
	# gcc -o parallel.o parallel.c 
	# gcc -o filter.o filter.c 
	gcc -o $@ parallelPython.c filter.c 
	./$@
	rm -f parallel.o filter.o 
	
batch: 
	gcc -o $@ batch.c filter.c 
	./$@

assembly:
	$(TOOLCHAIN_PREFIX)objdump -d parallel.elf > assemblyParallel.txt	

assemblyBatch:
	$(TOOLCHAIN_PREFIX)objdump -d batch.elf > assemblyBatch.txt

assemblyInit:
	make -C python/ assemblyCore

