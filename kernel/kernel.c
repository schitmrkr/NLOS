#include <stdint.h>

extern void kmain(void); 

void kmain() {
    volatile uint16_t* vga = (uint16_t*)0xB8000; // VGA memory
    const char* msg = "Welcome to NLOS!";

    for (int i = 0; msg[i] != '\0'; i++) {
        vga[i] = (0x0F << 8) | msg[i];   // white on black
    }

    while(1);
}