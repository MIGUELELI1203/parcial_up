CROSS_COMPILE = riscv64-unknown-elf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

CFLAGS = -march=rv32im -mabi=ilp32 -mno-relax -mcmodel=medlow -O0 -g -Wall -Wextra -nostdlib -ffreestanding -Iinc
LDFLAGS = -m elf32lriscv -T link.ld -nostdlib -nostartfiles

SOURCES = start.S main.c src/soc_emu_gpio.c src/soc_uart.c src/stub_stdlib.c src/systimer.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(OBJECTS:.S=.o)

all: firmware.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

firmware.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

run: firmware.elf
	qemu-system-riscv32 -M virt -nographic -kernel firmware.elf

clean:
	rm -f $(OBJECTS) firmware.elf

.PHONY: all run clean
