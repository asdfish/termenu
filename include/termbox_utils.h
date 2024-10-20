#pragma once
#include <termbox2.h>
#include <stdbool.h>

/*#define NO_MENU_SELECTIONS*/

typedef struct {
  uintattr_t foreground, background;
} Color;

typedef struct {
  unsigned int x, y;
  unsigned int width, height;

  unsigned int camera, cursor;

  Color cursor_color, normal_color;
/*#ifndef NO_MENU_SELECTIONS*/
/*  const char* selection_prefix;*/
/*#endif*/

  // do not modify
  char** items;
/*#ifndef NO_MENU_SELECTIONS*/
/*  bool* selections;*/
/*#endif*/
  unsigned int items_length;
} Menu;

/*#ifndef NO_MENU_SELECTIONS*/
/*// changes menu items from a NULL terminated array*/
/*// returns 0 on success, negative on failure*/
/*int menu_change_items(Menu* menu, const char** new_items);*/
/*#else*/
// still requires a NULL terminated array
/*void menu_change_items(Menu* menu, const char** new_items);*/
/*#endif*/
void menu_draw(Menu* menu);
void menu_move_cursor(Menu* menu, int step);
/*#ifndef NO_MENU_SELECTIONS*/
/*void menu_free(Menu* menu);*/
/*#endif*/

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
// returns -1 on failure 0 on success
int input_init(Input* input);
/*void input_move_cursor(Input* input, int step);*/
