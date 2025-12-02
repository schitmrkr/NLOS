#ifndef IO_H
#define IO_H

#include <stdint.h>

/* Read a byte from the given port */
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

/* Write a byte to the given port */
static inline void outb(uint16_t port, uint8_t val) {
  __asm__ __volatile__("outb %0, %1" : : "a"(val), "dN"(port));
}

#endif