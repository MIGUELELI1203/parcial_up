OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY {
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS {
  . = ORIGIN(RAM);
  
  .text : {
    *(.text.entry)
    *(.text .text.*)
  } > RAM
  
  .rodata : {
    *(.rodata .rodata.*)
  } > RAM
  
  .data : {
    *(.data .data.*)
  } > RAM
  
  .bss : {
    *(.bss .bss.*)
    *(COMMON)
  } > RAM
  
  /* Definir el símbolo _end al final de todas las secciones */
  _end = .;
  _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
