#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Core/Align.h"
#include "Core/IEEE754.h"
#include "Core/MemoryManager.h"

#include <cstdint>

#define OffsetPtr( ptr, bytes ) (void*)((char*)(ptr) + (bytes))

#define SubPtr( ptr1, ptr2 ) (ptrdiff_t)((char*)(ptr1) - (char*)(ptr2))

#endif // STD_TYPES_H