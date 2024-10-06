#pragma once
#include <stdbool.h>

// returns true if string contains query, else false
bool string_contains(const char* string, const char* query);

// returns the occurences of query in string
unsigned int string_count(const char* string, const char* query);

// deletes 1 char from string at index
void string_delete_char(char* string, unsigned int index);

// returns NULL terminated array of strings from a array which must be NULL terminated
// must be free() ed
// returns NULL on failure
// changes length to length of array
char** string_find_in_array(char** array, const char* query, unsigned int* length);

// returns string separated by delimiter as NULL terminated array
// must be free() ed
// returns NULL on failure
char** string_separate(const char* string, const char* delimiter);

// returns a heap string that that replaces all occurences of query with replacement in string
// must be free() ed
// returns NULL on failure
/*char* string_replace_all(const char* string, const char* query, const char* replacement);*/

// gets length of a replaced string
/*unsigned int string_replaced_length(const char* string, const char* query, const char* replacement);*/
