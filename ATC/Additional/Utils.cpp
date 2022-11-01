#include "Utils.h"

int MessageReturn(int return_value, const char* format, ... )
    {
    va_list ptr;
    va_start(ptr, format);

    vprintf (format, ptr);

    return return_value;
    }