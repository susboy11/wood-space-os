/*
 * ============================================================================
 * File:		sata_fis.h
 * Description:	SATA Frame Information Structure (FIS) definitions
 * Created:		2026-11-05
 * Author:		susboy11
 * ============================================================================
 */

#ifndef SATA_FIS_H
#define SATA_FIS_H

#include <stdint.h>

// ============================================================================
// FIS Type Values
// ============================================================================
#define SATA_FIS_TYPE_REG_H2D									0x27		// Register FIS - Host To Device
#define SATA_FIS_TYPE_REG_D2H									0x34		// Register FIS - Device To Host
#define SATA_FIS_TYPE_DMA_ACT									0x39		// DMA Activate FIS - Device To Host
#define SATA_FIS_TYPE_DMA_SETUP									0x41		// DMA Setup FIS - Bi-Directional
#define SATA_FIS_TYPE_DATA										0x46		// Data FIS - Bi-Directional
#define SATA_FIS_TYPE_BIST										0x58		// BIST Activate FIS - Bi-Directional
#define SATA_FIS_TYPE_PIO_SETUP									0x5F		// PIO Setup FIS - Device To Host
#define SATA_FIS_TYPE_DEV_BITS									0xA1		// Set Device Bits FIS - Device To Host

// ============================================================================
// 0x27: Register FIS - Host To Device Flags
// ============================================================================
#define SATA_FIS_TYPE_REG_H2D_FLAGS_PMPORT_MASK					0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_REG_H2D_FLAGS_PMPORT_SHIFT				0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_REG_H2D_FLAGS_C							(1 << 7)	// 1 = Command, 0 = Control

// ============================================================================
// 0x34: Register FIS - Device To Host Flags
// ============================================================================
#define SATA_FIS_TYPE_REG_D2H_FLAGS_PMPORT_MASK					0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_REG_D2H_FLAGS_PMPORT_SHIFT				0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_REG_D2H_FLAGS_I							(1 << 6)	// Interrupt Bit

// ============================================================================
// 0x39: DMA Activate FIS - Device To Host Flags
// ============================================================================
#define SATA_FIS_TYPE_DMA_ACTIVATE_FLAGS_MASK					0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_DMA_ACTIVATE_FLAGS_SHIFT					0			// Port Multiplier Port Shift

// ============================================================================
// 0x41: DMA Setup FIS - Bi-Directional Flags
// ============================================================================
#define SATA_FIS_TYPE_DMA_SETUP_FLAGS_PMPORT_MASK				0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_DMA_SETUP_FLAGS_PMPORT_SHIFT				0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_DMA_SETUP_FLAGS_D							(1 << 5)	// Direction (1 = Device To Host, 0 = Host To Device)
#define SATA_FIS_TYPE_DMA_SETUP_FLAGS_I							(1 << 6)	// Interrupt Bit
#define SATA_FIS_TYPE_DMA_SETUP_FLAGS_A							(1 << 7)	// Auto-Activate

// ============================================================================
// 0x58: BIST Activate FIS - Bi-Directional Flags
// ============================================================================
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PMPORT_MASK			0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PMPORT_SHIFT			0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_MASK				0xF0		// Pattern Definition
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_SHIFT				4			// Pattern Definition Shift

// Pattern Definition Bits
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_P					(1 << 4)	// Primitive Bit
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_L					(1 << 5)	// Loopback Mode
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_F					(1 << 6)	// Far-End Transmit Only
#define SATA_FIS_TYPE_BIST_ACTIVATE_FLAGS_PD_V					(1 << 7)	// Vendor Specific

// ============================================================================
// 0x5F: PIO Setup FIS - Device To Host Flags
// ============================================================================
#define SATA_FIS_TYPE_PIO_SETUP_FLAGS_PMPORT_MASK				0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_PIO_SETUP_FLAGS_PMPORT_SHIFT				0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_PIO_SETUP_FLAGS_D							(1 << 5)	// Direction (1 = Device To Host, 0 = Host To Device)
#define SATA_FIS_TYPE_PIO_SETUP_FLAGS_I							(1 << 6)	// Interrupt Bit

