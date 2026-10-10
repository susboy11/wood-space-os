/* 
 * =============================================================================
 * linker.ld - Kernel linked script
 * =============================================================================
 */

ENTRY(_start)

SECTIONS
{
    /* Kernel is loaded at 0x8000 */
    . = 0x8000;

    /* Код */
    .text :
	{
        *(.text)
        *(.text.*)
    }

    /* Only read (consts, strings) */
    .rodata :
	{
        *(.rodata)
        *(.rodata.*)
    }

    /* Init data */
    .data : {
        *(.data)
        *(.data.*)
    }

	/* buses structures*/
	.buses : ALIGN(8)
	{
		__start_section_buses = .;
		KEEP(*(.buses))
		__stop_section_buses = .;
	}

    /* Not init data */
    .bss :
	{
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    /* Other */
    /DISCARD/ :
	{
        *(.comment)
        *(.note.*)
        *(.eh_frame*)
    }
}