#include "Core/HeapAllocator.h"
#include "Core/Memory.h"
#include "Core/Assert.h"

// global instance
HeapAllocator g_heapAllocator( "HeapAllocator" );

// constructor
HeapAllocator::HeapAllocator( char const *name ) :
    Allocator( name ),
    m_freeLists( nullptr ),
    m_initialized( false ) {
}

// initialize free lists
void HeapAllocator::Initialize( void *memory, size_t size ) {
    m_freeLists = (FreeHeader**)memory;
    size_t freeListSize = sizeof( FreeHeader* ) * kFreeListCount;
    Memset( m_freeLists, 0, freeListSize );

    // add dummy header and footer
    Header *dummyHeader = (Header*)OffsetPtr( memory, size - sizeof( Header ) );
    dummyHeader->m_size = 0;
    dummyHeader->m_flags = kInUse;

    Footer *dummyFooter = (Footer*)OffsetPtr( memory, freeListSize );
    dummyFooter->m_size = 0;
    dummyFooter->m_flags = kInUse;

    // initialize free block of memory
    FreeHeader *header = (FreeHeader*)OffsetPtr( memory, freeListSize + sizeof( Footer ) );
    header->m_size  = size - freeListSize - sizeof( Header ) - sizeof( Footer );
    header->m_flags = kFree;
    header->m_next = nullptr;
    header->m_prev = nullptr;
    m_freeLists[GetListIndex( header->m_size )] = header;

    m_initialized = true;
}

// disable the allocator
void HeapAllocator::Deinitialize() {
    m_initialized = false;
}

// allocate a block of memory large enough to hold 'size' bytes. returns nullptr if allocation fails
void* HeapAllocator::Allocate( size_t size ) {
    Assert( m_initialized, "HeapAllocator \"%s\" is not initialized.", GetName() );

    // add space for header/footer and round up size to the next multiple of 8 or 16 bytes
    size_t allocSize = ( size + kMinAllocSize - 1 + sizeof( Header ) + sizeof( Footer ) ) & ~( kMinAllocSize - 1 );

    FreeHeader *header = Find( allocSize );
    if( !header ) {
        AssertAlways( "Failed to allocate %llx bytes from %s.", allocSize, GetName() );
        return nullptr;
    }

    Remove( header );

    size_t unusedSize = header->m_size - allocSize;
    if( unusedSize >= sizeof( Header ) + sizeof( Footer ) + kMinAllocSize ) {
        // split off part of this memory block and store it in a smaller list
        SetSize( header, allocSize );
        SetFlags( header, kInUse );

        FreeHeader *unusedHeader = GetNextFreeHeader( GetFooter( header ) );
        SetSize( unusedHeader, unusedSize );
        SetFlags( unusedHeader, kFree );
        Insert( unusedHeader );
    }

    SetFlags( header, kInUse );
    return OffsetPtr( header, sizeof( Header ) );
}

// return a block of memory to the free lists
void HeapAllocator::Deallocate( void *ptr ) {
    if( !ptr )
        return;

    FreeHeader *header = (FreeHeader*)OffsetPtr( ptr, -(intptr_t)sizeof( Header ) );
    SetFlags( header, kFree );
    Insert( header );
}

// find a free block of memory
HeapAllocator::FreeHeader* HeapAllocator::Find( size_t size ) {
    size_t list = GetListIndex( size );

    FreeHeader *header = m_freeLists[list];
    while( !header && list < kFreeListCount )
        header = m_freeLists[++list];

    if( list == ( kFreeListCount - 1 ) ) {
        while( header && header->m_size < size )
            header = header->m_next;
    }

    return list != kFreeListCount ? header : nullptr;
}

// add free memory to an appropriate list
void HeapAllocator::Insert( FreeHeader *header ) {
    // combine adjacent free blocks
    Footer *previousFooter = GetPrevFooter( header );
    if( previousFooter->m_flags != kInUse ) {
        FreeHeader *previousHeader = GetFreeHeader( previousFooter );
        Remove( previousHeader );
        SetSize( previousHeader, previousHeader->m_size + header->m_size );
        previousHeader->m_next = header->m_next;
        header = previousHeader;
    }

    FreeHeader *nextHeader = GetNextFreeHeader( GetFooter( header ) );
    if( nextHeader->m_flags != kInUse ) {
        Remove( nextHeader );
        SetSize( header, header->m_size + nextHeader->m_size );
        header->m_next = nextHeader->m_next;
    }

    size_t size = header->m_size;
    size_t list = GetListIndex( size );

    FreeHeader *next = m_freeLists[list];
    FreeHeader *previous = nullptr;

    if( list == ( kFreeListCount - 1 ) ) {
        // insert in order, sorted smallest to largest
        while( next && next->m_size < size ) {
            previous = next;
            next = next->m_next;
        }
    }

    // insert into a free list
    header->m_next = next;
    header->m_prev = previous ? GetFooter( previous ) : nullptr;
    if( next )
        next->m_prev = GetFooter( header );

    if( previous )
        previous->m_next = header;

    if( next == m_freeLists[list] )
        m_freeLists[list] = header;
}

// remove from a free list
void HeapAllocator::Remove( FreeHeader const *header ) {
    size_t list = GetListIndex( header->m_size );
    if( header->m_prev )
        GetFreeHeader( header->m_prev )->m_next = header->m_next;

    if( header->m_next )
        header->m_next->m_prev = header->m_prev;

    if( m_freeLists[list] == header )
        m_freeLists[list] = header->m_next;
}