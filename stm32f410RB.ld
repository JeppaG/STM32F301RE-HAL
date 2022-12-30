/* Copyright 2020 JG Mechatronics AB */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

MEMORY
{
	flash	(rx):	ORIGIN = 0x08000000, LENGTH = 128K
	ram		(rwx):	ORIGIN = 0x20000000, LENGTH = 32K
}

__rom_start__	= ORIGIN(flash);
__rom_size__	= LENGTH(flash);
__ram_start__	= ORIGIN(ram);
__ram_size__	= LENGTH(ram);
__ram_end__     = __ram_start__ + __ram_size__;
__stack_end__   = __ram_end__;	/* Top of ram */
__stack_size__  = 16K;
__stack_start__ = __stack_end__ - __stack_size__;
__heap_start__	= __bss_end__; /* Between bss and stack */
__heap_end__	= __stack_start__;
end				= __heap_start__;
_HEAP_START = __heap_start__;
_HEAP_END = __heap_end__;

SECTIONS
{
	.text :
	{
	    __vectors__ = .;
	    KEEP(*(.vectors))   /* Vector table */
	    __start__ = .;
		KEEP(*(.startup))	/* Startup code */
		*(.text*)           /* Program code */
		KEEP(*(.rodata))	/* ReadOnly data */
		*(.glue_7)
		*(.glue7_t)
		*(.eh_frame)
		. = ALIGN(4);
		__ctors_start__ = .;
		KEEP(*(.init_array)) /* C++ constructors */
		KEEP(*(.ctors))      /* C++ constructors */
		__ctors_end__ = .;
		. = ALIGN(16);
		__text_end__ = .;
	} >flash
	
	.data : ALIGN(16)
	{
		__data_start__ = .;    /* Used in crt0.S */
		*(.data*) 	         /* Initialized data */
		__data_end__ = .;    /* Used in crt0.S */
	} >ram AT >flash
	
	.bss (NOLOAD) : ALIGN(16)
	{
	    __bss_start__ = .;    /* Used in crt0.S */
		*(.bss*)		    /* Un-initialized data */
		*(COMMON)           /* Common data */
		__bss_end__ = .;    /* Used in crt0.S */
	} >ram

    /* C++ exception unwinding stuff - needed by some toolchains */
    .ARM.extab :
    {
         *(.ARM.extab* .gnu.linkonce.armextab.*)
    } >flash
        
    .ARM.exidx : 
    { 
         __exidx_start = .;
         *(.ARM.exidx* .gnu.linkonce.armexidx.*)
         __exidx_end = .;
    } >flash
}

/* Firmware entry point */

ENTRY(__vectors__)