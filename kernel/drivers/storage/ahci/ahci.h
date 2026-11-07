/*
 * ============================================================================
 * File:		ahci.h
 * Description:	AHCI definitions
 * Created:		2026-10-10
 * Author:		susboy11
 * ============================================================================
 */
 
#ifndef AHCI_H
#define AHCI_H

#include <stdint.h>

// ============================================================================
// Generic Host Control Registers
// ============================================================================
#define AHCI_GHC_CAP											0x00		// Host Capabilities
#define AHCI_GHC_GHC											0x04		// Global Host Control
#define AHCI_GHC_IS												0x08		// Interrupt Status
#define AHCI_GHC_PI												0x0C		// Ports Implemented
#define AHCI_GHC_VS												0x10		// Version
#define AHCI_GHC_CCC_CTL										0x14		// Command Completion Coalescing Control
#define AHCI_GHC_CCC_PORTS										0x18		// Command Completion Coalescing Ports
#define AHCI_GHC_EM_LOC											0x1C		// Enclosure Management Location
#define AHCI_GHC_EM_CTL											0x20		// Enclosure Management Control
#define AHCI_GHC_CAP2											0x24		// Host Capabilities Extended
#define AHCI_GHC_BOHC											0x28		// BIOS/OS Handoff Control and Status

// ============================================================================
// Offset 0x00: CAP – HBA Capabilities (Generic Host Control)
// ============================================================================
#define AHCI_GHC_CAP_NP_MASK									0x0000001F	// Number Of Ports (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_NP_SHIFT									0			// Number Of Ports Shift
#define AHCI_GHC_CAP_SXS										(1 << 5)	// Supports External SATA (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_EMS										(1 << 6)	// Enclosure Management Supported (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_CCCS										(1 << 7)	// Command Completion Coalescing Supported (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_NCS_MASK									0x00001F00	// Number Of Command Slots (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_NCS_SHIFT									8			// Number Of Command Slots Shift
#define AHCI_GHC_CAP_PSC										(1 << 13)	// Partial State Capable (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SSC										(1 << 14)	// Slumber State Capable (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_PMD										(1 << 15)	// PIO Multiple DRQ Block (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_FBSS										(1 << 16)	// FIS-based Switching Supported (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SPM										(1 << 17)	// Supports Port Multiplier (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SAM										(1 << 18)	// Supports AHCI Mode Only (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_ISS_MASK									0x00F00000	// Interface Speed Support (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_ISS_SHIFT									20			// Interface Speed Support Shift
#define AHCI_GHC_CAP_SCLO										(1 << 24)   // Supports Command List Override (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SAL										(1 << 25)	// Supports Activity LED (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SALP										(1 << 26)	// Supports Aggressive Link Power Management (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SSS										(1 << 27)	// Supports Staggered Spin-Up (RO, Reset = HwInit)
#define AHCI_GHC_CAP_SMPS										(1 << 28)	// Supports Mechanical Presence Switch (RO, Reset = HwInit)
#define AHCI_GHC_CAP_SSNTF										(1 << 29)	// Supports SNotification Register (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_SNCQ										(1 << 30)	// Supports Native Command Queuing (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP_S64A										(1 << 31)	// Supports 64-Bit Addressing (RO, Reset = ImplSpec)

// Interface Speed Support Values
#define AHCI_GHC_CAP_ISS_GEN1									1			// Gen 1 (1.5 Gbps)
#define AHCI_GHC_CAP_ISS_GEN2									2			// Gen 2 (3 Gbps)
#define AHCI_GHC_CAP_ISS_GEN3									3			// Gen 3 (6 Gbps)

// ============================================================================
// Offset 0x04: GHC – Global HBA Control (Generic Host Control)
// ============================================================================
#define AHCI_GHC_GHC_HR											(1 << 0)	// HBA Reset (RW1, Reset = 0)
#define AHCI_GHC_GHC_IE											(1 << 1)	// Interrupt Enable (RW, Reset = 0)
#define AHCI_GHC_GHC_MRSM										(1 << 2)	// MSI Revert To Single Message (RO, Reset = 0)
#define AHCI_GHC_GHC_AE											(1 << 31)	// AHCI Enable (RW/RO, Reset = ImplSpec)

// ============================================================================
// Offset 0x08: IS – Interrupt Status Register (Generic Host Control)
// ============================================================================
#define AHCI_GHC_IS_IPS_MASK									0xFFFFFFFF	// Interrupt Pending Status (RWC, Reset = 0)
#define AHCI_GHC_IS_IPS_SHIFT									0			// Interrupt Pending Status Shift

// ============================================================================
// Offset 0x0C: PI – Ports Implemented (Generic Host Control)
// ============================================================================
#define AHCI_GHC_PI_PI_MASK										0xFFFFFFFF	// Port Implemented (RO, Reset = HwInit)
#define AHCI_GHC_PI_PI_SHIFT									0			// Port Implemented Shift

