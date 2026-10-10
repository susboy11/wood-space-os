/*
 * ============================================================================
 * File:		string.c
 * Description: String utilities implementation
 * Created:		2026-10-09
 * Author:		susboy11
 * ============================================================================
*/

#include "lib/string.h"

size_t stringLength(const char *str)
{
	size_t len = 0;
	
	while (str[len] != '\0')
	{
		len++;
	}
	
	return len;
}

int stringCompare(const char *str_1, const char *str_2)
{
	size_t i = 0;
	
	while (((str_1[i] != '\0') && (str_2[i] != '\0')) && (str_1[i] == str_2[i]))
	{
		i++;
	}
	
	return (unsigned char)str_1[i] - (unsigned char)str_2[i];
}

int stringNCompare(const char *str_1, const char *str_2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (((str_1[i] == '\0') || (str_2[i] == '\0')) || (str_1[i] != str_2[i]))
		{
			return (unsigned char)str_1[i] - (unsigned char)str_2[i];
		}
	}
	
	return 0;
}

void stringCopy(char *dest, const char *src)
{
	size_t i = 0;
	
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	
	dest[i] = '\0';
}

void stringNCopy(char *dest, const char *src, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (src[i] != '\0')
		{
			dest[i] = src[i];
		}
		else
		{
			dest[i] = '\0';
		}
	}
}

void stringWriteDec(char *dest, int *pos, uint32_t value)
{
	if (value == 0)
	{
		dest[(*pos)++] = '0';
		
		return;
	}
	
	char tmp[16];
	int n = 0;
	
	while (value > 0)
	{
		tmp[n++] = '0' + (value % 10);
		value /= 10;
	}
	
	while (n > 0)
	{
		dest[(*pos)++] = tmp[--n];
	}
}