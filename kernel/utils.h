#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void itoa(int n, char *buf);
int strlen(const char *s);

void *memset(void *ptr, uint8_t value, int num);
void *memcpy(void *dest, const void *src, int num);

#endif