#ifndef DRIVERS_PORT_H
#define DRIVERS_PORT_H

#include <stdint.h>

uint8_t inb(uint16_t port);
uint8_t outb(uint16_t port, uint8_t value);
void io_wait();

#define outportb outb
#define inportb  inb

#endif // DRIVERS_PORT_H
