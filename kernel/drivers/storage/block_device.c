/*
 * ============================================================================
 * File:		block_device.c
 * Description: Block device controller implementation
 * Created:		2026-09-29
 * Author:		susboy11
 * ============================================================================
*/

#include <stddef.h>

#include "drivers/storage/block_device.h"

#define MAX_BLOCK_DEVICES		16

static block_device_t *block_devices[MAX_BLOCK_DEVICES];
static int device_count = 0;

int blockDeviceRegister(block_device_t *device)
{
	if (device_count >= MAX_BLOCK_DEVICES)
	{
		return -1;
	}
	
	if ((device == NULL) || (device->read == NULL))
	{
		return -1;
	}
	
	block_devices[device_count] = device;
	
	return device_count++;
}

block_device_t* getBlockDevice(int device_index)
{
	if ((device_index < 0) || (device_index >= device_count))
	{
		return NULL;
	}
	
	return block_devices[device_index];
}

int getBlockDeviceCount(void)
{
	return device_count;
}

int readBlockDevice(int device_index, uint32_t lba, uint32_t count, void *buffer)
{
	block_device_t *device = getBlockDevice(device_index);
	
	if ((device == NULL) || (device->read == NULL))
	{
		return -1;
	}
	
	return device->read(device, lba, count, buffer);
}

int writeBlockDevice(int device_index, uint32_t lba, uint32_t count, const void *buffer)
{
	block_device_t *device = getBlockDevice(device_index);
	
	if ((device == NULL) || (device->write == NULL))
	{
		return -1;
	}
	
	return device->write(device, lba, count, buffer);
}