/*
 * ============================================================================
 * File:		console_print.h
 * Description: VGA text console output
 * Created:		2026-10-09
 * Author:		susboy11
 * ============================================================================
*/

#ifndef CONSOLE_PRINT_H
#define CONSOLE_PRINT_H

#include <stdint.h>

#define COLOR_BLACK			0x0
#define COLOR_WHITE			0xF
#define COLOR_LIGHT_GREEN	0xA
#define COLOR_YELLOW		0xE
#define COLOR_LIGHT_RED		0xC

#define VGA_BUFFER			0xB8000
#define VGA_WIDTH			80
#define VGA_HEIGHT			25

void consoleClear(void);
void consolePutChar(char c, unsigned char color);
void consolePrint(const char *string, unsigned char color);

void consolePrintDec(uint32_t value, unsigned char color);
void consolePrintHex(uint32_t value, int digits, unsigned char color);

#endif