// ============================================================================
// Offset 0x10: VS – AHCI Version (Generic Host Control)
// ============================================================================
#define AHCI_GHC_VS_MNR_MASK									0x0000FFFF	// Minor Version Number (RO, Reset = Version)
#define AHCI_GHC_VS_MNR_SHIFT									0			// Minor Version Number Shift
#define AHCI_GHC_VS_MJR_MASK									0xFFFF0000	// Major Version Number (RO, Reset = Version)
#define AHCI_GHC_VS_MJR_SHIFT									16			// Major Version Number Shift

// ============================================================================
// Offset 0x14: CCC_CTL – Command Completion Coalescing Control (Generic Host Control)
// ============================================================================
#define AHCI_GHC_CCC_CTL_EN										(1 << 0)	// Enable (RW, Reset = 0)
#define AHCI_GHC_CCC_CTL_INT_MASK								0x000000F8	// Interrupt (RO, Reset = ImplSpec)
#define AHCI_GHC_CCC_CTL_INT_SHIFT								3			// Interrupt Shift
#define AHCI_GHC_CCC_CTL_CC_MASK								0x0000FF00	// Command Completions (RW, Reset = 1)
#define AHCI_GHC_CCC_CTL_CC_SHIFT								8			// Command Completions Shift
#define AHCI_GHC_CCC_CTL_TV_MASK								0xFFFF0000	// Timeout Value (RW, Reset = 1)
#define AHCI_GHC_CCC_CTL_TV_SHIFT								16			// Timeout Value Shift

// ============================================================================
// Offset 0x18: CCC_PORTS – Command Completion Coalescing Ports (Generic Host Control)
// ============================================================================
#define AHCI_GHC_CCC_PORTS_PRT_MASK								0xFFFFFFFF	// Ports (RW, Reset = 0)
#define AHCI_GHC_CCC_PORTS_PRT_SHIFT							0			// Ports Shift

// ============================================================================
// Offset 0x1C: EM_LOC – Enclosure Management Location (Generic Host Control)
// ============================================================================
#define AHCI_GHC_EM_LOC_SZ_MASK									0x0000FFFF	// Buffer Size (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_LOC_SZ_SHIFT								0			// Buffer Size Shift
#define AHCI_GHC_EM_LOC_OFST_MASK								0xFFFF0000	// Offset (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_LOC_OFST_SHIFT								16			// Offset Shift

// ============================================================================
// Offset 0x20: EM_CTL – Enclosure Management Control (Generic Host Control)
// ============================================================================
#define AHCI_GHC_EM_CTL_STS_MR									(1 << 0)	// Message Received (RWC, Reset = 0)
#define AHCI_GHC_EM_CTL_CTL_TM									(1 << 8)	// Transmit Message (RW1, Reset = 0)
#define AHCI_GHC_EM_CTL_CTL_RST									(1 << 9)	// Reset (RW1, Reset = 0)
#define AHCI_GHC_EM_CTL_SUPP_LED								(1 << 16)	// LED Message Types (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_SUPP_SAFTE								(1 << 17)	// SAF-TE Enclosure Management Messages (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_SUPP_SES2								(1 << 18)	// SES-2 Enclosure Management Messages (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_SUPP_SGPIO								(1 << 19)	// SGPIO Enclosure Management Messages (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_ATTR_SMB								(1 << 24)	// Single Message Buffer (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_ATTR_XMT								(1 << 25)	// Transmit Only (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_ATTR_ALHD								(1 << 26)	// Activity LED Hardware Driven (RO, Reset = ImplSpec)
#define AHCI_GHC_EM_CTL_ATTR_PM									(1 << 27)	// Port Multiplier Support (RO, Reset = ImplSpec)

// ============================================================================
// Offset 0x24: CAP2 – HBA Capabilities Extended (Generic Host Control)
// ============================================================================
#define AHCI_GHC_CAP2_BOH										(1 << 0)	// BIOS/OS Handoff (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP2_NVMP										(1 << 1)	// NVMHCI Present (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP2_APST										(1 << 2)	// Automatic Partial To Slumber Transitions (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP2_SDS										(1 << 3)	// Supports Device Sleep (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP2_SADM										(1 << 4)	// Supports Aggressive Device Sleep Management (RO, Reset = ImplSpec)
#define AHCI_GHC_CAP2_DESO										(1 << 5)	// DevSleep Entrance From Slumber Only (RO, Reset = ImplSpec)

// ============================================================================
// Offset 0x28: BOHC – BIOS/OS Handoff Control and Status (Generic Host Control)
// ============================================================================
#define AHCI_GHC_BOHC_BOS										(1 << 0)	// BIOS Owned Semaphore (RW, Reset = 0)
#define AHCI_GHC_BOHC_OOS										(1 << 1)	// OS Owned Semaphore (RW, Reset = 0)
#define AHCI_GHC_BOHC_SOOE										(1 << 2)	// SMI On OS Ownership Change Enable (RW, Reset = 0)
#define AHCI_GHC_BOHC_OOC										(1 << 3)	// OS Ownership Change (RWC, Reset = 0)
#define AHCI_GHC_BOHC_BB										(1 << 4)	// BIOS Busy (RW, Reset = 0)

