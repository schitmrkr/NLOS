#include "utils.h"

void itoa(int n, char *buf) {
  int i = 0;
  int is_negative = 0;

  if (n == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return;
  }

  if (n < 0) {
    is_negative = 1;
    n = -n;
  }

  char temp[12];
  int j = 0;

  while (n > 0) {
    // '0' has an ASCII value of 48
    temp[j++] = '0' + n % 10;
    n /= 10;
  }

  if (is_negative) {
    buf[i++] = '-';
  }

  for (int k = j - 1; k >= 0; k--) {
    buf[i++] = temp[k];
  }

  buf[i] = '\0';
}

/* Integer to hex string */
void itox(unsigned int n, char *buf) {
  int i = 0;
  if (n == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return;
  }

  char temp[9]; // Max 8 hex digits for 32 bits
  int j = 0;
  while (n > 0) {
    unsigned int digit =
        n & 0xF; // This operation is equivalent to n AND 0000 1111
    if (digit < 10)
      temp[j++] = '0' + digit;
    else
      temp[j++] = 'A' + (digit - 10);
    // Shift the n to right by 4 bits
    // n = n / 16   (integer division)
    // 0011 1010 1111   (before)
    // 0000 0011 1010   (after shift)
    n >>= 4;
  }

  while (j > 0) {
    buf[i++] = temp[--j];
  }
  buf[i] = '\0';
}

int strlen(const char *s) {
  int len = 0;
  while (s[len])
    len++;
  return len;
}

// Memory set
// *ptr - Pointer to the memory block you want to fill
// value - Value to be set
// num - Number of bytes to be set
void *memset(void *ptr, uint8_t value, int num) {
  uint8_t *p = (uint8_t *)ptr;
  for (int i = 0; i < num; i++) {
    p[i] = value;
  }
  return ptr;
}

// Memory copy
// *dest - Pointer to the destination memory block
// *src - Pointer to the source memory block
// num - Number of bytes to copy
void *memcpy(void *dest, const void *src, int num) {
  uint8_t *p = (uint8_t *)dest;
  const uint8_t *q = (const uint8_t *)src;
  for (int i = 0; i < num; i++) {
    p[i] = q[i];
  }
  return dest;
}
