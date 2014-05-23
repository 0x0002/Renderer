#include "Core/Allocator.h"

#include <memory>

// global instance
Allocator g_defaultAllocator( "DefaultAllocator" );

Allocator::Allocator( String const &name ) : m_name( name ) {
}

void* Allocator::Allocate( size_t size ) {
    return operator new( size );
}

void Allocator::Deallocate( void *p ) {
    operator delete( p );
}

String const& Allocator::GetName() const {
    return m_name;
}