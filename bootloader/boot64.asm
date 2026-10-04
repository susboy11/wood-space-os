; ============================================================================
; File:			boot64.asm
; Description:	Bootloader: load kernel from disk, enter Long Mode, jump to kernel
; Created:		2026-10-03
; Author:		susboy11
; ============================================================================

bits 16
org 0x7C00

KERNEL_LOAD_ADDR 	equ 0x8000	; Where to load kernel
KERNEL_SECTORS		equ 64		; How many sectors to read (32 KB)

start:
	cli
	xor		ax, ax
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		sp, 0x7C00

	; Save boot drive number (BIOS passes it in DL)
	mov		[boot_drive], dl

	mov		si, msg_loading
	call	print_string

	; Read kernel from disk using INT 13h AH=42h (LBA read)
	mov		si, dap
	mov		ah, 0x42
	mov		dl, [boot_drive]
	int		0x13
	jc		disk_error

	mov		si, msg_ok
	call	print_string

	; Check Long Mode support 
	mov		eax, 0x80000000
	cpuid
	cmp		eax, 0x80000001
	jb		no_long_mode

	; Check Long Mode support 
	mov		eax, 0x80000001
	cpuid
	test	edx, (1 << 29)
	jz		no_long_mode

	; Load GDT
	lgdt	[GDT64.Pointer]

	; Far jump to 32-bit code (Protected Mode)
	mov		eax, cr0
	or		eax, 1
	mov		cr0, eax
	jmp		GDT64.Code32:protected_mode

; Print string via BIOS
print_string:
	lodsb
	cmp		al, 0
	je		.done
	mov		ah, 0x0E
	int		0x10
	jmp		print_string
.done:
	ret

; Disk error handler
disk_error:
	mov		si, msg_disk_err
	call	print_string
.hang:
	jmp		$

; Data
msg_loading		db 'Loading kernel...', 13, 10, 0
msg_ok			db 'OK', 13, 10, 0
msg_disk_err	db 'Disk read error!', 13, 10, 0
msg_no_lm		db 'Long Mode not supported!', 0
boot_drive		db 0

; Disk Address Packet (DAP) for INT 13h AH=42h
align 4
dap:
    db 0x10					; Size of DAP (16 bytes)
    db 0					; Reserved
    dw KERNEL_SECTORS		; Number of sectors to read
    dw KERNEL_LOAD_ADDR		; Offset (destination)
    dw 0x0000				; Segment (destination) = 0x0000:0x8000
    dq 1					; LBA (starting sector, 1 = right after boot sector)

; 32-bit Protected Mode
bits 32
protected_mode:
	mov		ax, GDT64.Data
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		fs, ax
	mov		gs, ax

	; Clear page tables area
	mov		edi, 0x1000
	mov		cr3, edi
	xor		eax, eax
	mov		ecx, 4096
	rep		stosd

	; PML4 -> PDPT -> PD -> PT
	mov		edi, 0x1000
	mov		DWORD [edi], 0x2003
	add		edi, 0x1000
	mov		DWORD [edi], 0x3003
	add		edi, 0x1000
	mov		DWORD [edi], 0x4003
	add		edi, 0x1000

	; Fill PT: identity map first 2 MB
	mov		ebx, 0x00000003
	mov		ecx, 512
.map_pt:
	mov		DWORD [edi], ebx
	add		ebx, 0x1000
	add		edi, 8
	loop	.map_pt

	; Enable PAE
	mov		eax, cr4
	or		eax, (1 << 5)
	mov		cr4, eax

	; Load CR3
	mov		eax, 0x1000
	mov		cr3, eax

	; Set LME in EFER
	mov		ecx, 0xC0000080
	rdmsr
	or		eax, (1 << 8)
	wrmsr

	; Enable Paging
	mov		eax, cr0
	or		eax, (1 << 31)
	mov		cr0, eax

	; Far jump to 64-bit code (Long Mode)
	jmp		GDT64.Code:long_mode_entry

; GDT
align 8
GDT64:
    dq		0
.Code32 equ $ - GDT64
    dq		0x00CF9A000000FFFF
.Data equ $ - GDT64
    dq		0x00CF92000000FFFF
.Code equ $ - GDT64
    dq		(1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
.Pointer:
    dw		$ - GDT64 - 1
    dq		GDT64

; 64-bit Long Mode
bits 64
long_mode_entry:
	mov		ax, GDT64.Data
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ss, ax

	; Set up stack
	mov		rsp, 0x90000

	; Jump to kernel entry point
	mov		rax, KERNEL_LOAD_ADDR
	jmp		rax

; No Long Mode handler
bits 16
no_long_mode:
	mov		si, msg_no_lm
	call	print_string
.hang:
	jmp		$

; Boot sector padding
times 510 - ($ - $$) db 0

; Boot sector signature
dw 0xAA55