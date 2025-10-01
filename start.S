# Start.S - Punto de entrada para RISC-V
.section .text.entry
.globl _start
_start:
    # Configurar el puntero de pila (sp) al final de la RAM
    la sp, _stack_top
    
    # Saltar a la función main
    call main
    
    # Bucle infinito si main retorna
_loop:
    j _loop

# Definir el símbolo para el tope de la pila
.section .bss
.space 4096   # Reservar 4KB para la pila
_stack_top:
