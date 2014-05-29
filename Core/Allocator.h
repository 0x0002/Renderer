#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Core/StdTypes.h"

#include <new>

class Allocator {
public:
    Allocator( char const *name ); // does not make a copy of string

    void* Allocate( size_t size );
    void Deallocate( void *ptr );

    char const* GetName() const;

    bool operator==( Allocator const &allocator ) const;
    bool operator!=( Allocator const &allocator ) const;

private:
    char const *m_name;
};

#pragma warning( push )
#pragma warning( disable: 4100 )

template<typename T>
inline void Construct( T *p ) {
    new ( p ) T();
}

template<typename T>
inline void Construct( T *p, T const &val ) {
    new ( p ) T( val );
}

template<typename T>
inline void Destruct( T *val ) {
    val->~T();
}

#pragma warning( pop )

#endif // ALLOCATOR_H
