/*
 * ============================================================================
 * File:		pci.h
 * Description: PCI bus controller
 * Created:		2026-09-30
 * Author:		susboy11
 * ============================================================================
*/

#ifndef PCI_H
#define PCI_H

#include <stdint.h>

// ============================================================================
// PCI Configuration Space Offsets
// ============================================================================
#define PCI_CFG_VENDOR_ID										0x00
#define PCI_CFG_DEVICE_ID										0x02
#define PCI_CFG_COMMAND											0x04
#define PCI_CFG_STATUS											0x06
#define PCI_CFG_REVISION_ID										0x08
#define PCI_CFG_PROG_IF											0x09
#define PCI_CFG_SUBCLASS										0x0A
#define PCI_CFG_CLASS_CODE										0x0B
#define PCI_CFG_CACHE_LINE_SIZE									0x0C
#define PCI_CFG_LATENCY_TIMER									0x0D
#define PCI_CFG_HEADER_TYPE										0x0E
#define PCI_CFG_BIST											0x0F

// Type 0 Offsets
#define PCI_CFG_TYPE0_BAR0										0x10
#define PCI_CFG_TYPE0_BAR1										0x14
#define PCI_CFG_TYPE0_BAR2										0x18
#define PCI_CFG_TYPE0_BAR3										0x1C
#define PCI_CFG_TYPE0_BAR4										0x20
#define PCI_CFG_TYPE0_BAR5										0x24
#define PCI_CFG_TYPE0_CARDBUS_CIS								0x28
#define PCI_CFG_TYPE0_SUBSYSTEM_VENDOR							0x2C
#define PCI_CFG_TYPE0_SUBSYSTEM_ID								0x2E
#define PCI_CFG_TYPE0_EXPANSION_ROM								0x30
#define PCI_CFG_TYPE0_CAPABILITIES								0x34
#define PCI_CFG_TYPE0_INTERRUPT_LINE							0x3C
#define PCI_CFG_TYPE0_INTERRUPT_PIN								0x3D
#define PCI_CFG_TYPE0_MIN_GRANT									0x3E
#define PCI_CFG_TYPE0_MAX_LATENCY								0x3F

// Type 1 Offsets
#define PCI_CFG_TYPE1_BAR0										0x10
#define PCI_CFG_TYPE1_BAR1										0x14
#define PCI_CFG_TYPE1_PRIMARY_BUS								0x18
#define PCI_CFG_TYPE1_SECONDARY_BUS								0x19
#define PCI_CFG_TYPE1_SUBORDINATE_BUS							0x1A
#define PCI_CFG_TYPE1_SECONDARY_TIMER							0x1B
#define PCI_CFG_TYPE1_IO_BASE									0x1C
#define PCI_CFG_TYPE1_IO_LIMIT									0x1D
#define PCI_CFG_TYPE1_SECONDARY_STATUS							0x1E
#define PCI_CFG_TYPE1_MEMORY_BASE								0x20
#define PCI_CFG_TYPE1_MEMORY_LIMIT								0x22
#define PCI_CFG_TYPE1_PREFETCH_MEMORY_BASE						0x24
#define PCI_CFG_TYPE1_PREFETCH_MEMORY_LIMIT						0x26
#define PCI_CFG_TYPE1_PREFETCH_MEMORY_BASE_UPPER				0x28
#define PCI_CFG_TYPE1_PREFETCH_MEMORY_LIMIT_UPPER				0x2C
#define PCI_CFG_TYPE1_IO_BASE_UPPER								0x30
#define PCI_CFG_TYPE1_IO_LIMIT_UPPER							0x32
#define PCI_CFG_TYPE1_CAPABILITIES								0x34
#define PCI_CFG_TYPE1_EXPANSION_ROM								0x38
#define PCI_CFG_TYPE1_INTERRUPT_LINE							0x3C
#define PCI_CFG_TYPE1_INTERRUPT_PIN								0x3D
#define PCI_CFG_TYPE1_BRIDGE_CONTROL							0x3E

