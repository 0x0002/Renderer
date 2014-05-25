#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Core/StdTypes.h"

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

template<typename T>
inline void Construct( T *p, T const &val ) {
    new ( p ) T( val );
}

template<typename T>
inline void Destroy( T *val ) {
    val->~T();
}

#endif // ALLOCATOR_H
