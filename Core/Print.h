#ifndef PRINT_H
#define PRINT_H

#include "Core/StdTypes.h"

// console text colors
namespace PrintColor{

    // bit 0 - foreground blue
    // bit 1 - foreground green
    // bit 2 - foreground red
    // bit 3 - foreground intensity

    // bit 4 - background blue
    // bit 5 - background green
    // bit 6 - background red
    // bit 7 - background intensity

    enum Type{
        kRed      = 0x0C,
        kGreen    = 0x0A,
        kBlue     = 0x09,
        kCyan     = 0x0B,
        kMagenta  = 0x0D,
        kYellow   = 0x0E
    };

}

// print to visual studio output window
void Print( char const *format, ... );
void PrintLine( char const *format, ... );

// print to the console window
void PrintConsole( char const *format, ... );
void PrintConsole( PrintColor::Type color, char const *format, ... );
void PrintLineConsole( char const *format, ... );
void PrintLineConsole( PrintColor::Type color, char const *format, ... );

void Printf( char const *format, ... );

template<size_t size>
void Sprintf( char buffer[size], char const *format, ... );
void Sprintf( char *buffer, size_t size, char const *format, ... );

#endif // PRINT_H