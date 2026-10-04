# =============================================================================
# Makefile - OS build and run
# =============================================================================

QEMU           = /cygdrive/d/Program/QEMU/qemu-system-x86_64
BOOT_IMAGE     = $(HOME)/myos/bootloader/build/boot64.bin
KERNEL_IMAGE   = $(HOME)/myos/kernel/build/kernel.bin
DISK_IMAGE     = $(HOME)/myos/build/disk.img

.PHONY: all bootloader kernel disk run debug clean

all: bootloader kernel disk

bootloader:
	$(MAKE) -C bootloader

kernel:
	$(MAKE) -C kernel

disk: bootloader kernel
	@echo "Creating disk image..."
	@mkdir -p $(HOME)/myos/build
	dd if=/dev/zero of=$(DISK_IMAGE) bs=512 count=2880 2>/dev/null
	dd if=$(BOOT_IMAGE) of=$(DISK_IMAGE) bs=512 count=1 conv=notrunc 2>/dev/null
	dd if=$(KERNEL_IMAGE) of=$(DISK_IMAGE) bs=512 seek=1 conv=notrunc 2>/dev/null
	@echo "Disk image ready: $(DISK_IMAGE)"

run: disk
	@echo "Starting OS in QEMU (AHCI mode)..."
	@$(QEMU) -drive format=raw,file="`cygpath -w $(DISK_IMAGE)`",if=none,id=disk0 \
				-device ahci,id=ahci \
				-device ide-hd,drive=disk0,bus=ahci.0

debug: disk
	@echo "Starting OS in QEMU (debug mode)..."
	@$(QEMU) -drive format=raw,file="`cygpath -w $(DISK_IMAGE)`",if=none,id=disk0 \
				-device ahci,id=ahci \
				-device ide-hd,drive=disk0,bus=ahci.0 \
				-d int,cpu_reset,guest_errors \
				-no-reboot -no-shutdown

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C kernel clean
	rm -rf $(HOME)/myos/build