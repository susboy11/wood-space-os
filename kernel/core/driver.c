/*
 * ============================================================================
 * File:		driver.c
 * Description: Driver abstraction layer implementation
 * Created:		2026-10-04
 * Author:		susboy11
 * ============================================================================
*/

#include "include/driver.h"
#include "include/device.h"

#include "lib/string.h"

#define MAX_DRIVERS		16

static driver_t *drivers[MAX_DRIVERS];
static int driver_count = 0;

void registerDriver(driver_t *driver)
{
	if (driver_count >= MAX_DRIVERS)
	{
		return;
	}
	
	drivers[driver_count] = driver;
	driver_count++;
}

driver_t* getDriverByIndex(int index)
{
	if ((index < 0) || (index >= driver_count))
	{
		return NULL;
	}
	
	return drivers[index];
}

driver_t* getDriverByName(const char *name)
{
	for (int i = 0; i < driver_count; i++)
	{
		if (stringCompare(drivers[i]->name, name) == 0)
		{
			return drivers[i];
		}
	}
	
	return NULL;
}

int getDriverCount(void)
{
	return driver_count;
}

void matchAllDrivers(void)
{
	for (int i = 0; i < getDeviceCount(); i++)
	{
		device_t *device = getDeviceByIndex(i);
		
		if (device->driver != NULL)
		{
			continue;
		}
		
		for (int j = 0; j < driver_count; j++)
		{
			driver_t *driver = drivers[j];
			
			if ((driver->match == NULL))
			{
				continue;
			}
			
			if (driver->match(device))
			{
				device->driver = driver;
				
				if (driver->probe != NULL)
				{
					driver->probe(device);
				}
				
				break;
			}
		}
	}
}
