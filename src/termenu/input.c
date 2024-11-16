#include <termenu/input.h>

void input_add_char(Input* input, char new_char) {
  unsigned int contents_length = strlen(input->contents);
  if(contents_length + 2 < input->contents_size) {
    input->contents[contents_length] = new_char;
    input->contents[contents_length + 1] = '\0';

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
