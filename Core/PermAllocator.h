#ifndef PERM_ALLOCATOR_H
#define PERM_ALLOCATOR_H

#include "Core/Allocator.h"

class PermAllocator : public Allocator {
public:
    PermAllocator( char const *name );
    void Initialize( void *memory, size_t size );
    void Deinitialize();

    void* Allocate( size_t size );
    void Deallocate( void *ptr );

    void *Begin();
    bool IsInitialized() const;

private:
    enum {
        kMinAllocSize = 16
    };

    inline size_t Available() { return SubPtr( m_end, m_begin ); }

    void *m_begin;
    void *m_end;

    bool  m_initialized;
};

// global instance
extern PermAllocator g_permAllocator;

#endif // PERM_ALLOCATOR_H