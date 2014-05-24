#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Container/String.h"

class Allocator {
public:
    Allocator( String const &name );

    void* Allocate( size_t size );
    void Deallocate( void *p );

    String const& GetName() const;

private:
    String m_name;
};

// global instance
extern Allocator g_defaultAllocator;

#endif // ALLOCATOR_H
