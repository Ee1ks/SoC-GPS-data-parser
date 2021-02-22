#ifndef _DISPLAY_DRIVER_H_
#define _DISPLAY_DRIVER_H_

#include "utils.h"

void init_display(uint8_t *ram_addr);
void clear_display(uint8_t *ram_addr);
void write_to_display(uint8_t *ram_addr);

#endif