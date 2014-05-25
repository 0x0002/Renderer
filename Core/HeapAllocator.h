#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include "Core/Allocator.h"

// based on http://web.ics.purdue.edu/~cs354/labs/lab6/
class HeapAllocator : public Allocator {
public:
    HeapAllocator( char const *name );

    // initialize free lists
    void Initialize( void *memory, size_t size );

    // disable the allocator
    void Deinitialize();

    // allocate a block of memory large enough to hold 'size' bytes. returns NULL if allocation fails
    void* Allocate( size_t size );

    // return a block of memory to the free lists
    void Deallocate( void *ptr );

private:
    struct Header {
        size_t m_size;       // size of the memory block including header and footer
        size_t m_flags;      // see Flags enum below
    };
    typedef Header Footer;

    struct FreeHeader {
        size_t      m_size;  // size of the memory block including header and footer
        size_t      m_flags; // see Flags enum below
        FreeHeader *m_next;  // this is only valid for free blocks of memory
        Footer     *m_prev;  // this is only valid for free blocks of memory
    };

    enum Flags {
        kFree  = 0,
        kInUse = 1
    };

    enum {
        kFreeListCount   = 65,
        kFreeListMaxSize = ( kFreeListCount - 1 ) * 8,
        kMinAllocSize    = 16, // need at least enough space for FreeHeader::m_next and FreeHeader::m_prev
    };

    // returns the header of this memory block
    inline FreeHeader* GetFreeHeader( Footer *footer ) { return (FreeHeader*)OffsetPtr( footer, sizeof( Footer ) - footer->m_size ); }

    // returns the footer of this memory block
    inline Footer* GetFooter( FreeHeader *header ) { return (Footer*)OffsetPtr( header, header->m_size - sizeof( Footer ) ); }

    // returns the header of the next adjacent memory block
    inline FreeHeader* GetNextFreeHeader( Footer *footer ) { return (FreeHeader*)OffsetPtr( footer, sizeof( Footer ) ); }

    // returns the header of the previous adjacent memory block
    inline Footer* GetPrevFooter( FreeHeader *header ) { return (Footer*)OffsetPtr( header, -(intptr_t)sizeof( Footer ) ); }

    // get a free list index for memory block of given size
    inline size_t GetListIndex( size_t size ) { return size >= kFreeListMaxSize ? ( kFreeListCount - 1 ) : size / 8; }

    // set size in both header and footer
    inline void SetSize( FreeHeader *header, size_t size ) {
        header->m_size = size;
        GetFooter( header )->m_size = size;
    }

    // set flags in both header and footer
    inline void SetFlags( FreeHeader *header, size_t flags ) {
        header->m_flags = flags;
        GetFooter( header )->m_flags = flags;
    }

    // find a free block of memory
    FreeHeader* Find( size_t size );

    // add free memory to an appropriate list
    void Insert( FreeHeader *header );

    // remove from a free list
    void Remove( FreeHeader const *header );

private:
    FreeHeader **m_freeLists;
    bool         m_initialized;
};

// global instance
extern HeapAllocator g_heapAllocator;

#endif // HEAP_ALLOCATOR_H