// ============================================================================
// Port registers (Port offset = 0x100 + (PI Asserted Bit Position * 0x80)
// ============================================================================
#define AHCI_PxCLB												0x00		// Port x Command List Base Address
#define AHCI_PxCLBU												0x04		// Port x Command List Base Address Upper
#define AHCI_PxFB												0x08		// Port x FIS Base Address
#define AHCI_PxFBU												0x0C		// Port x FIS Base Address Upper
#define AHCI_PxIS												0x10		// Port x Interrupt Status
#define AHCI_PxIE												0x14		// Port x Interrupt Enable
#define AHCI_PxCMD												0x18		// Port x Command and Status
#define AHCI_PxTFD												0x20		// Port x Task File Data
#define AHCI_PxSIG												0x24		// Port x Signature
#define AHCI_PxSSTS												0x28		// Port x Serial ATA Status (SCR0: SStatus)
#define AHCI_PxSCTL												0x2C		// Port x Serial ATA Control (SCR2: SControl)
#define AHCI_PxSERR												0x30		// Port x Serial ATA Error (SCR1: SError)
#define AHCI_PxSACT												0x34		// Port x Serial ATA Active (SCR3: SActive)
#define AHCI_PxCI												0x38		// Port x Command Issue
#define AHCI_PxSNTF												0x3C		// Port x Serial ATA Notification (SCR4: SNotification)
#define AHCI_PxFBS												0x40		// Port x FIS-Based Switching Control
#define AHCI_PxDEVSLP											0x44		// Port x Device Sleep
#define AHCI_PxVS												0x70		// Port x Vendor Specific

// Optionally
#define AHCI_PORT_BASE											0x100		// Port Base Address
#define AHCI_PORT_SIZE											0x80		// Port Size

// ============================================================================
// Offset 0x00: PxCLB – Port x Command List Base Address
// ============================================================================
#define AHCI_PxCLB_CLB_MASK										0xFFFFFC00	// Command List Base Address (RW, Reset = ImplSpec)
#define AHCI_PxCLB_CLB_SHIFT									10			// Command List Base Address Shift

// ============================================================================
// Offset 0x04: PxCLBU – Port x Command List Base Address Upper
// ============================================================================
#define AHCI_PxCLBU_CLBU_MASK									0xFFFFFFFF	// Command List Base Address Upper (RW, Reset = ImplSpec)
#define AHCI_PxCLBU_CLBU_SHIFT									0			// Command List Base Address Upper Shift

// ============================================================================
// Offset 0x08: PxFB – Port x FIS Base Address
// ============================================================================
#define AHCI_PxFB_FB_MASK										0xFFFFFF00	// FIS Base Address (RW, Reset = ImplSpec)
#define AHCI_PxFB_FB_SHIFT										8			// FIS Base Address Shift

// ============================================================================
// Offset 0x0C: PxFBU – Port x FIS Base Address Upper
// ============================================================================
#define AHCI_PxFBU_FBU_MASK										0xFFFFFFFF	// FIS Base Address Upper (RW, Reset = ImplSpec)
#define AHCI_PxFBU_FBU_SHIFT									0			// FIS Base Address Upper Shift

// ============================================================================
// Offset 0x10: PxIS – Port x Interrupt Status
// ============================================================================
#define AHCI_PxIS_DHRS											(1 << 0)	// Device To Host Register FIS Interrupt (RWC, Reset = 0)
#define AHCI_PxIS_PSS											(1 << 1)    // PIO Setup FIS Interrupt (RWC , Reset = 0)
#define AHCI_PxIS_DSS											(1 << 2)	// DMA Setup FIS Interrupt (RWC , Reset = 0)
#define AHCI_PxIS_SDBS											(1 << 3)	// Set Device Bits Interrupt (RWC , Reset = 0)
#define AHCI_PxIS_UFS											(1 << 4)	// Unknown FIS Interrupt (RO , Reset = 0)
#define AHCI_PxIS_DPS											(1 << 5)	// Descriptor Processed (RWC , Reset = 0)
#define AHCI_PxIS_PCS											(1 << 6)	// Port Connect Change Status (RO , Reset = 0)
#define AHCI_PxIS_DMPS											(1 << 7)	// Device Mechanical Presence Status (RWC , Reset = 0)
#define AHCI_PxIS_PRCS											(1 << 22)	// PhyRdy Change Status (RO , Reset = 0)
#define AHCI_PxIS_IPMS											(1 << 23)	// Incorrect Port Multiplier Status (RWC , Reset = 0)
#define AHCI_PxIS_OFS											(1 << 24)	// Overflow Status (RWC , Reset = 0)
#define AHCI_PxIS_INFS											(1 << 26)	// Interface Non-fatal Error Status (RWC , Reset = 0)
#define AHCI_PxIS_IFS											(1 << 27)	// Interface Fatal Error Status (RWC , Reset = 0)
#define AHCI_PxIS_HBDS											(1 << 28)	// Host Bus Data Error Status (RWC , Reset = 0)
#define AHCI_PxIS_HBFS											(1 << 29)	// Host Bus Fatal Error Status (RWC , Reset = 0)
#define AHCI_PxIS_TFES											(1 << 30)	// Task File Error Status (RWC , Reset = 0)
#define AHCI_PxIS_CPDS											(1 << 31)	// Cold Port Detect Status (RWC , Reset = 0)

