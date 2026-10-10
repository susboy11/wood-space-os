/*
 * ============================================================================
 * File:		bus.h
 * Description: Bus abstaction layer
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#ifndef BUS_H
#define BUS_H

#include <stdint.h>

#define BUS_MAX_NAME_SIZE		64

#define BUS_REGISTER(bus) \
		static bus_t *__bus_##bus \
		__attribute__((used, section(".buses"))) = &bus

typedef struct bus bus_t;

typedef struct bus
{
	char name[BUS_MAX_NAME_SIZE];
	int (*init)(bus_t *bus);
	int (*scan)(bus_t *bus);
} bus_t;

void registerBus(bus_t *bus);
void registerAllBuses(void);

bus_t* getBusByIndex(int index);
bus_t* getBusByName(const char *name);
int getBusCount(void);

#endif