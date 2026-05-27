#ifndef UTILS_H
#define UTILS_H

#include "linked_list.h"

#define SUCCESS 0
#define ERROR_EMPTY_LIST 1
#define ERROR_INVALID_POSITION 2
#define ERROR_DISPLAY_FAILED 3
#define ERROR_NULL_POINTER 4
#define ERROR_NO_RECORD 5

void read_string(char *buffer, int size);
const char *get_error_message(int error_code);

#endif