// ============================================================================
// 0xA1: Set Device Bits FIS - Device To Host Flags
// ============================================================================
#define SATA_FIS_TYPE_SET_DEVICE_BITS_FLAGS_PMPORT_MASK			0x0F		// Port Multiplier Port
#define SATA_FIS_TYPE_SET_DEVICE_BITS_FLAGS_PMPORT_SHIFT		0			// Port Multiplier Port Shift
#define SATA_FIS_TYPE_SET_DEVICE_BITS_FLAGS_I					(1 << 6)	// Interrupt Bit
#define SATA_FIS_TYPE_SET_DEVICE_BITS_FLAGS_N					(1 << 7)	// Notification Bit

typedef struct
{
	uint8_t	fis_type;											// SATA_FIS_TYPE_REG_H2D (0x27)
	uint8_t flags;												// Flags
	uint8_t	command;											// ATA Command Code
	uint8_t	featurel;											// Feature Register (Low)
	uint8_t	lba0;												// LBA Low
	uint8_t	lba1;												// LBA Mid
	uint8_t	lba2;												// LBA High
	uint8_t	device;												// Device Register
	uint8_t	lba3;												// LBA Low (Expanded)
	uint8_t	lba4;												// LBA Mid (Expanded)
	uint8_t	lba5;												// LBA High (Expanded)
	uint8_t	featureh;											// Feature Register (High)
	uint8_t	countl;												// Sector Count (Low)
	uint8_t	counth;												// Sector Count (High)
	uint8_t	icc;												// Isochronous Command Completion
	uint8_t	control;											// Control Register
	uint8_t	reserved0[4];										// Reserved
} __attribute__((packed)) sata_fis_reg_h2d_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_REG_D2H (0x34)
	uint8_t flags;												// Flags
	uint8_t status;												// Status Register
	uint8_t error;												// Error Register
	uint8_t lba0;												// LBA Low
	uint8_t lba1;												// LBA Mid
	uint8_t lba2;												// LBA High
	uint8_t device;												// Device Register
	uint8_t lba3;												// LBA Low (Expanded)
	uint8_t lba4;												// LBA Mid (Expanded)
	uint8_t lba5;												// LBA High (Expanded)
	uint8_t reserved0;											// Reserved
	uint8_t countl;												// Sector Count (Low)
	uint8_t counth;												// Sector Count (High)
	uint8_t reserved1[6];										// Reserved
} __attribute__((packed)) sata_fis_reg_d2h_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_DMA_ACT (0x39)
	uint8_t flags;												// Flags
	uint8_t reserved0[2];										// Reserved
} __attribute__((packed)) sata_fis_dma_act_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_DMA_SETUP (0x41)
	uint8_t flags;												// Flags
	uint8_t reserved0[2];										// Reserved
	uint64_t dma_buffer_id;										// DMA Buffer Identifier
	uint32_t reserved1;											// Reserved
	uint32_t dma_buffer_offset;									// DMA Buffer Offset
	uint32_t dma_transfer_count;								// DMA Transfer Count
	uint32_t reserved2;											// Reserved
} __attribute__((packed)) sata_fis_dma_setup_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_BIST (0x58)
	uint8_t flags;												// Flags
	uint8_t reserved0;											// Reserved
	uint32_t data1;												// Data1
	uint32_t data2;												// Data2
	uint8_t reserved1;											// Reserved
} __attribute__((packed)) sata_fis_bist_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_PIO_SETUP (0x5F)
	uint8_t flags;												// Flags
	uint8_t status;												// Status Register
	uint8_t error;												// Error Register
	uint8_t lba0;												// LBA Low
	uint8_t lba1;												// LBA Mid
	uint8_t lba2;												// LBA High
	uint8_t device;												// Device Register
	uint8_t lba3;												// LBA Low (Expanded)
	uint8_t lba4;												// LBA Mid (Expanded)
	uint8_t lba5;												// LBA High (Expanded)
	uint8_t reserved0;											// Reserved
	uint8_t countl;												// Sector Count (Low)
	uint8_t counth;												// Sector Count (High)
	uint8_t reserved1;											// Reserved
	uint8_t e_status;											// New Status (End Status)
	uint16_t transfer_count;									// Transfer Count
	uint8_t reserved2[2];										// Reserved
} __attribute__((packed)) sata_fis_pio_setup_t;

typedef struct
{
	uint8_t fis_type;											// SATA_FIS_TYPE_DEV_BITS (0xA1)
	uint8_t flags;												// Flags
	uint8_t status;												// Status Register
	uint8_t error;												// Error Register
	uint32_t sactive;											// SActive Register
} __attribute__((packed)) sata_fis_dev_bits_t;

#endif