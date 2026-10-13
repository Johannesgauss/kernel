#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

extern void *irq_routines[16];
void irqr_add(int irqr, void (*handler)(void));

#endif // ARCH_IRQ_H
