#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Container/String.h"

#include <utility>

class Allocator {
public:
    Allocator( String const &name );

    void* Allocate( size_t size );
    void Deallocate( void *p );

    String const& GetName() const;

    bool operator==( Allocator const &allocator ) const;
    bool operator!=( Allocator const &allocator ) const;

private:
    String m_name;
};

template<typename T>
__forceinline void Construct( T *p, T const &val ) {
    new ( p ) T( val );
}

template<typename T>
__forceinline void Destroy( T *val ) {
    val->~T();
}

// global instance
extern Allocator g_defaultAllocator;

#endif // ALLOCATOR_H
