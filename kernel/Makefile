# =============================================================================
# Makefile - Kernel build
# =============================================================================

CC      = $(HOME)/cross/toolchain/bin/x86_64-elf-gcc
AS      = /cygdrive/d/Program/NASM/nasm.exe
LD      = $(HOME)/cross/toolchain/bin/x86_64-elf-ld
OBJCOPY = $(HOME)/cross/toolchain/bin/x86_64-elf-objcopy

BUILD   = build

# Include directories
INCLUDES = -I.

CFLAGS  = -c -ffreestanding -fno-stack-protector -mno-red-zone \
			-mcmodel=kernel -Wall -Wextra $(INCLUDES)

# Source files
C_SOURCES   = core/kernel.c \
				drivers/bus/pci/pci_scanner.c \
				drivers/storage/block_device.c

ASM_SOURCES = arch/x86_64/entry.asm

# Object files
C_OBJECTS   = $(patsubst %.c,$(BUILD)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst %.asm,$(BUILD)/%.o,$(ASM_SOURCES))
OBJECTS     = $(ASM_OBJECTS) $(C_OBJECTS)

# Output files
KERNEL_ELF  = $(BUILD)/kernel.elf
KERNEL_BIN  = $(BUILD)/kernel.bin

.PHONY: all clean

all: $(KERNEL_BIN)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

$(KERNEL_ELF): $(OBJECTS) linker.ld
	@mkdir -p $(BUILD)
	$(LD) -T linker.ld -o $@ $(OBJECTS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf64 $< -o $@

clean:
	rm -rf $(BUILD)