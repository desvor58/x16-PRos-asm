OUTPUT_FORMAT("elf32-i386")
ENTRY(_cstart)
SECTIONS
{
    . = 0x0;
    
    .text : {
        *(.text.cstart)
        *(.text)
        *(.text.*)
    }
    .rodata : {
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    .outbuf_section : {
        *(.outbuf_section)
    }

    .intext_section : {
        *(.intext_section)
    }

    /DISCARD/ : {
        *(.comment) *(.note*)
    }
}