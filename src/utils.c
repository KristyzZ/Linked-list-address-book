#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void read_string(char *buffer, int size) 
{
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

const char *get_error_message(int error_code)
{
    switch (error_code) {
        case SUCCESS:
            return SUCCESS;

        case ERROR_EMPTY_LIST:
            return "Address book is empty";

        case ERROR_INVALID_POSITION:
            return "Invalid position";

        case ERROR_DISPLAY_FAILED:
            return "Display failed";

        case ERROR_NULL_POINTER:
            return "Null pointer error";

        case ERROR_NO_RECORD:
            return "No matching record found";

        default:
            return "Unknown error";
    }
}