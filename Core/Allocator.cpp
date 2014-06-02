#include "Core/Allocator.h"
#include <memory>

Allocator::Allocator( char const *name ) : m_name( name ) {
}

void* Allocator::Allocate( size_t size ) {
    return operator new( size );
}

void Allocator::Deallocate( void *p ) {
    operator delete( p );
}

char const* Allocator::GetName() const {
    return m_name;
}
bool Allocator::operator==( Allocator const &allocator ) const {
    return this == &allocator;
}

bool Allocator::operator!=( Allocator const &allocator ) const {
    return this != &allocator;
}