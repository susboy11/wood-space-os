/*
 * ============================================================================
 * File:		console_print.c
 * Description: VGA text console output implementation
 * Created:		2026-10-09
 * Author:		susboy11
 * ============================================================================
*/

#include "lib/console_print.h"

static int cursor_x = 0;
static int cursor_y = 0;

void consoleClear(void)
{
	volatile unsigned short *video = (volatile unsigned short *)VGA_BUFFER;
	
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		video[i] = (unsigned short)((COLOR_BLACK << 8) | ' ');
	}
	
	cursor_x = 0;
	cursor_y = 0;
}

void consolePutChar(char c, unsigned char color)
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

void consolePrint(const char *string, unsigned char color)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		consolePutChar(string[i], color);
	}
}

void consolePrintDec(uint32_t value, unsigned char color)
{
	if (value == 0)
	{
		consolePutChar('0', color);
		
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
		consolePutChar(buf[--i], color);
	}
}

void consolePrintHex(uint32_t value, int digits, unsigned char color)
{
	char hex[] = "0123456789ABCDEF";
	
	for (int i = digits - 1; i >= 0; i--)
	{
		consolePutChar(hex[(value >> (i * 4)) & 0xF], color);
	}
}