// ============================================================================
// Offset 0x14: PxIE – Port x Interrupt Enable
// ============================================================================
#define AHCI_PxIE_DHRE											(1 << 0)	// Device to Host Register FIS Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_PSE											(1 << 1)	// PIO Setup FIS Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_DSE											(1 << 2)	// DMA Setup FIS Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_SDBE											(1 << 3)	// Set Device Bits FIS Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_UFE											(1 << 4)	// Unknown FIS Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_DPE											(1 << 5)	// Descriptor Processed Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_PCE											(1 << 6)	// Port Change Interrupt Enable (RW, Reset = 0)
#define AHCI_PxIE_DMPE											(1 << 7)	// Device Mechanical Presence Enable (RW/RO, Reset = 0)
#define AHCI_PxIE_PRCE											(1 << 22)	// PhyRdy Change Interrupt Enable (RW/RO, Reset = 0)
#define AHCI_PxIE_IPME											(1 << 23)	// Incorrect Port Multiplier Enable (RW, Reset = 0)
#define AHCI_PxIE_OFE											(1 << 24)	// Overflow Enable (RW, Reset = 0)
#define AHCI_PxIE_INFE											(1 << 26)	// Interface Non-Fatal Error Enable (RW, Reset = 0)
#define AHCI_PxIE_IFE											(1 << 27)	// Interface Fatal Error Enable (RW, Reset = 0)
#define AHCI_PxIE_HBDE											(1 << 28)	// Host Bus Data Error Enable (RW, Reset = 0)
#define AHCI_PxIE_HBFE											(1 << 29)	// Host Bus Fatal Error Enable (RW, Reset = 0)
#define AHCI_PxIE_TFEE											(1 << 30)	// Task File Error Enable (RW, Reset = 0)
#define AHCI_PxIE_CPDE											(1 << 31)	// Cold Presence Detect Enable (RW/RO, Reset = 0)

// ============================================================================
// Offset 0x18: PxCMD – Port x Command and Status
// ============================================================================
#define AHCI_PxCMD_ST											(1 << 0)	// Start (RW, Reset = 0)
#define AHCI_PxCMD_SUD											(1 << 1)	// Spin-Up Device (RW/RO, Reset = 0/1)
#define AHCI_PxCMD_POD											(1 << 2)	// Power On Device (RW/RO, Reset = 0/1)
#define AHCI_PxCMD_CLO											(1 << 3)	// Command List Override (RW1, Reset = 0)
#define AHCI_PxCMD_FRE											(1 << 4)	// FIS Receive Enable (RW, Reset = 0)
#define AHCI_PxCMD_CCS_MASK										0x00001F00	// Current Command Slot (RO, Reset = 0h)
#define AHCI_PxCMD_CCS_SHIFT									8			// Current Command Slot Shift
#define AHCI_PxCMD_MPSS											(1 << 13)	// Mechanical Presence Switch State (RO, Reset = see desc)
#define AHCI_PxCMD_FR											(1 << 14)	// FIS Receive Running (RO, Reset = 0)
#define AHCI_PxCMD_CR											(1 << 15)   // Command List Running (RO, Reset = 0)
#define AHCI_PxCMD_CPS											(1 << 16)	// Cold Presence State (RO, Reset = see desc)
#define AHCI_PxCMD_PMA											(1 << 17)	// Port Multiplier Attached (RW/RO, Reset = 0)
#define AHCI_PxCMD_HPCP											(1 << 18)	// Hot Plug Capable Port (RO, Reset = HwInit)
#define AHCI_PxCMD_MPSP											(1 << 19)	// Mechanical Presence Switch Attached (RO, Reset = HwInit)
#define AHCI_PxCMD_CPD											(1 << 20)	// Cold Presence Detection (RO, Reset = HwInit)
#define AHCI_PxCMD_ESP											(1 << 21)	// External SATA Port (RO, Reset = HwInit)
#define AHCI_PxCMD_FBSCP										(1 << 22)	// FIS-Based Switching Capable Port (RO, Reset = HwInit)
#define AHCI_PxCMD_APSTE										(1 << 23)	// Automatic Partial to Slumber Transitions (RW, Reset = 0)
#define AHCI_PxCMD_ATAPI										(1 << 24)	// Device Is ATAPI (RW, Reset = 0)
#define AHCI_PxCMD_DLAE											(1 << 25)	// Drive LED On ATAPI (RW, Reset = 0)
#define AHCI_PxCMD_ALPE											(1 << 26)	// Aggressive Link Power Management Enable (RW/RO, Reset = 0)
#define AHCI_PxCMD_ASP											(1 << 27)	// Aggressive Slumber/Partial (RW/RO, Reset = 0)		
#define AHCI_PxCMD_ICC_MASK										0xF0000000	// Interface Communication Control (RW, Reset = 0)
#define AHCI_PxCMD_ICC_SHIFT									28			// Interface Communication Control Shift

