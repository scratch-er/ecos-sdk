#include "generated/autoconf.h"

ENTRY(_start)

SECTIONS {
  _pmem_start = CONFIG_LINK_ADDRESS;
  . = _pmem_start;
  .text : {
    *(entry)
    *(.text*)
  }
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  .data : {
    *(.data)
  }
  edata = .;
  _data = .;
  .bss : {
	_bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  }
  end = .;
  _end = .;
  
  /* Stack at the end of program, 1MB size */
  . = ALIGN(16);
  _stack_top = .;
  . = . + 0x100000;
  _stack_pointer = .;
  
  _heap_start = ALIGN(0x1000);
}
