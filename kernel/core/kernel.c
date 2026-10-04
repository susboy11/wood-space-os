/*
 * ============================================================================
 * File:        kernel.c
 * Description: Kernel entry point and basic output
 * Created:     2026-10-03
 * Author:      susboy11
 * ============================================================================
 */

#include "drivers/bus/pci/pci_scanner.h"

#define VGA_BUFFER			0xB8000
#define VGA_WIDTH			80
#define VGA_HEIGHT			25

#define COLOR_BLACK			0x0
#define COLOR_WHITE			0xF
#define COLOR_LIGHT_GREEN	0xA
#define COLOR_YELLOW		0xE
#define COLOR_LIGHT_RED		0xC

static int cursor_x = 0;
static int cursor_y = 0;

void putChar(char c, unsigned char color)
{
	volatile unsigned short *video = (volatile unsigned short *)VGA_BUFFER;

	if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
		return;
	}

	if (c == '\r')
	{
		cursor_x = 0;
		return;
	}

	int pos = cursor_y * VGA_WIDTH + cursor_x;

	video[pos] = (unsigned short)((color << 8) | (unsigned char)c);
	cursor_x++;

	if (cursor_x >= VGA_WIDTH)
	{
		cursor_x = 0;
		cursor_y++;
	}
}

void print(const char *str, unsigned char color)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		putChar(str[i], color);
	}
}

void printDec(uint32_t value, unsigned char color)
{
	if (value == 0)
	{
		putChar('0', color);
		return;
	}

	char buf[16];
	int i = 0;
	
	while (value > 0)
	{
		buf[i++] = '0' + (value % 10);
		value /= 10;
	}

	while (i > 0)
	{
		putChar(buf[--i], color);
	}
}

void printHex(uint32_t value, int digits, unsigned char color)
{
	char hex[] = "0123456789ABCDEF";

	for (int i = digits - 1; i >= 0; i--)
	{
		putChar(hex[(value >> (i * 4)) & 0xF], color);
	}
}

void KernelMain(void)
{
	volatile unsigned short *video = (volatile unsigned short *)VGA_BUFFER;

	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		video[i] = (unsigned short)((COLOR_BLACK << 8) | ' ');
	}

	cursor_x = 0;
	cursor_y = 0;

	print("Hello from C kernel!\n", COLOR_WHITE);
	print("Long Mode is working.\n", COLOR_LIGHT_GREEN);
	print("This is my first OS.\n\n", COLOR_WHITE);
	print("Scanning PCI bus...\n", COLOR_WHITE);

	initPCIScanner();

	int count = getPCIDeviceCount();

	print("PCI devices found: ", COLOR_WHITE);
	printDec(count, COLOR_LIGHT_GREEN);
	print("\n\n", COLOR_WHITE);
	print("--- All PCI devices ---\n", COLOR_YELLOW);

	for (int i = 0; i < count; i++)
	{
		pci_device_t *dev = getPCIDevice(i);

		print("Dev ", COLOR_WHITE);
		printDec(dev->access.bus, COLOR_WHITE);
		print(":", COLOR_WHITE);
		printDec(dev->access.slot, COLOR_WHITE);
		print(".", COLOR_WHITE);
		printDec(dev->access.func, COLOR_WHITE);

		print("  Vendor:Device = ", COLOR_WHITE);
		printHex(dev->vendor_id, 4, COLOR_WHITE);
		print(":", COLOR_WHITE);
		printHex(dev->device_id, 4, COLOR_WHITE);

		print("  Class = ", COLOR_WHITE);
		printHex(dev->class_code, 2, COLOR_WHITE);
		print(":", COLOR_WHITE);
		printHex(dev->subclass, 2, COLOR_WHITE);
		print(":", COLOR_WHITE);
		printHex(dev->prog_if, 2, COLOR_WHITE);

		print("\n", COLOR_WHITE);
	}

	print("\nLooking for AHCI controller...\n", COLOR_YELLOW);

	pci_device_t *ahci_devices[8];

	int ahci_count = findPCIDevices(0x01, 0x06, 0x01, ahci_devices, 8);

	if (ahci_count > 0)
	{
		print("AHCI controller(s) found: ", COLOR_LIGHT_GREEN);
		printDec(ahci_count, COLOR_LIGHT_GREEN);
		print("\n", COLOR_WHITE);

		pci_device_t *ahci = ahci_devices[0];
		print("  Bus:Slot.Func = ", COLOR_WHITE);
		printDec(ahci->access.bus, COLOR_WHITE);
		print(":", COLOR_WHITE);
		printDec(ahci->access.slot, COLOR_WHITE);
		print(".", COLOR_WHITE);
		printDec(ahci->access.func, COLOR_WHITE);
		print("\n", COLOR_WHITE);

		print("  BAR5 (ABAR) = 0x", COLOR_WHITE);
		printHex(ahci->bar[5], 8, COLOR_WHITE);
		print("\n", COLOR_WHITE);
	}
	else
	{
		print("AHCI controller NOT found!\n", COLOR_LIGHT_RED);
		print("QEMU is probably using IDE instead of AHCI.\n", COLOR_WHITE);
		print("Add '-device ahci' to QEMU command line.\n", COLOR_WHITE);
	}

	while (1)
	{

	}
}