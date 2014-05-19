#include "Atomic.h"
#include <Windows.h>

// variables must be aligned on a 32-bit boundary
uint32_t AtomicAdd( volatile uint32_t *addend, uint32_t value ) {
    return InterlockedExchangeAdd( addend, value );
}

uint32_t AtomicSubtract( volatile uint32_t *addend, uint32_t value ) {
    return InterlockedExchangeSubtract( addend, value );
}

uint32_t AtomicSwap( volatile uint32_t *destination, uint32_t value ) {
    return InterlockedExchange( destination, value );
}

uint32_t AtomicCompareAndSwap( volatile uint32_t *destination, uint32_t value, uint32_t comparand ) {
    return InterlockedCompareExchange( destination, value, comparand );
}

uint32_t AtomicIncrement( volatile uint32_t *addend ) {
    return InterlockedIncrement( addend );
}

uint32_t AtomicDecrement( volatile uint32_t *addend ) {
    return InterlockedDecrement( addend );
}

// variables must be aligned on a 64-bit boundary
uint64_t AtomicAdd( volatile uint64_t *addend, uint64_t value ) {
    return InterlockedExchangeAdd( addend, value );
}

uint64_t AtomicSubtract( volatile uint64_t *addend, uint64_t value ) {
    return InterlockedExchangeSubtract( addend, value );
}

uint64_t AtomicSwap( volatile uint64_t *destination, uint64_t value ) {
    return InterlockedExchange( destination, value );
}

uint64_t AtomicCompareAndSwap( volatile uint64_t *destination, uint64_t value, uint64_t comparand ) {
    return InterlockedCompareExchange( destination, value, comparand );
}

uint64_t AtomicIncrement( volatile uint64_t *addend ) {
    return InterlockedIncrement( addend );
}

uint64_t AtomicDecrement( volatile uint64_t *addend ) {
    return InterlockedDecrement( addend );
}
