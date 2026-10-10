/*
 * ============================================================================
 * File:		device.h
 * Description: Device abstraction layer
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

#define DEVICE_MAX_NAME_SIZE		64
#define DEVICE_MAX_CHILDREN			4

typedef struct bus bus_t;
typedef struct device device_t;
typedef struct driver driver_t;

typedef struct device
{
	char name[DEVICE_MAX_NAME_SIZE];
	bus_t *bus;
	void *bus_data;
	driver_t *driver;
	void *driver_data;
	int state;
	uint32_t flags;
	uint8_t irq;
	volatile void *mmio_base;
	uint32_t mmio_size;
	uint32_t io_base;
	uint32_t io_size;
	device_t *parent;
	device_t *children[DEVICE_MAX_CHILDREN];
	int children_count;
} device_t;

device_t* allocDevice(void);
void registerDevice(device_t *device);

device_t* getDeviceByIndex(int index);
device_t* getDeviceByName(const char *name);
int getDeviceCount(void);

#endif