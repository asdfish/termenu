#ifndef INPUT_H
#define INPUT_H

#include <termenu/color.h>

typedef struct {
  unsigned int x, y, width;

  Color cursor_color, normal_color;

  unsigned int camera, cursor;

  unsigned int contents_size;
  // do not touch, read only
  char* contents;
} Input;

void input_add_char(Input* input, char new_char);
void input_del_char(Input* input);
void input_draw(Input* input);
void input_free(Input* input);
int input_init(Input* input);

#endif
