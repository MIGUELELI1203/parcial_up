#include <stdint.h>
#include "soc_emu_gpio.h"
#include "soc_uart.h"

char wr_buffer[256]="";

void delay(volatile uint32_t count) {
    while (count--) {
        __asm__ volatile("nop");
    }
}

// Función simple para convertir uint32_t a string hexadecimal
void uint32_to_hex_string(uint32_t value, char* buffer) {
    const char hex_chars[] = "0123456789ABCDEF";
    int i;
    for (i = 0; i < 8; i++) {
        buffer[7-i] = hex_chars[(value >> (i*4)) & 0xF];
    }
    buffer[8] = '\0';
}

void main(void) {
    volatile uint32_t sw_value = 1;

    emu_gpio_init();
    uart_init(115200); // Initialize UART

    emu_gpio_write_port(sw_value);
    
    // Convertir el valor a string y mostrarlo
    uint32_to_hex_string(sw_value, wr_buffer);
    uart_puts("GPIO State: 0x");
    uart_puts(wr_buffer);
    uart_puts("\n\r");
    
    uart_puts("Press u key to increment the counter\n");
    uart_puts("Press d key to decrement the counter\n");
    uart_puts("Press cntrl+a c to exit qemu\n");
    
    while (1) {
        while (uart_tstc())  // Check if data is available
        {
            char c = uart_getc();  // Read character
            if (c == 'u') {
                sw_value++;  // Increment on 'u'
            } else if (c == 'd') {
                if (sw_value > 0) {  // Solo decrementar si es mayor que 0
                    sw_value--;  // Decrement on 'd'
                }
            }
            if (sw_value > 0xFF)  // Limit to 8 bits
            {
                sw_value = 0xFF;
            }
            emu_gpio_write_port(sw_value);  // Write to LEDs
            
            // Convertir el valor a string y mostrarlo
            uint32_to_hex_string((uint8_t)sw_value, wr_buffer);
            uart_puts("GPIO State: 0x");
            uart_puts(wr_buffer);
            uart_puts("\n\r");
        }
    }
}
