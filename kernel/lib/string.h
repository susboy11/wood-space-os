/*
 * ============================================================================
 * File:		string.h
 * Description: String utilities
 * Created:		2026-10-09
 * Author:		susboy11
 * ============================================================================
*/

#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

size_t stringLength(const char *str);
int stringCompare(const char *str_1, const char *str_2);
int stringNCompare(const char *str_1, const char *str_2, size_t n);
void stringCopy(char *dest, const char *src);
void stringNCopy(char *dest, const char *src, size_t n);
void stringWriteDec(char *dest, int *pos, uint32_t value);

#endif