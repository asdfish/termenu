#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "utils/string_utils.h"
#include "utils/termbox_utils.h"

#define EXAMPLE_USAGE "\"termenu \"item 1\\nitem2\" | $SHELL\"\n"

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

  const char* items_raw = argv[1];
  char** items = string_separate(items_raw, delimiter);
  if(items == NULL) {
    fprintf(stderr, "malloc failed\n");
    fflush(stderr);
    return -1;
  }


  free(items);
  return 0;
}
