#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "utils/string_utils.h"
#include "utils/termbox_utils.h"

#define EXAMPLE_USAGE "\"termenu \"item 1\\nitem2\" | $SHELL\"\n"

unsigned int width, height;

void draw_border(void);

int main(int argc, const char* argv[]) {
  const char* delimiter = NULL;

  switch(argc) {
    case 1:
      fprintf(stderr, "Not enough arguments\nExample usage:\n" EXAMPLE_USAGE);
      fflush(stderr);
      return -1;
    case 3:
      delimiter = argv[2];
      break;
    default:
      delimiter = DEFAULT_DELIMITER;
      break;
  }

  if(delimiter == NULL)
    return -1;

  unsigned int items_length = 0;

  const char* items_raw = argv[1];
  char** items = string_separate(items_raw, delimiter, &items_length);
  if(items == NULL) {
    fprintf(stderr, "malloc failed\n");
    fflush(stderr);
    return -1;
  }

  tb_init();

  width = tb_width();
  height = tb_height();

  Input input = {
    1, 1,
    width - 2,
    INPUT_CURSOR_COLOR, INPUT_NORMAL_COLOR,
    0, 0,
    INPUT_LENGTH,
    NULL
  };

  Menu menu = {
    1, 3,
    width - 2, height - 4,
    0, 0,
    MENU_CURSOR_COLOR, MENU_NORMAL_COLOR,

    items, items_length,
  };

  if(input_init(&input) != 0) {
    fprintf(stderr, "malloc failed\n");
    fflush(stderr);
    goto tb_shutdown;
  }

  draw_border();

  const char* allowed_chars = ALLOWED_CHARS;

  bool using_items = true;
  const char* selected_item = NULL;

  bool change_items = false;

  while(1) {
    if(change_items) {
      if(!using_items)
        free(menu.items);

      if(strlen(input.contents) != 0) {
        menu.items = string_find_in_array(items, input.contents, &menu.items_length);

        if(menu.items == NULL)
          goto exit_loop;

        menu.cursor = 0;
        using_items = false;
      } else {
        menu.items = items;
        menu.items_length = items_length;
        using_items = true;
      }
    }
    change_items = false;

    input_draw(&input);
    menu_draw(&menu);
    tb_present();

    struct tb_event event;
    tb_poll_event(&event);

    if(event.type == TB_EVENT_RESIZE) {
      width = tb_width();
      height = tb_height();
      draw_border();

      input.width = width - 2;

      menu.width = width - 2;
      menu.height = height- 4;
    }

    switch(event.key) {
      case TB_KEY_BACKSPACE:
      case TB_KEY_BACKSPACE2:
        input_del_char(&input);
        change_items = true;
        continue;

      case TB_KEY_ESC:
        goto exit_loop;

      case TB_KEY_ENTER:
        if(menu.cursor < menu.items_length)
          selected_item = menu.items[menu.cursor];
        else
          selected_item = input.contents;

        tb_shutdown();
        goto menu_submit;

      case TB_KEY_ARROW_UP:
        menu_move_cursor(&menu, -1);
        change_items = false;
        continue;
      case TB_KEY_ARROW_DOWN:
        menu_move_cursor(&menu, 1);
        change_items = false;
        continue;
    }

    if(event.ch < UCHAR_MAX) {
      char input_char[1];
      input_char[0] = event.ch;

      if(strstr(allowed_chars, input_char) != NULL) {
        input_add_char(&input, event.ch);
        change_items = true;
      }
    }
  }

menu_submit:
  if(selected_item != NULL) {
    fprintf(stdout, "%s", selected_item);
    fflush(stdout);
  }

exit_loop:
  if(!using_items)
    free(menu.items);
  input_free(&input);

tb_shutdown:
  tb_shutdown();
  free(items);
  return 0;
}

void draw_border(void) {
  for(unsigned int i = 1; i < width - 1; i ++) {
    tb_print_ex(i, 0, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_HORIZONTAL);
    tb_print_ex(i, 2, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_HORIZONTAL);
    tb_print_ex(i, height - 1, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_HORIZONTAL);
  }

  for(unsigned int i = 1; i < height - 1; i ++) {
    tb_print_ex(0, i, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_VERTICAL);
    tb_print_ex(width - 1, i, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_VERTICAL);
  }

  tb_print_ex(0, 0, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_TOP_LEFT);
  tb_print_ex(width - 1, 0, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_TOP_RIGHT);

  tb_print_ex(0, 2, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_MIDDLE_LEFT);
  tb_print_ex(width - 1, 2, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_MIDDLE_RIGHT);

  tb_print_ex(0, height - 1, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_BOTTOM_LEFT);
  tb_print_ex(width - 1, height - 1, BORDER_FOREGROUND, BORDER_BACKGROUND, NULL, BORDER_BOTTOM_RIGHT);
}
