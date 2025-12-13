#ifndef IO_H
#define IO_H

#include <stdint.h>

// Read a byte from the given port
// Equivalent to following assembly code:
//
// mov dx, [port]  ; Load port address into dx register
// in al, dx       ; Read byte from port into al register
// mov [ret], al   ; Store byte in ret
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

// Write a byte to the given port
// Equivalent to following assembly code:
//
// mov dx, [port]  ; Load port address into dx register
// mov al, [val]   ; Load byte into al register
// out dx, al      ; Write byte to port
static inline void outb(uint16_t port, uint8_t val) {
  __asm__ __volatile__("outb %0, %1" : : "a"(val), "dN"(port));
}

// New interrupt control
// Equivalent to following assembly code:
// sti
// sti is a no-op if interrupts are already enabled
static inline void enable_interrupts() { __asm__ __volatile__("sti"); }

// Equivalent to following assembly code:
// cli
// cli is a no-op if interrupts are already disabled
static inline void disable_interrupts() { __asm__ __volatile__("cli"); }

#endif