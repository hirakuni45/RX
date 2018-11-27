/*!	@file
	@brief	RX66T R5F566TK リンカー・スクリプト @n
			Code: 1M, RAM: 128K, DataFlash: 32K
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/

/* Default linker script, for normal executables */
OUTPUT_ARCH(rx)
ENTRY(_start)

/* Do we need any of these for elf?
   __DYNAMIC = 0;    */

/* This memory layout corresponds to the smallest predicted RX66TK chip.  */
MEMORY {
	RAM (w)    : ORIGIN = 0x00000000, LENGTH = 0x0001FC00 /* 128K - stack_size (1024) */
	USTACK (w) : ORIGIN = 0x0001FF80, LENGTH = 4 /* ustack 896 bytes */
	ISTACK (w) : ORIGIN = 0x00020000, LENGTH = 4 /* istack 128 bytes  */
	ROM (w)    : ORIGIN = 0xFFF00000, LENGTH = 0x000FFFD0 /* 1024K - hw_vectors(48) */
}

SECTIONS
{
  .text           :
  {
    PROVIDE (_start = .);
    *(.text P .stub .text.* .gnu.linkonce.t.*)
    KEEP (*(.text.*personality*))
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
    *(.interp .hash .dynsym .dynstr .gnu.version*)
    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);
    . = ALIGN(4);
    KEEP (*(.init))
    KEEP (*(.fini))
  } > ROM

  .rodata : {
    . = ALIGN(4);
    *(.plt)
    *(.rodata C C_2 C_1 W W_2 W_1 .rodata.* .gnu.linkonce.r.*)
    *(.rodata1)
    *(.eh_frame_hdr)
    KEEP (*(.eh_frame))
    KEEP (*(.gcc_except_table)) *(.gcc_except_table.*)
    . = ALIGN(4);
    PROVIDE(__romdatastart = .);
  } > ROM

  .data : {
    . = ALIGN(4);
    PROVIDE (__datastart = .); /* IF_ROROM */
    PROVIDE (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE (__preinit_array_end = .);
    PROVIDE (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE (__init_array_end = .);
    PROVIDE (__fini_array_start = .);
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE (__fini_array_end = .);
    LONG(0); /* Sentinel.  */

    /* gcc uses crtbegin.o to find the start of the constructors, so
       we make sure it is first.  Because this is a wildcard, it
       doesn't matter if the user does not actually link against
       crtbegin.o; the linker won't look for a file to match a
       wildcard.  The wildcard also means that it doesn't matter which
       directory crtbegin.o is in.  */
    KEEP (*crtbegin*.o(.ctors))

    /* We don't want to include the .ctor section from from the
       crtend.o file until after the sorted ctors.  The .ctor section
       from the crtend file contains the end of ctors marker and it
       must be last */
    KEEP (*(EXCLUDE_FILE (*crtend*.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))

    KEEP (*crtbegin*.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend*.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))

    KEEP (*(.jcr))
    *(.data.rel.ro.local) *(.data.rel.ro*)
    *(.dynamic)

    *(.data D .data.* .gnu.linkonce.d.*)
    KEEP (*(.gnu.linkonce.d.*personality*))
    SORT(CONSTRUCTORS)
    *(.data1)
    *(.got.plt) *(.got)

    /* We want the small data sections together, so single-instruction offsets
       can access them all, and initialized data all before uninitialized, so
       we can shorten the on-disk segment size.  */
    . = ALIGN(4);
    *(.sdata .sdata.* .gnu.linkonce.s.* D_2 D_1)

    . = ALIGN(4);
    _edata = .;
    PROVIDE (edata = .);
    PROVIDE (__dataend = .);
  } > RAM AT> ROM

  /* Note that __romdatacopysize may be ZERO for the simulator, which
     knows how to intialize RAM directly.  It should ONLY be used for
     copying data from ROM to RAM; if you need to know the size of the
     data section, subtract the end symbol from the start symbol.  */
  /* Note that crt0 assumes this is a multiple of four; all the
     start/stop symbols are also assumed long-aligned.  */
  PROVIDE (__romdatacopysize = SIZEOF(.data));

  .bss : {
    . = ALIGN(4);
    PROVIDE (__bssstart = .);
    *(.dynbss)
    *(.sbss .sbss.*)
    *(.bss B B_2 B_1 .bss.* .gnu.linkonce.b.*)
    . = ALIGN(4);
    *(COMMON)
    . = ALIGN(4);
    PROVIDE (__bssend = .);
    _end = .;
    PROVIDE (end = .);
  } > RAM
  PROVIDE (__bsssize = SIZEOF(.bss) / 4);

  .istack (ORIGIN (ISTACK)) :
  {
    PROVIDE (__istack = .);
    *(.istack)
  }

  .ustack (ORIGIN (USTACK)) :
  {
    PROVIDE (__ustack = .);
    *(.ustack)
  }

  /* Providing one of these symbols in your code is sufficient to have
     it linked in to the fixed vector table.  */

  PROVIDE (__rx_priviledged_exception_handler = 0x00000000);
  PROVIDE (__rx_access_exception_handler = 0x00000000);
  PROVIDE (__rx_undefined_exception_handler = 0x00000000);
  PROVIDE (__rx_floating_exception_handler = 0x00000000);
  PROVIDE (__rx_nonmaskable_exception_handler = 0x00000000);

  .vectors (0xFFFFFFD0) :
  {
    PROVIDE (__vectors = .);
    LONG (__rx_priviledged_exception_handler);
    LONG (__rx_access_exception_handler);
    LONG (0);
    LONG (__rx_undefined_exception_handler);
    LONG (0);
    LONG (__rx_floating_exception_handler);
    LONG (0);
    LONG (0);
    LONG (0);
    LONG (0);
    LONG (__rx_nonmaskable_exception_handler);
    LONG (_start);
  }

  /* The rest are all not normally part of the runtime image.  */

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /DISCARD/ : { *(.note.GNU-stack) }
}
