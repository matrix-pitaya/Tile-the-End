#pragma once

#include"enum/enum.h"

#include <cstdarg>
#include <cstdio>

#define DEBUG_VERSION

namespace Core::Console
{
    inline void Print(const char* fmt, ...)
    {
#ifdef DEBUG_VERSION
        printf("\033[0m");
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\033[0m\n");
#endif
    }
    inline void Print(Core::Color color, const char* fmt, ...)
    {
#ifdef DEBUG_VERSION
        switch (color)
        {
            case Core::Color::White:    printf("\033[37m");  break;
            case Core::Color::Black:    printf("\033[30m");  break;
            case Core::Color::Green:    printf("\033[32m"); break;
            case Core::Color::Red:      printf("\033[31m"); break;
            case Core::Color::Yellow:   printf("\033[33m"); break;
            case Core::Color::Blue:     printf("\033[34m"); break;
            default:                    printf("\033[0m");  break;
        }
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\033[0m\n");
#endif
    }
}
