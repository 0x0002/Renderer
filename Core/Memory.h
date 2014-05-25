#ifndef MEMORY_H
#define MEMORY_H

#include "Core/StdTypes.h"
#include "Core/MemoryManager.h"

void Memcpy( void *dst, size_t dstSize, void *src, size_t size );
void Memmove( void *dst, size_t dstSize, void *src, size_t size );
void Memset( void *dst, uint8_t val, size_t size );

#endif // MEMORY_H