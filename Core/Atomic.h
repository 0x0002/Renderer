#ifndef ATOMIC_H
#define ATOMIC_H

#include "Core/StdTypes.h"

// variables must be aligned on a 32-bit boundary
uint32_t AtomicAdd( volatile uint32_t *addend, uint32_t value );
uint32_t AtomicSubtract( volatile uint32_t *addend, uint32_t value );
uint32_t AtomicSwap( volatile uint32_t *destination, uint32_t value );
uint32_t AtomicCompareAndSwap( volatile uint32_t *destination, uint32_t value, uint32_t comparand );
uint32_t AtomicIncrement( volatile uint32_t *addend );
uint32_t AtomicDecrement( volatile uint32_t *addend );

// variables must be aligned on a 64-bit boundary
uint64_t AtomicAdd( volatile uint64_t *addend, uint64_t value );
uint64_t AtomicSubtract( volatile uint64_t *addend, uint64_t value );
uint64_t AtomicSwap( volatile uint64_t *destination, uint64_t value );
uint64_t AtomicCompareAndSwap( volatile uint64_t *destination, uint64_t value, uint64_t comparand );
uint64_t AtomicIncrement( volatile uint64_t *addend );
uint64_t AtomicDecrement( volatile uint64_t *addend );

#endif // ATOMIC_H