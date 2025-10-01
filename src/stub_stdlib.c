// Implementación mínima de funciones de la biblioteca estándar para sistemas embebidos
#include <stdint.h>

// Definiciones mínimas necesarias
#define EBADF 9
#define ENFILE 23
#define S_IFCHR 0020000

// Variables globales
int errno = 0;

// Fin del programa
void _exit(int i) {
    __asm__ __volatile__ (" ebreak ");
}

// Terminar proceso (no implementado en este sistema)
void _kill(int pid) {
    __asm__ __volatile__ (" ebreak ");
}

// Obtener ID del proceso
int _getpid(void) {
    return 1;
}

// Cerrar archivo (no implementado)
int _close(int file) {
    errno = EBADF;
    return -1;
}

// Obtener estado del archivo
int _fstat(int file, void *st) {
    // Indicar que es un dispositivo de caracteres
    ((uint32_t*)st)[1] = S_IFCHR;
    return 0;
}

// Verificar si es un terminal
int _isatty(int file) {
    return 1;
}

// Buscar en archivo (no implementado)
int _lseek(int file, int ptr, int dir) {
    return 0;
}

// Abrir archivo (no implementado)
int _open(const char *name, int flags, int mode) {
    errno = ENFILE;
    return -1;
}

// Leer de archivo (no implementado)
int _read(int file, char *ptr, int len) {
    return 0;
}

// Escribir en archivo
int _write(int file, char *ptr, int len) {
    return len;
}

// Ajustar el break del programa
char *_sbrk(int delta) {
    extern char _end[];
    static char *end_of_data = _end;
    char *ptr = end_of_data;
    end_of_data += delta;
    return ptr;
}
