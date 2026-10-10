/*
 * ============================================================================
 * File:		bus.c
 * Description: Bus abstaction layer implementation
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#include "include/bus.h"

#include "lib/string.h"

#define MAX_BUSES		16

extern bus_t *__start_section_buses[];
extern bus_t *__stop_section_buses[];

static bus_t *buses[MAX_BUSES];
static int bus_count = 0;

void registerBus(bus_t *bus)
{
	if (bus_count >= MAX_BUSES)
	{
		return;
	}
	
	buses[bus_count] = bus;
	bus_count++;
}

void registerAllBuses(void)
{
	for (bus_t **ptr = __start_section_buses; ptr < __stop_section_buses; ptr++)
	{
		registerBus(*ptr);
	}
}

bus_t* getBusByIndex(int index)
{
	if ((index < 0) || (index >= bus_count))
	{
		return NULL;
	}
	
	return buses[index];
}

bus_t* getBusByName(const char *name)
{
	for (int i = 0; i < bus_count; i++)
	{
		if (stringCompare(buses[i]->name, name) == 0)
		{
			return buses[i];
		}
	}
	
	return NULL;
}

int getBusCount(void)
{
	return bus_count;
}