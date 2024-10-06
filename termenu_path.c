#include "utils/string_utils.h"

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  const char* path = getenv("PATH");
  if(path == NULL)
    return -1;

  char** path_separated = string_separate(path, ":", NULL);
  if(path_separated == NULL)
    return -1;

  for(unsigned int i = 0; path_separated[i] != NULL; i ++) {
    DIR* directory_pointer = opendir(path_separated[i]);
    if(directory_pointer == NULL)
      continue;

    struct dirent* dirent_pointer;
    while((dirent_pointer = readdir(directory_pointer)) != NULL)
      if(dirent_pointer->d_type == DT_REG)
        fprintf(stdout, "%s\n", dirent_pointer->d_name);

    closedir(directory_pointer);
  }
  fflush(stdout);

  free(path_separated);
  return 0;
}
