/*
 * ============================================================================
 * File:		pci_scanner.h
 * Description: 
 * Created:		2026-09-30
 * Author:		susboy11
 * ============================================================================
*/

#ifndef PCI_SCANNER_H
#define PCI_SCANNER_H

#include "include/default_types.h"

typedef struct
{
	struct
	{
		uint8_t bus;
		uint8_t slot;
		uint8_t func;	
	} access;
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	uint16_t status;
	uint8_t revision_id;
	uint8_t prog_if;
	uint8_t subclass;
	uint8_t class_code;
	uint8_t cache_line_size;
	uint8_t latency_timer;
	uint8_t header_type;
	uint8_t bist;
	uint32_t bar[6];
} pci_device_t;

void initPCIScanner(void);
int getPCIDeviceCount(void);
pci_device_t* getPCIDevice(int index);
int findPCIDevices(uint8_t class_code, uint8_t subclass, uint8_t prog_if, pci_device_t **result, int max_result);
void enablePCIBusMastering(pci_device_t *device);
void enablePCIMemorySpace(pci_device_t *device);

uint8_t readPCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint32_t readPCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void writePCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t data);
void writePCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t data);
void writePCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint8_t data);

#endif