// ============================================================================
// Offset 0x00: ID - Identifiers
// ============================================================================
#define PCI_ID_VID_MASK											0x0000FFFF	// Vendor ID (RO, Reset = ImplSpec)
#define PCI_ID_VID_SHIFT										0			// Vendor ID Shift
#define PCI_ID_DID_MASK											0xFFFF0000	// Device ID (RO, Reset = ImplSpec)
#define PCI_ID_DID_SHIFT										16			// Device ID Shift

// ============================================================================
// Offset 0x04: CMD - Command
// ============================================================================
#define PCI_CMD_IOSE											(1 << 0)	// I/O Space Enable (RW/RO, Reset = ImplSpec)
#define PCI_CMD_MSE												(1 << 1)	// Memory Space Enable (RW, Reset = 0)
#define PCI_CMD_BME												(1 << 2)	// Bus Master Enable (RW, Reset = 0)
#define PCI_CMD_SCE												(1 << 3)	// Special Cycle Enable (RO, Reset = 0)
#define PCI_CMD_MWIE											(1 << 4)	// Memory Write and Invalidate Enable (RW/RO, Reset = ImplSpec)
#define PCI_CMD_VGA												(1 << 5)	// VGA Palette Snooping Enable (RO, Reset = 0)
#define PCI_CMD_PEE												(1 << 6)	// Parity Error Response Enable (RW/RO, Reset = 0)
#define PCI_CMD_WCC												(1 << 7)	// Wait Cycle Enable (RO, Reset = 0)
#define PCI_CMD_SEE												(1 << 8)	// SERR# Enable (RW/RO, Reset = 0)
#define PCI_CMD_FBE												(1 << 9)	// Fast Back-to-Back Enable (RW/RO, Reset = 0)
#define PCI_CMD_ID												(1 << 10)	// Interrupt Disable (RW, Reset = 0)

// ============================================================================
// Offset 0x06: STS - Device Status
// ============================================================================
#define PCI_STS_IS												(1 << 3)	// Interrupt Status (RO, Reset = 0)
#define PCI_STS_CL												(1 << 4)	// Capabilities List (RO, Reset = 1)
#define PCI_STS_C66												(1 << 5)	// 66 MHz Capable (RO, Reset = ImplSpec)
#define PCI_STS_FBC												(1 << 7)	// Fast Back-to-Back Capable (RO, Reset = ImplSpec)
#define PCI_STS_DPD												(1 << 8)	// Master Data Parity Error Detected (RWC, Reset = 0)
#define PCI_STS_DEVT_MASK										0x00000600	// DEVSEL# Timing (RO, Reset = ImplSpec)
#define PCI_STS_DEVT_SHIFT										9			// DEVSEL# Timing Shift
#define PCI_STS_STA												(1 << 11)	// Signaled Target-Abort (RWC, Reset = 0)
#define PCI_STS_RTA												(1 << 12)	// Received Target Abort (RWC, Reset = 0)
#define PCI_STS_RMA												(1 << 13)	// Received Master-Abort (RWC, Reset = 0)
#define PCI_STS_SSE												(1 << 14)	// Signaled System Error (RWC, Reset = 0)
#define PCI_STS_DPE												(1 << 15)	// Detected Parity Error (RWC, Reset = 0)

// ============================================================================
// Offset 0x08: RID - Revision ID
// ============================================================================
#define PCI_RID_RID_MASK										0x000000FF	// Revision ID (RO, Reset = 0)
#define PCI_RID_RID_SHIFT										0			// Revision ID Shift

// ============================================================================
// Offset 0x09: CC - Class Code
// ============================================================================
#define PCI_CC_PI_MASK											0x000000FF	// Programming Interface (RO, Reset = ImplSpec)
#define PCI_CC_PI_SHIFT											0			// Programming Interface Shift
#define PCI_CC_SCC_MASK											0x0000FF00	// Sub Class Code (RO, Reset = ImplSpec)
#define PCI_CC_SCC_SHIFT										8			// Sub Class Code Shift
#define PCI_CC_BCC_MASK											0x00FF0000	// Base Class Code (RO, Reset = 1)
#define PCI_CC_BCC_SHIFT										16			// Base Class Code Shift

