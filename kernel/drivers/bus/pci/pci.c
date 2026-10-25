/*
 * ============================================================================
 * File:		pci.c
 * Description: PCI bus controller implementation
 * Created:		2026-09-30
 * Author:		susboy11
 * ============================================================================
*/

#include <stddef.h>

#include "drivers/bus/pci/pci.h"

#include "arch/x86_64/io.h"

#include "include/bus.h"
#include "include/device.h"

#include "lib/string.h"

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
	return readPCIConfigWord(bus, slot, func, PCI_CFG_VENDOR_ID) != 0xFFFF;
}

static int addPCIDevice(uint8_t bus, uint8_t slot, uint8_t func, pci_device_t *device)
{
	if (pci_device_count >= MAX_PCI_DEVICES)
	{
		return -1;
	}
	
	device->address.bus = bus;
	device->address.slot = slot;
	device->address.func = func;
	
	device->config_header.vendor_id = readPCIConfigWord(bus, slot, func, PCI_CFG_VENDOR_ID);
	device->config_header.device_id = readPCIConfigWord(bus, slot, func, PCI_CFG_DEVICE_ID);
	device->config_header.command = readPCIConfigWord(bus, slot, func, PCI_CFG_COMMAND);
	device->config_header.status = readPCIConfigWord(bus, slot, func, PCI_CFG_STATUS);
	device->config_header.revision_id = readPCIConfigByte(bus, slot, func, PCI_CFG_REVISION_ID);
	device->config_header.progif = readPCIConfigByte(bus, slot, func, PCI_CFG_PROG_IF);
	device->config_header.subclass = readPCIConfigByte(bus, slot, func, PCI_CFG_SUBCLASS);
	device->config_header.class_code = readPCIConfigByte(bus, slot, func, PCI_CFG_CLASS_CODE);
	device->config_header.cache_line_size = readPCIConfigByte(bus, slot, func, PCI_CFG_CACHE_LINE_SIZE);
	device->config_header.latency_timer = readPCIConfigByte(bus, slot, func, PCI_CFG_LATENCY_TIMER);
	device->config_header.header_type = readPCIConfigByte(bus, slot, func, PCI_CFG_HEADER_TYPE);
	device->config_header.bist = readPCIConfigByte(bus, slot, func, PCI_CFG_BIST);

	uint8_t header_type = device->config_header.header_type & PCI_HTYPE_HL_MASK;

	if (header_type == 0x00)
	{
		for (int i = 0; i < 6; i++)
		{
			device->config_header.type0.bar[i] = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE0_BAR0 + (i * 4));
		}

		device->config_header.type0.cardbus_cis = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE0_CARDBUS_CIS);
		device->config_header.type0.subsystem_vendor_id = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE0_SUBSYSTEM_VENDOR);
		device->config_header.type0.subsystem_device_id = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE0_SUBSYSTEM_ID);
		device->config_header.type0.expansion_rom = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE0_EXPANSION_ROM);
		device->config_header.type0.capabilities = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE0_CAPABILITIES);
		device->config_header.type0.interrupt_line = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE0_INTERRUPT_LINE);
		device->config_header.type0.interrupt_pin = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE0_INTERRUPT_PIN);
		device->config_header.type0.min_grant = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE0_MIN_GRANT);
		device->config_header.type0.max_latency = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE0_MAX_LATENCY);
	}
	else if (header_type == 0x01)
	{
		for (int i = 0; i < 2; i++)
		{
			device->config_header.type1.bar[i] = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE1_BAR0 + (i * 4));
		}

		device->config_header.type1.primary_bus = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_PRIMARY_BUS);
		device->config_header.type1.secondary_bus = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_SECONDARY_BUS);
		device->config_header.type1.subordinate_bus = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_SUBORDINATE_BUS);
		device->config_header.type1.secondary_timer = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_SECONDARY_TIMER);
		device->config_header.type1.io_base = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_IO_BASE);
		device->config_header.type1.io_limit = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_IO_LIMIT);
		device->config_header.type1.secondary_status = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_SECONDARY_STATUS);
		device->config_header.type1.memory_base = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_MEMORY_BASE);
		device->config_header.type1.memory_limit = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_MEMORY_LIMIT);
		device->config_header.type1.prefetch_memory_base = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_PREFETCH_MEMORY_BASE);
		device->config_header.type1.prefetch_memory_limit = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_PREFETCH_MEMORY_LIMIT);
		device->config_header.type1.prefetch_memory_base_upper = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE1_PREFETCH_MEMORY_BASE_UPPER);
		device->config_header.type1.prefetch_memory_limit_upper = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE1_PREFETCH_MEMORY_LIMIT_UPPER);
		device->config_header.type1.io_base_upper = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_IO_BASE_UPPER);
		device->config_header.type1.io_limit_upper = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_IO_LIMIT_UPPER);
		device->config_header.type1.capabilities = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_CAPABILITIES);
		device->config_header.type1.expansion_rom = readPCIConfigDWord(bus, slot, func, PCI_CFG_TYPE1_EXPANSION_ROM);
		device->config_header.type1.interrupt_line = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_INTERRUPT_LINE);
		device->config_header.type1.interrupt_pin = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_INTERRUPT_PIN);
		device->config_header.type1.bridge_control = readPCIConfigWord(bus, slot, func, PCI_CFG_TYPE1_BRIDGE_CONTROL);
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
		
		uint8_t header_type = readPCIConfigByte(bus, slot, 0, PCI_CFG_HEADER_TYPE);
		uint8_t func_count = (header_type & PCI_HTYPE_MFD) ? 8 : 1;
		
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
			
			if (device.config_header.class_code == 0x06 && device.config_header.subclass == 0x04)
			{
				uint8_t next_bus = readPCIConfigByte(bus, slot, func, PCI_CFG_TYPE1_SECONDARY_BUS);
				
				scanPCIBus(next_bus, depth + 1);
			}
		}
	}
}

