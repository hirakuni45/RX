/*====================================================*/
/*  R5F563T6EDFM gcc リンカースクリプト               */
/*  シングルチップモード                              */
/*  内臓RAM 0x00000000～0x000001FFF (8KB)             */
/*  内臓ROM 0xFFFF0000～0xFFFFFFFFF (64KB)            */
/*====================================================*/

MEMORY {
    RAM(rwx) : org = 0x00000000, len = 0x00001000
    ROM(rx)  : org = 0x00008000, len = 0x00008000
}

SECTIONS {

	_usp_init = 0x00001f00;
	_isp_init = 0x00002000;

    .fvectors 0x0000FFD0 : {
		vect.o(.fvectors)
    }

  .text : {
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
    *(.rodata C C_2 C_1 .rodata.* .gnu.linkonce.r.*)
    *(.rodata1)
    *(.eh_frame_hdr)
    KEEP (*(.eh_frame))
    KEEP (*(.gcc_except_table)) *(.gcc_except_table.*)
    . = ALIGN(4);
    PROVIDE(__romdatastart = .);
  } > ROM

  .cdlist : {
    . = ALIGN(4);
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
  } > ROM

  PROVIDE( __datainternal = ABSOLUTE(LOADADDR(.data)));

  .data : {
    PROVIDE (__datastart = .); /* IF_ROROM */

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

}