// Interface Communication Control Values
#define AHCI_PxCMD_ICC_NOI										0x00		// No-Op / Idle
#define AHCI_PxCMD_ICC_A										0x01		// Active
#define AHCI_PxCMD_ICC_P										0x02		// Partial
#define AHCI_PxCMD_ICC_S										0x06		// Slumber
#define AHCI_PxCMD_ICC_DS										0x08		// DevSleep

// ============================================================================
// Offset 0x20: PxTFD – Port x Task File Data
// ============================================================================
#define AHCI_PxTFD_STS_MASK										0x000000FF	// Status (RO, Reset = 0x7F)
#define AHCI_PxTFD_STS_SHIFT									0			// Status Shift
#define AHCI_PxTFD_ERR_MASK										0x0000FF00	// Error (RO, Reset = 0)
#define AHCI_PxTFD_ERR_SHIFT									8			// Error Shift

// Status Bits
#define AHCI_PxTFD_STS_ERR										(1 << 0)	// Indicates An Error During The Transfer
#define AHCI_PxTFD_STS_CS1_MASK									0x06		// Command Specific 1 
#define AHCI_PxTFD_STS_CS1_SHIFT								1			// Command Specific 1 Shift
#define AHCI_PxTFD_STS_DRQ										(1 << 3)	// Indicates A Data Transfer Is Requested
#define AHCI_PxTFD_STS_CS2_MASK									0x70		// Command Specific 2 
#define AHCI_PxTFD_STS_CS2_SHIFT								4			// Command Specific 2 Shift
#define AHCI_PxTFD_STS_BSY										(1 << 7)	// Indicates The Interface Is Busy

// ============================================================================
// Offset 0x24: PxSIG – Port x Signature
// ============================================================================
#define AHCI_PxSIG_SIG_MASK										0xFFFFFFFF	// Signature (RO, Reset = FFFFFFFFh)
#define AHCI_PxSIG_SIG_SHIFT									0

// Signature Bits
#define AHCI_PxSIG_SIG_SCR_MASK									0x000000FF	// Sector Count Register (RO, Reset = 0xFF)
#define AHCI_PxSIG_SIG_SCR_SHIFT								0			// Sector Count Register Shift
#define AHCI_PxSIG_SIG_LBALR_MASK								0x0000FF00	// LBA Low Register (RO, Reset = 0xFF)
#define AHCI_PxSIG_SIG_LBALR_SHIFT								8			// LBA Low Register Shift
#define AHCI_PxSIG_SIG_LBAMR_MASK								0x00FF0000	// LBA Mid Register (RO, Reset = 0xFF)
#define AHCI_PxSIG_SIG_LBAMR_SHIFT								16			// LBA Mid Register Shift
#define AHCI_PxSIG_SIG_LBAHR_MASK								0xFF000000	// LBA High Register (RO, Reset = 0xFF)
#define AHCI_PxSIG_SIG_LBAHR_SHIFT								24			// LBA High Register Shift

// ============================================================================
// Offset 0x28: PxSSTS – Port x Serial ATA Status (SCR0: SStatus)
// ============================================================================
#define AHCI_PxSSTS_DET_MASK									0x0000000F	// Device Detection (RO, Reset = 0)
#define AHCI_PxSSTS_DET_SHIFT									0			// Device Detection Shift
#define AHCI_PxSSTS_SPD_MASK									0x000000F0	// Current Interface Speed (RO, Reset = 0)
#define AHCI_PxSSTS_SPD_SHIFT									4			// Current Interface Speed Shift
#define AHCI_PxSSTS_IPM_MASK									0x00000F00	// Interface Power Management (RO, Reset = 0)
#define AHCI_PxSSTS_IPM_SHIFT									8			// Interface Power Management Shift

