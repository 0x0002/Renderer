#include "Core/PermAllocator.h"
#include "Core/Assert.h"

// global instance
PermAllocator g_permAllocator( "PermAllocator" );

PermAllocator::PermAllocator( char const *name ) :
    Allocator( name ),
    m_begin( nullptr ),
    m_end( nullptr ),
    m_initialized( false ) {
}

void PermAllocator::Initialize( void *memory, size_t size ) {
    m_begin = memory;
    m_end = OffsetPtr( m_begin, size );

    m_initialized = true;
}

void PermAllocator::Deinitialize() {
    m_initialized = false;
}

void* PermAllocator::Allocate( size_t size ) {
    Assert( m_initialized, "HeapAllocator \"%s\" is not initialized.", GetName() );

    size_t allocSize = ( size + kMinAllocSize - 1 ) & ~( kMinAllocSize - 1 );

    if( allocSize > Available() ) {
        AssertAlways( "Failed to allocate %llx bytes from %s.", allocSize, GetName() );
        return nullptr;
    }

    void *alloc = m_begin;
    m_begin = OffsetPtr( m_begin, allocSize );

    return alloc;
}

void PermAllocator::Deallocate( void * /*ptr*/ ) {
    // do nothing
}

void* PermAllocator::Begin() {
    return m_begin;
}

bool PermAllocator::IsInitialized() const {
    return m_initialized;
}