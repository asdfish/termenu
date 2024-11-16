#include <common/string_utils.h>
#include <stdlib.h>
#include <string.h>

bool string_contains(const char* string, const char* query) {
  if(strstr(string, query) != NULL)
    return true;

  return false;
}

unsigned int string_count(const char* string, const char* query) {
  unsigned int count = 0;
  unsigned int query_length = strlen(query);

  const char* string_pointer = string;

  while((string_pointer = strstr(string_pointer, query)) != NULL) {
    count ++;
    string_pointer += query_length;
  }

  return count;
}

void string_delete_char(char* string, unsigned int index) {
  strcpy(string + index, string + index + 1);
}

char** string_find_in_array(char** array, const char* query, unsigned int* length) {
  unsigned int query_occurences = 0;
  for(unsigned int i = 0; array[i] != NULL; i ++)
    if(string_contains(array[i], query))
      query_occurences ++;

  if(length != NULL)
    *length = query_occurences;

  char** output = (char**) malloc((query_occurences + 1) * sizeof(const char*));
  if(output == NULL)
    return NULL;

  for(unsigned int i = 0, j = 0; array[i] != NULL; i ++)
    if(string_contains(array[i], query)) {
      output[j] = array[i];
      j ++;
    }
  output[query_occurences] = NULL;

  return output;
}

char** string_separate(const char* string, const char* delimiter, unsigned int* length) {
  char* string_copy = strdup(string);
  if(string_copy == NULL)
    return NULL;

  unsigned int count = string_count(string_copy, delimiter);
  if(length != NULL)
    *length = count;

  char** array = (char**)malloc((count + 1) * sizeof(char*));
  if(array == NULL) {
    free(string_copy);
    return NULL;
  }

  if(count != 0) {
    char* buffer;
    unsigned int i = 0;
    while((buffer = strsep(&string_copy, delimiter)) != NULL) {
      array[i] = buffer;
      i ++;
    }
  }
  array[count] = NULL;

  free(string_copy);
  return array;
}
