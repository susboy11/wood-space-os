/*
 * ============================================================================
 * File:		block_device.h
 * Description: 
 * Created:		2026-09-29
 * Author:		susboy11
 * ============================================================================
*/

#ifndef BLOCK_DEVICE_H
#define BLOCK_DEVICE_H

#include "include/default_types.h"

typedef struct block_device
{
	char name[16];
	uint32_t sector_size;
	uint32_t total_sectors;
	int (*read)(struct block_device *device, uint32_t lba, uint32_t count, void *buffer);
	int (*write)(struct block_device *device, uint32_t lba, uint32_t count, const void *buffer);
	void *private_data;
} block_device_t;

int blockDeviceRegister(block_device_t *device);
block_device_t* getBlockDevice(int device_index);
int getBlockDeviceCount(void);

int readBlockDevice(int device_index, uint32_t lba, uint32_t count, void *buffer);
int writeBlockDevice(int device_index, uint32_t lba, uint32_t count, const void *buffer);

#endif