#include "Core/Print.h"

#include <cstdio>
#include <stdarg.h>
#include <windows.h>

enum { 
    kVSOutputBufferSize = 1024 * 100,
    kConsoleBufferSize  = 1024 * 100
};

void va_Print( char const *format, va_list args );
void va_PrintLine( char const *format, va_list args );
void va_PrintConsole( char const *format, va_list args );
void va_PrintConsole( PrintColor::Type color, char const *format, va_list args );
void va_PrintLineConsole( char const *format, va_list args );
void va_PrintLineConsole( PrintColor::Type color, char const *format, va_list args );

// print to visual studio output window
void Print( char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_Print( format, args );
    va_end( args );
}

void va_Print( char const *format, va_list args ) {
    char buffer[ kVSOutputBufferSize ];
    vsprintf_s( buffer, kVSOutputBufferSize, format, args );
    OutputDebugString( buffer );
}

void PrintLine( char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_PrintLine( format, args );
    va_end( args );
}

void va_PrintLine( char const *format, va_list args ) {
    char buffer[ kVSOutputBufferSize ];
    vsprintf_s( buffer, kVSOutputBufferSize, format, args );
    strcat_s( buffer, "\n" );
    OutputDebugString( buffer );
}

// print to the console window
void PrintConsole( char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_PrintConsole( format, args );
    va_end( args );
}

void va_PrintConsole( char const *format, va_list args ) {
    vprintf( format, args );
}

void PrintConsole( PrintColor::Type color, char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_PrintConsole( color, format, args );
    va_end( args );
}

void va_PrintConsole( PrintColor::Type color, char const *format, va_list args ) {
    // get a handle to stdout
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

    // store the current stdout state
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hstdout, &csbi );

    // change the color
    SetConsoleTextAttribute( hstdout, (WORD)color );

    vprintf( format, args );

    // set to original color
    SetConsoleTextAttribute( hstdout, csbi.wAttributes );
}

void PrintLineConsole( char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_PrintLineConsole( format, args );
    va_end( args );
}

void va_PrintLineConsole( char const *format, va_list args ) {
    char buffer[ kConsoleBufferSize ];
    vsprintf_s( buffer, kConsoleBufferSize, format, args );
    strcat_s( buffer, "\n" );
    printf( "%s", buffer );
}

void PrintLineConsole( PrintColor::Type color, char const *format, ... ) {
    va_list args;
    va_start( args, format );
    va_PrintLineConsole( color, format, args );
    va_end( args );
}

void va_PrintLineConsole( PrintColor::Type color, char const *format, va_list args ) {
    char buffer[ kConsoleBufferSize ];

    // get a handle to stdout
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

    // store the current stdout state
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hstdout, &csbi );

    // change the color
    SetConsoleTextAttribute( hstdout, (WORD)color );

    vsprintf_s( buffer, kConsoleBufferSize, format, args );
    strcat_s( buffer, "\n" );
    printf( "%s", buffer );

    // set to original color
    SetConsoleTextAttribute( hstdout, csbi.wAttributes );
}

void Printf( char const *format, ... ) {
    va_list args;
    va_start( args, format );
    vprintf_s( format, args );
    va_end( args );
}

template<size_t size>
void Sprintf( char buffer[size], char const *format, ... ) {
    va_list args;
    va_start( args, format );
    vsprintf_s( buffer, format, args );
    va_end( args );
}

void Sprintf( char *buffer, size_t size, char const *format, ... ) {
    va_list args;
    va_start( args, format );
    vsprintf_s( buffer, size, format, args );
    va_end( args );
}