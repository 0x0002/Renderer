#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Core/StdTypes.h"

class MemoryManager {
public:
    MemoryManager( size_t totalMemory );
    ~MemoryManager();

    void Initialize();
    void SetHeapAllocator();

    void* Allocate( size_t size );
    void Deallocate( void *ptr );

private:
    typedef void* (*AllocFn)( size_t size );
    typedef void (*DeallocFn)( void *ptr );

    AllocFn   m_allocFn;
    DeallocFn m_deallocFn;

    void *m_begin; // allocated from operator new
    void *m_end;   // end of memory
};

// global instance
extern MemoryManager g_memoryManager;

inline void* operator new( size_t size ) throw() {
    return g_memoryManager.Allocate( size );
}

inline void operator delete( void *ptr ) throw() {
    g_memoryManager.Deallocate( ptr );
}

inline void* operator new[]( size_t size ) throw() {
    return g_memoryManager.Allocate( size );
}

inline void operator delete[]( void *ptr ) throw() {
    g_memoryManager.Deallocate( ptr );
}

#endif // MEMORY_MANAGER_H