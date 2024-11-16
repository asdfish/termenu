#include <termenu/menu.h>

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

    const char* item_name = menu->items[item];

    for(unsigned int j = 0; j < menu->width; j ++) {
      char next_char = ' ';

      if(j < strlen(item_name))
        next_char = item_name[j];
      
      tb_set_cell(menu->x + j, menu->y + i, next_char, color->foreground, color->background);
    }
  }
}

void menu_move_cursor(Menu* menu, int step) {
  if((int) menu->cursor + step > 0)
    menu->cursor += step;
  else
    menu->cursor = 0;

  if(menu->cursor > menu->items_length - 1)
    menu->cursor = menu->items_length - 1;
}
