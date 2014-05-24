#include "Core/Assert.h"

#include <cstdio>
#include <cstring>
#include <windows.h>

void ReportError( const char *errorType,
                  const char *file,
                  int line,
                  const char *format,
                  ... ) {
    enum { kBufferSize = 1024 };
    char outputWindowMessage[ kBufferSize ];
    char messageBoxMessage[ kBufferSize ];

    // print out the file and line in visual studio format so the error
    // can be double clicked in the output window file(line) : error
    int offset = sprintf_s( outputWindowMessage, "%s(%d) : ", file , line );	
    if( format ) {	
        va_list args;
        va_start( args, format );
        vsnprintf_s( outputWindowMessage + offset,
            kBufferSize - offset,
            _TRUNCATE,
            format,
            args );
        vsnprintf_s( messageBoxMessage,
            kBufferSize,
            _TRUNCATE,
            format,
            args );
        va_end( args );
    }
    else{
        strcpy_s( outputWindowMessage + offset, kBufferSize - offset, "No error message" );
        strcpy_s( messageBoxMessage, kBufferSize, "No error message" );
    }

    // print to visual studio output window
    OutputDebugString( outputWindowMessage );
    OutputDebugString( "\n" );

    // display a message box
    MessageBox( NULL, messageBoxMessage, errorType, 0 );
}