// ============================================================================
// Offset 0x0C: CLS – Cache Line Size
// ============================================================================
#define PCI_CLS_CLS_MASK										0x000000FF	// Cache Line Size (RW, Reset = 0)
#define PCI_CLS_CLS_SHIFT										0			// Cache Line Size Shift

// ============================================================================
// Offset 0x0D: MLT – Master Latency Timer
// ============================================================================
#define PCI_MLT_MLT_MASK										0x000000FF	// Master Latency Timer (RW, Reset = 0)
#define PCI_MLT_MLT_SHIFT										0			// Master Latency Timer Shift

// ============================================================================
// Offset 0x0E: HTYPE – Header Type
// ============================================================================
#define PCI_HTYPE_HL_MASK										0x0000007F	// Header Layout (RO, Reset = 0)
#define PCI_HTYPE_HL_SHIFT										0			// Header Layout Shift
#define PCI_HTYPE_MFD											(1 << 7)	// Multi-Function Device (RO, Reset = ImplSpec)

// ============================================================================
// Offset 0x0F: BIST – Built In Self Test
// ============================================================================
#define PCI_BIST_CC_MASK										0x0000000F	// Completion Code (RO, Reset = 0)
#define PCI_BIST_CC_SHIFT										0			// Completion Code Shift
#define PCI_BIST_SB												(1 << 6)	// Stat BIST (RW, Reset = 0)
#define PCI_BIST_BC												(1 << 7)	// BIST Capable (RO, Reset = 1)

typedef struct
{
	struct
	{
		uint8_t bus;
		uint8_t slot;
		uint8_t func;
	} address;

	struct
	{
		uint16_t vendor_id;
		uint16_t device_id;
		uint16_t command;
		uint16_t status;
		uint8_t revision_id;
		uint8_t progif;
		uint8_t subclass;
		uint8_t class_code;
		uint8_t cache_line_size;
		uint8_t latency_timer;
		uint8_t header_type;
		uint8_t bist;

		union
		{
			struct
			{
				uint32_t bar[6];
				uint32_t cardbus_cis;
				uint16_t subsystem_vendor_id;
				uint16_t subsystem_device_id;
				uint32_t expansion_rom;
				uint8_t capabilities;
				uint8_t reserved[7];
				uint8_t interrupt_line;
				uint8_t interrupt_pin;
				uint8_t min_grant;
				uint8_t max_latency;
			} type0;

			struct
			{
				uint32_t bar[2];
				uint8_t primary_bus;
				uint8_t secondary_bus;
				uint8_t subordinate_bus;
				uint8_t secondary_timer;
				uint8_t io_base;
				uint8_t io_limit;
				uint16_t secondary_status;
				uint16_t memory_base;
				uint16_t memory_limit;
				uint16_t prefetch_memory_base;
				uint16_t prefetch_memory_limit;
				uint32_t prefetch_memory_base_upper;
				uint32_t prefetch_memory_limit_upper;
				uint16_t io_base_upper;
				uint16_t io_limit_upper;
				uint8_t capabilities;
				uint8_t reserved[3];
				uint32_t expansion_rom;
				uint8_t interrupt_line;
				uint8_t interrupt_pin;
				uint16_t bridge_control;
			} type1;
		};
	} config_header;
} pci_device_t;

int getPCIDeviceCount(void);
pci_device_t* getPCIDevice(int index);
void enablePCIBusMastering(pci_device_t *device);
void enablePCIMemorySpace(pci_device_t *device);

uint8_t readPCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint32_t readPCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void writePCIConfigByte(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint8_t data);
void writePCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint16_t data);
void writePCIConfigDWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t data);

#endif
