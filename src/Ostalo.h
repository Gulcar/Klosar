#pragma once

#include <iostream>
#include <stdarg.h>

inline void Error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    printf("ERROR: ");
    vprintf(msg, args);
    printf("\n");

    va_end(args);
    std::exit(-1);
}
