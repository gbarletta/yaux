OBJS := boot.o main.o memory.o paging.o uart.o trap.o
OUT := kernel.elf
AS := riscv64-unknown-elf-as
LD := riscv64-unknown-elf-ld 
CC := riscv64-unknown-elf-gcc
EMU := qemu-system-riscv64
CFLAGS := -g -c -Wall -Wextra -std=c11 -pedantic -nostdlib -ffreestanding -mcmodel=medany -ftree-ter
EMUFLAGS := -monitor stdio -machine virt -bios none
ASFLAGS :=
DEBUGFLAGS := -chardev socket,path=/tmp/gdb-socket,server=on,wait=off,id=gdb0 -gdb chardev:gdb0 -S 


run: kernel.elf
	$(EMU) $(EMUFLAGS) -kernel kernel.elf

disasm: kernel.elf
	riscv64-unknown-elf-objdump kernel.elf -D

kernel.elf: link.ld $(OBJS)
	$(LD) $(LDFLAGS) -o kernel.elf -T link.ld $(OBJS)

usermode.o: usermode.s
	$(AS) $(ASFLAGS) usermode.s -o usermode.o

boot.o: boot.s
	$(AS) $(ASFLAGS) boot.s -o boot.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

memory.o: memory.c
	$(CC) $(CFLAGS) memory.c

paging.o: paging.c
	$(CC) $(CFLAGS) paging.c

trap.o: trap.c
	$(CC) $(CFLAGS) trap.c	

clean:
	rm -f $(OBJS) $(OUT)