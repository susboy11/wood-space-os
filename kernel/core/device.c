/*
 * ============================================================================
 * File:		device.c
 * Description: Device abstraction layer implementation
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#include "include/device.h"

#include "lib/string.h"

#define MAX_DEVICES		64

static device_t devices[MAX_DEVICES];
static int device_count = 0;
static int device_alloc_count = 0;

static void clearDevice(device_t *device)
{
	device->name[0] = '\0';
	device->bus = NULL;
	device->bus_data = NULL;
	device->driver = NULL;
	device->driver_data = NULL;
	device->state = 0;
	device->flags = 0;
	device->irq = 0;
	device->mmio_base = NULL;
	device->mmio_size = 0;
	device->io_base = 0;
	device->io_size = 0;
	device->parent = NULL;
	
	for (int i = 0; i < DEVICE_MAX_CHILDREN; i++)
	{
		device->children[i] = NULL;
	}
	
	device->children_count = 0;
}

device_t* allocDevice(void)
{
	if (device_alloc_count >= MAX_DEVICES)
	{
		return NULL;
	}
	
	device_t *device = &devices[device_alloc_count];
	
	device_alloc_count++;
	
	clearDevice(device);
	
	return device;
}

void registerDevice(device_t *device)
{
	if (device == NULL)
	{
		return;
	}
	
	if ((device < &devices[0]) || (device >= &devices[MAX_DEVICES]))
	{
		return;
	}
	
	if (device_count < device_alloc_count)
	{
		device_count++;
	}
}

device_t* getDeviceByIndex(int index)
{
	if ((index < 0) || (index >= device_count))
	{
		return NULL;
	}
	
	return &devices[index];
}

device_t* getDeviceByName(const char *name)
{
	for (int i = 0; i < device_count; i++)
	{
		if (stringCompare(devices[i].name, name) == 0)
		{
			return &devices[i];
		}
	}
	
	return NULL;
}

int getDeviceCount(void)
{
	return device_count;
}