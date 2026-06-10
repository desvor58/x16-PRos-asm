CFLAGS := -march=i8086 -mcmodel=tiny -nostdlib -ffreestanding -fno-builtin -ffunction-sections -Iinclude
LDFLAGS := -T link.ld --gc-sections

PROS_DIR := ../x16-PRos
PROS_BFLAGS := -dtm -no-kernel-recomp -no-boot-recomp -no-programs-recomp -quiet

all: prasm

run: deploy
	cd $(PROS_DIR) && \
	./build-linux.sh $(PROS_BFLAGS) && \
	mcopy -i disk_img/x16pros.img prasm.ple ::/PLE.DIR/ && \
	./run-linux.sh

deploy: prasm
	cp bin/prasm.ple $(PROS_DIR)


prasm: main prstd assembler
	ia16-elf-ld $(LDFLAGS) obj/prstdS.o obj/prstdC.o obj/main.o obj/assembler.o -o bin/prasm.elf
	python3 mkple.py
	
main:
	ia16-elf-gcc $(CFLAGS) -c src/main.c -o obj/main.o

prstd:
	nasm src/prstd.s -f elf -o obj/prstdS.o
	ia16-elf-gcc $(CFLAGS) -c src/prstd.c -o obj/prstdC.o

	mkdir -p lib/prstd
	ar rcs lib/prstd/libprstd.a obj/prstdC.o obj/prstdS.o

assembler: prstd
	ia16-elf-gcc $(CFLAGS) -c src/assembler.c -o obj/assembler.o

	mkdir -p lib/asm
	ar rcs lib/asm/libprstd.a obj/assembler.o

.PHONY: clear
clear:
	rm -rf obj/*.o *.bin