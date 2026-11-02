#ifndef PORT_BLIT_H
#define PORT_BLIT_H
#include <3ds.h>
#include <stdbool.h>
#include <stdint.h>
bool port_blit_rgb565_top(const uint16_t *pixels, unsigned width, unsigned height);
#endif
