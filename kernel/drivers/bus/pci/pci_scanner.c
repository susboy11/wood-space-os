/*
 * ============================================================================
 * File:		pci_scanner.c
 * Description: 
 * Created:		2026-09-30
 * Author:		susboy11
 * ============================================================================
*/

#include "drivers/bus/pci/pci_scanner.h"
#include "arch/x86_64/io.h"

#define MAX_PCI_DEVICES			64
#define MAX_DEPTH_PCI_SCAN		8

#define CONFIG_ADDRESS			0xCF8
#define CONFIG_DATA				0xCFC

static pci_device_t pci_devices[MAX_PCI_DEVICES];
static int pci_device_count = 0;

static uint32_t calculatePCIAddress(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	return (uint32_t)(0x80000000 | (bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC));
}

static int isPCIDeviceExist(uint8_t bus, uint8_t slot, uint8_t func)
{
	return readPCIConfigWord(bus, slot, func, 0x00) != 0xFFFF;
}

static int addPCIDevice(uint8_t bus, uint8_t slot, uint8_t func, pci_device_t *device)
{
	if (pci_device_count >= MAX_PCI_DEVICES)
	{
		return -1;
	}
	
	device->access.bus = bus;
	device->access.slot = slot;
	device->access.func = func;	
	device->vendor_id = readPCIConfigWord(bus, slot, func, 0x00);
	device->device_id = readPCIConfigWord(bus, slot, func, 0x02);
	device->command = readPCIConfigWord(bus, slot, func, 0x04);
	device->status = readPCIConfigWord(bus, slot, func, 0x06);
	device->revision_id = readPCIConfigByte(bus, slot, func, 0x08);
	device->prog_if = readPCIConfigByte(bus, slot, func, 0x09);
	device->subclass = readPCIConfigByte(bus, slot, func, 0x0A);
	device->class_code = readPCIConfigByte(bus, slot, func, 0x0B);
	device->cache_line_size = readPCIConfigByte(bus, slot, func, 0x0C);
	device->latency_timer = readPCIConfigByte(bus, slot, func, 0x0D);
	device->header_type = readPCIConfigByte(bus, slot, func, 0x0E);
	device->bist = readPCIConfigByte(bus, slot, func, 0x0F);
	
	for (int i = 0; i < 6; i++)
	{
		device->bar[i] = readPCIConfigDWord(bus, slot, func, 0x10 + (i * 4));
	}
	
	pci_devices[pci_device_count] = *device;
	pci_device_count++;
	
	return 0;
}

static void scanPCIBus(uint8_t bus, int depth)
{
	if (depth > MAX_DEPTH_PCI_SCAN)
	{
		return;
	}
	
	for (int slot = 0; slot < 32; slot++)
	{
		if (!isPCIDeviceExist(bus, slot, 0))
		{
			continue;
		}
		
		uint8_t header_type = readPCIConfigByte(bus, slot, 0, 0x0E);
		uint8_t func_count = (header_type & 0x80) ? 8 : 1;
		
		for (int func = 0; func < func_count; func++)
		{
			if (isPCIDeviceExist(bus, slot, func) == 0)
			{
				continue;
			}
			
			pci_device_t device;
			
			if (addPCIDevice(bus, slot, func, &device) != 0)
			{
				return;
			}
			
			if (device.class_code == 0x06 && device.subclass == 0x04)
			{
				uint8_t next_bus = readPCIConfigByte(bus, slot, func, 0x19);
				
				scanPCIBus(next_bus, depth + 1);
			}
		}
	}
}

void initPCIScanner(void)
{
	pci_device_count = 0;
	
	scanPCIBus(0, 0);
}

int getPCIDeviceCount(void)
{
	return pci_device_count;
}

pci_device_t* getPCIDevice(int index)
{
	if ((index < 0) || (index >= pci_device_count))
	{
		return NULL;
	}
	
	return &pci_devices[index];
}

int findPCIDevices(uint8_t class_code, uint8_t subclass, uint8_t prog_if, pci_device_t **result, int max_result)
{
	int found = 0;
	
	for (int i = 0; i < pci_device_count; i++)
	{
		if (found >= max_result)
		{
			break;
		}
		
		pci_device_t *device = &pci_devices[i];
		
		if ((device->class_code == class_code) && (device->subclass == subclass) && (device->prog_if == prog_if))
		{
			result[found] = device;
			found++;
		}
	}
	
	return found;
}

void enablePCIBusMastering(pci_device_t *device)
{
	uint16_t command = readPCIConfigWord(device->access.bus, device->access.slot, device->access.func, 0x04);
	
	command |= (1 << 2);
	
	writePCIConfigWord(device->access.bus, device->access.slot, device->access.func, 0x04, command);
}

void enablePCIMemorySpace(pci_device_t *device)
{
	uint16_t command = readPCIConfigWord(device->access.bus, device->access.slot, device->access.func, 0x04);
	
	command |= (1 << 1);
	
	writePCIConfigWord(device->access.bus, device->access.slot, device->access.func, 0x04, command);
}

uint8_t readPCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t value = readPCIConfigDWord(bus, slot, func, offset);
	
	return (uint8_t)((value >> ((offset & 3) * 8)) & 0xFF);
}

uint16_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t value = readPCIConfigDWord(bus, slot, func, offset);
	
	return (uint16_t)((value >> ((offset & 2) * 8)) & 0xFFFF);
}

uint32_t readPCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t address = calculatePCIAddress(bus, slot, func, offset);
	
	outl(CONFIG_ADDRESS, address);
	
	return inl(CONFIG_DATA);
}

void writePCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t data)
{
	uint32_t address = calculatePCIAddress(bus, slot, func, offset);
	
	outl(CONFIG_ADDRESS, address);
	outl(CONFIG_DATA, data);
}

void writePCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t data)
{
	uint32_t old_value = readPCIConfigDWord(bus, slot, func, offset);
	uint32_t shift = (offset & 2) * 8;
	uint32_t mask = (0xFFFF << shift);
	uint32_t new_value = (old_value & ~mask) | ((uint32_t)data << shift);
	
	writePCIConfigDWord(bus, slot, func, offset, new_value);
}

void writePCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint8_t data)
{
	uint32_t old_value = readPCIConfigDWord(bus, slot, func, offset);
	uint32_t shift = (offset & 3) * 8;
	uint32_t mask = (0xFF << shift);
	uint32_t new_value = (old_value & ~mask) | ((uint32_t)data << shift);
	
	writePCIConfigDWord(bus, slot, func, offset, new_value);
}