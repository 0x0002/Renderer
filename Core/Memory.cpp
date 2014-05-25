#include "Core/Memory.h"

#include <cstring>

void Memcpy( void *dst, size_t dstSize, void *src, size_t size ) {
    memcpy_s( dst, dstSize, src, size );
}

void Memmove( void *dst, size_t dstSize, void *src, size_t size ) {
    memmove_s( dst, dstSize, src, size );
}

void Memset( void *dst, uint8_t val, size_t size ) {
    memset( dst, val, size );
}