// Device Detection Values
#define AHCI_PxSSTS_DET_NDD										0x00		// No Device Detected And Phy Communication Not Established
#define AHCI_PxSSTS_DET_DDCNE									0x01		// Device Presence Detected But Phy Communication Not Established
#define AHCI_PxSSTS_DET_DDCE									0x03		// Device Rresence Detected And Phy Communication Established
#define AHCI_PxSSTS_DET_OFF										0x04		// Phy In Offline Mode As A Result Of The Interface Being Disabled Or Running In A BIST Loopback Mode

// Current Interface Speed Values
#define AHCI_PxSSTS_SPD_NONE									0x00		// Device Not Present Or Communication Not Established
#define AHCI_PxSSTS_SPD_GEN1									0x01		// Generation 1 Communication Rate Negotiated
#define AHCI_PxSSTS_SPD_GEN2									0x02		// Generation 2 Communication Rate Negotiated
#define AHCI_PxSSTS_SPD_GEN3									0x03		// Generation 3 Communication Rate Negotiated

// Interface Power Management Values
#define AHCI_PxSSTS_IPM_NONE									0x00		// Device Not Present Or Communication Not Established
#define AHCI_PxSSTS_IPM_A										0x01		// Interface In Active State
#define AHCI_PxSSTS_IPM_P										0x02		// Interface In Partial Power Management State
#define AHCI_PxSSTS_IPM_S										0x06		// Interface In Slumber Power Management State
#define AHCI_PxSSTS_IPM_DS										0x08		// Interface In DevSleep Power Management State

// ============================================================================
// Offset 0x2C: PxSCTL – Port x Serial ATA Control (SCR2: SControl)
// ============================================================================
#define AHCI_PxSCTL_DET_MASK									0x0000000F	// Device Detection Initialization (RW, Reset = 0)
#define AHCI_PxSCTL_DET_SHIFT									0			// Device Detection Initialization Shift
#define AHCI_PxSCTL_SPD_MASK									0x000000F0	// Speed Allowed (RW, Reset = 0)
#define AHCI_PxSCTL_SPD_SHIFT									4			// Speed Allowed Shift
#define AHCI_PxSCTL_IPM_MASK									0x00000F00	// Interface Power Management Transitions Allowed (RW, Reset = 0)
#define AHCI_PxSCTL_IPM_SHIFT									8			// Interface Power Management Transitions Allowed Shift

// Device Detection Initialization Values
#define AHCI_PxSCTL_DET_NONE									0x00		// No Device Detection Or Initialization Action Requested
#define AHCI_PxSCTL_DET_RESET									0x01		// This Is Functionally Equivalent To A Hard Reset And Results In The Interface Being Reset And Communications Reinitialized
#define AHCI_PxSCTL_DET_DISABLE									0x04		// Disable The Serial ATA Interface And Put Phy In Offline Mode

// Speed Allowed Values
#define AHCI_PxSCTL_SPD_NS										0x00		// No Speed Negotiation Restrictions
#define AHCI_PxSCTL_SPD_LS_GEN1									0x01		// Limit Speed Negotiation To Generation 1 Communication Rate
#define AHCI_PxSCTL_SPD_LS_GEN2									0x02		// Limit Speed Negotiation To A Rate Not Greater Than Generation 2 Communication Rate
#define AHCI_PxSCTL_SPD_LS_GEN3									0x03		// Limit Speed Negotiation To A Rate Not Greater Than Generation 3 Communication Rate

// Interface Power Management Transitions Allowed Values
#define AHCI_PxSCTL_IPM_NONE									0x00		// No Interface Restrictions
#define AHCI_PxSCTL_IPM_TP										0x01		// Transitions To The Partial State Disabled
#define AHCI_PxSCTL_IPM_TS										0x02		// Transitions To The Slumber State Disabled
#define AHCI_PxSCTL_IPM_TPS										0x03		// Transitions To Both Partial And Slumber States Disabled
#define AHCI_PxSCTL_IPM_TDS										0x04		// Transitions To The DevSleep Power Management State Are Disabled
#define AHCI_PxSCTL_IPM_TPDS									0x05		// Transitions To The Partial And DevSleep Power Management States Are Disabled
#define AHCI_PxSCTL_IPM_TSDS									0x06		// Transitions To The Slumber And DevSleep Power Management States Are Disabled
#define AHCI_PxSCTL_IPM_TPSDS									0x07		// Transitions To The Partial, Slumber And DevSleep Power Management States Are Disabled

// ============================================================================
// Offset 0x30: PxSERR – Port x Serial ATA Error (SCR1: SError)
// ============================================================================
#define AHCI_PxSERR_ERR_MASK									0x0000FFFF	// Error (RWC, Reset = 0)
#define AHCI_PxSERR_ERR_SHIFT									0			// Error Shift
#define AHCI_PxSERR_DIAG_MASK									0xFFFF0000	// Diagnostics (RWC, Reset = 0)
#define AHCI_PxSERR_DIAG_SHIFT									16			// Diagnostics Shift

