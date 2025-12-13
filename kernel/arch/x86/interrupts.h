#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "idt.h"
#include <stdint.h>

void pic_remap();

extern void keyboard_isr(void);
extern void isr_common_stub(void);

#endif // INTERRUPTS_H