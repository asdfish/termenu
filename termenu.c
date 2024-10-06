#include <stdio.h>

#include "config.h"
#include "utils/string_utils.h"

#define EXAMPLE_USAGE "\"termenu \"item 1\\nitem2\" | $SHELL\"\n"

int main(int argc, const char* argv[]) {
  const char* delimiter = NULL;

  switch(argc) {
    case 1:
      fprintf(stderr, "Not enough arguments\nExample usage:\n" EXAMPLE_USAGE);
      return -1;
    case 3:
      delimiter = argv[2];
      break;
    default:
      delimiter = DEFAULT_DELIMITER;
      break;
  }

  const char* items_raw = argv[1];
  const char** items = string

  return 0;
}
