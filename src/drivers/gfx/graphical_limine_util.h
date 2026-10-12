#ifndef GRAPHICAL_LIMINE_UTIL
#define GRAPHICAL_LIMINE_UTIL

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"

extern volatile uint64_t limine_base_revision[];
extern volatile struct limine_framebuffer_request framebuffer_request;

void hcf(void);
// Build a pixel from 8-bit red, green and blue values following the channel
// layout of the framebuffer.
uint32_t fb_pixel(struct limine_framebuffer *fb, uint8_t red, uint8_t green, uint8_t blue);

#endif //GRAPHICAL_LIMINE_UTIL