static int initPCI(bus_t *bus)
{
	pci_device_count = 0;
	
	(void)bus;
	
	return 0;
}

static int scanPCI(bus_t *bus)
{
	scanPCIBus(0, 0);
	
	int registered = 0;
	
	for (int i = 0; i < pci_device_count; i++)
	{
		pci_device_t *pci = &pci_devices[i];
		device_t *device = allocDevice();
		
		if (device == NULL)
		{
			break;
		}
		
		int pos = 0;
		
		device->name[pos++] = 'p';
		device->name[pos++] = 'c';
		device->name[pos++] = 'i';
		device->name[pos++] = '-';
		
		stringWriteDec(device->name, &pos, (uint32_t)pci->address.bus);
		
		device->name[pos++] = ':';
		
		stringWriteDec(device->name, &pos, (uint32_t)pci->address.slot);
		
		device->name[pos++] = '.';
		
		stringWriteDec(device->name, &pos, (uint32_t)pci->address.func);
		
		device->name[pos] = '\0';
		device->bus = bus;
		device->bus_data = pci;
		
		registerDevice(device);
		registered++;
	}
	
	return registered;
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

void enablePCIBusMastering(pci_device_t *device)
{
	uint16_t command = readPCIConfigWord(device->address.bus, device->address.slot, device->address.func, PCI_CFG_COMMAND);
	
	command |= PCI_CMD_BME;
	
	writePCIConfigWord(device->address.bus, device->address.slot, device->address.func, PCI_CFG_COMMAND, command);
}

void enablePCIMemorySpace(pci_device_t *device)
{
	uint16_t command = readPCIConfigWord(device->address.bus, device->address.slot, device->address.func, PCI_CFG_COMMAND);
	
	command |= PCI_CMD_MSE;
	
	writePCIConfigWord(device->address.bus, device->address.slot, device->address.func, PCI_CFG_COMMAND, command);
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

void writePCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint8_t data)
{
	uint32_t old_value = readPCIConfigDWord(bus, slot, func, offset);
	uint32_t shift = (offset & 3) * 8;
	uint32_t mask = (0xFF << shift);
	uint32_t new_value = (old_value & ~mask) | ((uint32_t)data << shift);
	
	writePCIConfigDWord(bus, slot, func, offset, new_value);
}

void writePCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t data)
{
	uint32_t old_value = readPCIConfigDWord(bus, slot, func, offset);
	uint32_t shift = (offset & 2) * 8;
	uint32_t mask = (0xFFFF << shift);
	uint32_t new_value = (old_value & ~mask) | ((uint32_t)data << shift);
	
	writePCIConfigDWord(bus, slot, func, offset, new_value);
}

void writePCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t data)
{
	uint32_t address = calculatePCIAddress(bus, slot, func, offset);
	
	outl(CONFIG_ADDRESS, address);
	outl(CONFIG_DATA, data);
}

static bus_t pci_bus =
{
	.name = "pci",
	.init = initPCI,
	.scan = scanPCI,
};

BUS_REGISTER(pci_bus);