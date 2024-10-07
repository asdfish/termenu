#include "termbox_utils.h"

/*#ifndef NO_MENU_SELECTIONS*/
/*int menu_change_items(Menu* menu, const char** new_items) {*/
/*#else*/
/*void menu_change_items(Menu* menu, const char** new_items) {*/
/*#endif*/
/*  for(menu->items_length = 0; new_items[menu->items_length] != NULL; menu->items_length ++);*/
/**/
/*  menu->items = new_items;*/
/**/
/*#ifndef NO_MENU_SELECTIONS*/
/*  menu_free(menu);*/
/**/
/*  menu->selections = (bool*) calloc(menu->items_length, sizeof(bool));*/
/*  if(menu->selections == NULL)*/
/*    return -1;*/
/**/
/*  return 0;*/
/*#endif*/
/*}*/

void menu_draw(Menu* menu) {
  if(menu->camera > menu->cursor)
    menu->camera = menu->cursor;
  else if(menu->camera + menu->height - 1 < menu->cursor)
    menu->camera = menu->cursor - menu->height + 1;

  for(unsigned int i = 0; i < menu->height; i ++) {
    unsigned int item = menu->camera + i;

    if(item >= menu->items_length) {
      for(unsigned int j = 0; j < menu->width; j ++)
        tb_set_cell(menu->x + j, menu->y + i, ' ', menu->normal_color.foreground, menu->normal_color.background);
      continue;
    }

    Color* color = &menu->normal_color;
    if(item == menu->cursor)
      color = &menu->cursor_color;

/*#ifndef NO_MENU_SELECTIONS*/
/*    bool item_selected = menu->selections[item];*/
/*#endif*/
    const char* item_name = menu->items[item];

    for(unsigned int j = 0; j < menu->width; j ++) {
      char next_char = ' ';

/*#ifndef NO_MENU_SELECTIONS*/
/*      if(item_selected) {*/
/*        if(j < strlen(menu->selection_prefix))*/
/*          next_char = menu->selection_prefix[j];*/
/*        else if(j - strlen(menu->selection_prefix))*/
/*          next_char = item_name[j - strlen(menu->selection_prefix)];*/
/*      } else if(j < strlen(item_name))*/
/*#else*/
      if(j < strlen(item_name))
/*#endif*/
        next_char = item_name[j];
      
      tb_set_cell(menu->x + j, menu->y + i, next_char, color->foreground, color->background);
    }
  }
}

/*#ifndef NO_MENU_SELECTIONS*/
/*void menu_free(Menu* menu) {*/
/*  if(menu->selections != NULL)*/
/*    free(menu->selections);*/
/*}*/
/*#endif*/

void menu_move_cursor(Menu* menu, int step) {
  if((int) menu->cursor + step > 0)
    menu->cursor += step;
  else
    menu->cursor = 0;

  if(menu->cursor > menu->items_length - 1)
    menu->cursor = menu->items_length - 1;
}

void input_add_char(Input* input, char new_char) {
  unsigned int contents_length = strlen(input->contents);
  if(contents_length + 2 < input->contents_size) {
    input->contents[contents_length] = new_char;
    input->contents[contents_length + 2] = '\0';

    input->cursor = strlen(input->contents);
  }
}

void input_del_char(Input* input) {
  input->contents[strlen(input->contents) - 1] = '\0';
}

void input_draw(Input* input) {
  unsigned int contents_length = strlen(input->contents);
  if(input->cursor > contents_length)
    input->cursor = contents_length;

  if(input->camera > input->cursor)
    input->camera = input->cursor;

  if(input->camera + input->width - 1 < input->cursor)
    input->camera = input->cursor - input->width + 1;

  for(unsigned int i = 0; i < input->width; i ++) {
    unsigned int contents_x = i + input->camera;
    Color* color = &input->normal_color;
    if(contents_x == input->cursor)
      color = &input->cursor_color;

    char next_char = ' ';

    if(contents_x < contents_length)
      next_char = input->contents[contents_x];

    tb_set_cell(i + input->x, input->y, next_char, color->foreground, color->background);
  }
}

void input_free(Input* input) {
  free(input->contents);
}

int input_init(Input* input) {
  input->contents = malloc(input->contents_size * sizeof(char));
  if(input->contents == NULL)
    return -1;

  input->contents[0] = '\0';

  return 0;
}

/*void input_move_cursor(Input* input, int step) {*/
/*  if((int)input->cursor + step < 0)*/
/*    input->cursor = 0;*/
/*  else*/
/*    input->cursor += step;*/
/*}*/
