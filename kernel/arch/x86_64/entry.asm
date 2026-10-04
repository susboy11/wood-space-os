; ============================================================================
; File:			entry.asm
; Description:	Entry point for 64-bit kernel
; Created:		2026-10-03
; Author:		susboy11
; ============================================================================

bits 64

section .text
global _start

extern KernelMain

_start:
	; Setup segment registers (data selector = 0x10)
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ss, ax

	; Setup stack (grows down from 0x90000)
	mov		rsp, 0x90000

	; Call C kernel function
	call	KernelMain

; If KernelMain returns (should not)
.hang:
	cli
	hlt
	jmp		.hang