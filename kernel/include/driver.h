/*
 * ============================================================================
 * File:		driver.h
 * Description: Driver abstraction layer
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#ifndef DRIVER_H
#define DRIVER_H

#include <stdint.h>

#define DRIVER_MAX_NAME_SIZE		64

typedef struct device device_t;

typedef struct driver
{
	char name[DRIVER_MAX_NAME_SIZE];
	int (*match)(device_t *device);
	int (*probe)(device_t *device);
	int (*remove)(device_t *device);
} driver_t;

void registerDriver(driver_t *driver);

driver_t* getDriverByIndex(int index);
driver_t* getDriverByName(const char *name);
int getDriverCount(void);

void matchAllDrivers(void);

#endif