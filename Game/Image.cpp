#include "Game/Image.h"

#include "Core/File.h"
#include "Core/Assert.h"
#include "Math/Math.h"

void WritePPM( FilePath const &path, uint32_t width, uint32_t height, float const *data ) {
    // 16 bit ppm format

    FILE *file;
    fopen_s(  &file, path.FullPath(), "wb" );
    Assert( file, "Could not open %s", path.FullPath() );

    float maxValue = 65535.0f;
    fprintf( file, "P6\n%d %d\n%d\n", width, height, (int)maxValue );

    size_t size = width * height * 2 * 3;
    uint8_t *bytes = new uint8_t[size];

    uint8_t *p = bytes;
    for( uint32_t r = 0; r < height; ++r ) {
        for( uint32_t c = 0; c < width; ++c ) {
            uint16_t r = (uint16_t)Clamp( maxValue * *data++, 0.0f, maxValue );
            uint16_t g = (uint16_t)Clamp( maxValue * *data++, 0.0f, maxValue );
            uint16_t b = (uint16_t)Clamp( maxValue * *data++, 0.0f, maxValue );
            *p++ = (uint8_t)( r / 256 );
            *p++ = (uint8_t)( r % 256 );
            *p++ = (uint8_t)( g / 256 );
            *p++ = (uint8_t)( g % 256 );
            *p++ = (uint8_t)( b / 256 );
            *p++ = (uint8_t)( b % 256 );
        }
    }

    fwrite( bytes, 1, size, file );

    delete []bytes;
    fclose( file );
}