# =============================================================================
# Makefile - Bootloader build
# =============================================================================

NASM       = /cygdrive/d/Program/NASM/nasm.exe
ASM_SOURCE = boot64.asm
BUILD      = build
BIN        = $(BUILD)/boot64.bin

.PHONY: all clean

all: $(BIN)

$(BIN): $(ASM_SOURCE)
	@mkdir -p $(BUILD)
	$(NASM) -f bin $< -o $@

clean:
	rm -rf $(BUILD)