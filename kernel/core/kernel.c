/*
 * ============================================================================
 * File:        kernel.c
 * Description: Kernel entry point
 * Created:     2026-10-03
 * Author:      susboy11
 * ============================================================================
 */

#include <stddef.h>

#include "include/bus.h"
#include "include/device.h"
#include "include/driver.h"

#include "lib/console_print.h"

void KernelMain(void)
{
	consoleClear();

	consolePrint("Hello from C kernel!\n", COLOR_WHITE);
	consolePrint("Long Mode is working.\n", COLOR_LIGHT_GREEN);
	consolePrint("This is my first OS.\n\n", COLOR_WHITE);

	consolePrint("Registering buses...\n", COLOR_WHITE);
	registerAllBuses();
	consolePrint("  Buses: ", COLOR_WHITE);
	consolePrintDec(getBusCount(), COLOR_LIGHT_GREEN);
	consolePrint("\n", COLOR_WHITE);

	consolePrint("Initializing buses...\n", COLOR_WHITE);
	
	for (int i = 0; i < getBusCount(); i++)
	{
		bus_t *bus = getBusByIndex(i);
		
		if (bus->init != NULL)
		{
			bus->init(bus);
		}
	}

	consolePrint("Scanning buses...\n", COLOR_WHITE);
	
	for (int i = 0; i < getBusCount(); i++)
	{
		bus_t *bus = getBusByIndex(i);
		
		if (bus->scan != NULL)
		{
			bus->scan(bus);
		}
	}

	consolePrint("Devices: ", COLOR_WHITE);
	consolePrintDec(getDeviceCount(), COLOR_LIGHT_GREEN);
	consolePrint("\n", COLOR_WHITE);

	while (1)
	{
		
	}
}