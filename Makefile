OBJS = boot.o main.o memory.o paging.o uart.o
SOURCE = main.c memory.c paging.c uart.c
OUT = kernel.elf
AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld 
CC = riscv64-unknown-elf-gcc
EMU = qemu-system-riscv64
CFLAGS = -g -c -Wall -Wextra -std=c11 -pedantic -nostdlib -ffreestanding -mcmodel=medany -ftree-ter
EMUFLAGS = -monitor stdio -machine virt -bios none
ASFLAGS =

run: kernel.elf
	$(EMU) $(EMUFLAGS) -kernel kernel.elf

kernel.elf: link.ld $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.elf -T link.ld $(OBJS)

boot.o: boot.s
	$(AS) $(ASFLAGS) boot.s -o boot.o 

main.o: main.c
	$(CC) $(CFLAGS) main.c

memory.o: memory.c
	$(CC) $(CFLAGS) memory.c

paging.o: paging.c
	$(CC) $(CFLAGS) paging.c

clean:
	rm -f $(OBJS) $(OUT)