// Error Bits
#define AHCI_PxSERR_ERR_I										(1 << 0)	// Recovered Data Integrity Error
#define AHCI_PxSERR_ERR_M										(1 << 1)	// Recovered Communications Error
#define AHCI_PxSERR_ERR_T										(1 << 8)	// Transient Data Integrity Error
#define AHCI_PxSERR_ERR_C										(1 << 9)	// Persistent Communication Or Data Integrity Error
#define AHCI_PxSERR_ERR_P										(1 << 10)	// Protocol Error
#define AHCI_PxSERR_ERR_E										(1 << 11)	// Internal Error

// Diagnostics Bits
#define AHCI_PxSERR_DIAG_N										(1 << 16)	// PhyRdy Change
#define AHCI_PxSERR_DIAG_I										(1 << 17)	// Phy Internal Error
#define AHCI_PxSERR_DIAG_W										(1 << 18)	// Comm Wake
#define AHCI_PxSERR_DIAG_B										(1 << 19)	// 10B To 8B Decode Error
#define AHCI_PxSERR_DIAG_D										(1 << 20)	// Disparity Error
#define AHCI_PxSERR_DIAG_C										(1 << 21)	// CRC Error
#define AHCI_PxSERR_DIAG_H										(1 << 22)	// Handshake Error
#define AHCI_PxSERR_DIAG_S										(1 << 23)	// Link Sequence Error
#define AHCI_PxSERR_DIAG_T										(1 << 24)	// Transport State Transition Error
#define AHCI_PxSERR_DIAG_F										(1 << 25)	// Unknown FIS Type
#define AHCI_PxSERR_DIAG_X										(1 << 26)	// Exchanged

// ============================================================================
// Offset 0x34: PxSACT – Port x Serial ATA Active (SCR3: SActive)
// ============================================================================
#define AHCI_PxSACT_DS_MASK										0xFFFFFFFF	// Device Status (RW1, Reset = 0)
#define AHCI_PxSACT_DS_SHIFT									0			// Device Status Shift

// ============================================================================
// Offset 0x38: PxCI – Port x Command Issue
// ============================================================================
#define AHCI_PxCI_CI_MASK										0xFFFFFFFF	// Commands Issued (RW1, Reset = 0)
#define AHCI_PxCI_CI_SHIFT										0			// Commands Issued Shift

// ============================================================================
// Offset 0x3C: PxSNTF – Port x Serial ATA Notification (SCR4: SNotification)
// ============================================================================
#define AHCI_PxSNTF_PMN_MASK									0x0000FFFF	// PM Notify (RWC, Reset = 0)
#define AHCI_PxSNTF_PMN_SHIFT									0			// PM Notify Shift

// ============================================================================
// Offset 0x40: PxFBS: Port x FIS-based Switching Control
// ============================================================================
#define AHCI_PxFBS_EN											(1 << 0)	// Enable (RW, Reset = 0)
#define AHCI_PxFBS_DEC											(1 << 1)	// Device Error Clear (RW1, Reset = 0)
#define AHCI_PxFBS_SDE											(1 << 2)	// Single Device Error (RO, Reset = 0)
#define AHCI_PxFBS_DEV_MASK										0x00000F00	// Device To Issue (RW, Reset = 0)
#define AHCI_PxFBS_DEV_SHIFT									8			// Device To Issue Shift
#define AHCI_PxFBS_ADO_MASK										0x0000F000	// Active Device Optimization (RO, Reset = ImplSpec)
#define AHCI_PxFBS_ADO_SHIFT									12			// Active Device Optimization Shift
#define AHCI_PxFBS_DWE_MASK										0x000F0000	// Device With Error (RO, Reset = 0)
#define AHCI_PxFBS_DWE_SHIFT									16			// Device With Error Shift

// ============================================================================
// Offset 0x44: PxDEVSLP – Port x Device Sleep
// ============================================================================
#define AHCI_PxDEVSLP_ADSE										(1 << 0)	// Aggressive Device Sleep Enable (RW/RO, Reset = ImplSpec)
#define AHCI_PxDEVSLP_DSP										(1 << 1)	// Device Sleep Present (RO, Reset = ImplSpec)
#define AHCI_PxDEVSLP_DETO_MASK									0x000003FC	// Device Sleep Exit Timeout (RW/RO, Reset = ImplSpec)
#define AHCI_PxDEVSLP_DETO_SHIFT								2			// Device Sleep Exit Timeout Shift
#define AHCI_PxDEVSLP_MDAT_MASK									0x00007C00	// Minimum Device Sleep Assertion Time (RW/RO, Reset = ImplSpec)
#define AHCI_PxDEVSLP_MDAT_SHIFT								10			// Minimum Device Sleep Assertion Time Shift
#define AHCI_PxDEVSLP_DITO_MASK									0x01FF8000	// Device Sleep Idle Timeout (RW/RO, Reset = ImplSpec)
#define AHCI_PxDEVSLP_DITO_SHIFT								15			// Device Sleep Idle Timeout Shift
#define AHCI_PxDEVSLP_DM_MASK									0x1E000000	// DITO Multiplier (RO, Reset = HwInit)
#define AHCI_PxDEVSLP_DM_SHIFT									25			// DITO Multiplier Shift

