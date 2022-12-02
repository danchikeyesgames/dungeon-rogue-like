#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stddef.h>
#include <stdint.h>

#include "map.h"

#define DEFAULT 0x0

void screenSetup(uint32_t set);
void screenDraw();


#endif      // __DISPLAY_H__