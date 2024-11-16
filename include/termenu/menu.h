#ifndef MENU_H
#define MENU_H

#include <termenu/color.h>

typedef struct {
  unsigned int x, y;
  unsigned int width, height;

  unsigned int camera, cursor;

  Color cursor_color, normal_color;
  // do not modify
  char** items;
  unsigned int items_length;
} Menu;

void menu_draw(Menu* menu);
void menu_move_cursor(Menu* menu, int step);

#endif