// ============================================================================
// Command Header Flags
// ============================================================================
#define AHCI_CMD_HDR_FLAGS_CFL_MASK								0x0000001F	// Command FIS Length
#define AHCI_CMD_HDR_FLAGS_CFL_SHIFT							0        	// Command FIS Length Shift
#define AHCI_CMD_HDR_FLAGS_A									(1 << 5)	// ATAPI
#define AHCI_CMD_HDR_FLAGS_W									(1 << 6)	// Write
#define AHCI_CMD_HDR_FLAGS_P									(1 << 7)	// Prefetchable
#define AHCI_CMD_HDR_FLAGS_R									(1 << 8)	// Reset
#define AHCI_CMD_HDR_FLAGS_B									(1 << 9)	// BIST
#define AHCI_CMD_HDR_FLAGS_C									(1 << 10)	// Clear Busy Upon R_OK
#define AHCI_CMD_HDR_FLAGS_PMP_MASK								0x0000F000	// Port Multiplier Port
#define AHCI_CMD_HDR_FLAGS_PMP_SHIFT							12			// Port Multiplier Port Shift

// ============================================================================
// PRDT DBC
// ============================================================================
#define AHCI_PRDT_DBC_DBC_MASK									0x001FFFFF	// Data Byte Count
#define AHCI_PRDT_DBC_DBC_SHIFT									0			// Data Byte Count Shift
#define AHCI_PRDT_DBC_I											(1 << 31)	// Interrupt On Completion

typedef struct
{
	uint8_t dsfis[28];											// DMA Setup FIS
	uint8_t reserved0[4];										// Reserved
	uint8_t psfis[20];											// PIO Setup FIS
	uint8_t reserved1[12];										// Reserved
	uint8_t rfis[20];											// D2H Register FIS
	uint8_t reserved2[4];										// Reserved	
	uint8_t sdbfis[8];											// Set Device Bits FIS
	uint8_t ufis[64];											// Unknown FIS
	uint8_t reserved3[96];										// Reserved
} __attribute__((packed)) ahci_received_fis_t;

typedef struct
{
	uint16_t flags;												// Flags
	uint16_t prdtl;												// Physical Region Descriptor Table Length
	uint32_t prdbc;												// Physical Region Descriptor Byte Count
	uint32_t ctba;												// Command Table Descriptor Base Address
	uint32_t ctbau;												// Command Table Descriptor Base Address Upper
	uint32_t reserved[4];										// Reserved
} __attribute__((packed)) ahci_command_header_t;

typedef struct
{
	uint32_t dba;												// Data Base Address
	uint32_t dbau;												// Data Base Address Upper
	uint32_t reserved;											// Reserved
	uint32_t dbc;												// Data Byte Count + Interrupt On Completion
} __attribute__((packed)) ahci_prdt_t;

typedef struct
{
	uint8_t cfis[64];											// Command FIS
	uint8_t acmd[16];											// ATAPI Command
	uint8_t reserved[48];										// Reserved
	ahci_prdt_t prdt[];											// PRDT Entries
} __attribute__((packed)) ahci_command_table_t;

typedef struct ahci_controller ahci_controller_t;
typedef struct ahci_port ahci_port_t;

typedef struct ahci_controller
{
	void *pci_device;											// PCI Device Struct
	volatile uint32_t *abar;									// ABAR (BAR5 MMIO Base)
	uint32_t capabilities;										// CAP Register
	uint32_t version;											// VS Register
	uint32_t ports_implemented;									// PI Register
	uint8_t num_ports;											// CAP.NP + 1
	uint8_t num_cmd_slots;										// CAP.NCS + 1
	uint32_t cap2;												// CAP2 Register
	ahci_port_t *ports[32];										// Ports
	uint8_t irq;												// IRQ
	uint8_t initialized;										// Flag
} ahci_controller_t;

typedef struct ahci_port
{
	ahci_controller_t *ctrl;									// Parent controller
	uint8_t port_num;											// Port Number
	volatile uint32_t *regs;									// Port Registers
	ahci_command_header_t *cmd_list;							// Command List (1 KB)
	ahci_received_fis_t *fis;									// Received FIS (256 B)
	ahci_command_table_t *cmd_table;							// Command Table
	uint32_t signature;											// PxSIG Value
	uint64_t total_sectors;										// Total Sectors
	uint32_t sector_size;										// Sector Size
	uint8_t device_present;										// Device Present
	uint8_t device_type;										// Device Type
	uint8_t current_slot;										// Current Command Slot
	uint8_t initialized;										// Flag
	void *block_device;											// Block Device
} ahci_port_t;

void registerAHCI(void);

#endif