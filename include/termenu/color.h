#ifndef COLOR_H
#define COLOR_H

#include <termbox2.h>

typedef struct {
  uintattr_t foreground, background;
} Color;

#endif
