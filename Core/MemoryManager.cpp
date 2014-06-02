#include "Core/MemoryManager.h"
#include <cstdlib>

size_t const kTotalMemory = 1024 * 1024 * 100; // 100MB

// global instance
MemoryManager g_memoryManager( kTotalMemory );

inline void* DefaultAllocate( size_t size ) { return malloc( size ); }
inline void* PermAllocate( size_t size ) { return g_permAllocator.Allocate( size ); }
inline void* HeapAllocate( size_t size ) { return g_heapAllocator.Allocate( size ); }

inline void DefaultDeallocate( void *ptr ) { free( ptr ); }
inline void PermDeallocate( void *ptr ) { g_permAllocator.Deallocate( ptr ); }
inline void HeapDeallocate( void *ptr ) { g_heapAllocator.Deallocate( ptr ); }

MemoryManager::MemoryManager( size_t totalMemory ) :
    m_allocFn( DefaultAllocate ),
    m_deallocFn( DefaultDeallocate ),
    m_begin( operator new( totalMemory ) ),
    m_end( OffsetPtr( m_begin, totalMemory ) ) {
    m_allocFn   = nullptr;
    m_deallocFn = nullptr;
}

MemoryManager::~MemoryManager() {
    operator delete( m_begin );
}

void MemoryManager::Initialize() {
    g_permAllocator.Initialize( m_begin, SubPtr( m_end, m_begin ) );
    m_allocFn   = PermAllocate;
    m_deallocFn = PermDeallocate;
}

void MemoryManager::Deinitialize() {
    m_allocFn   = DefaultAllocate;
    m_deallocFn = DefaultDeallocate;
}

void MemoryManager::SetHeapAllocator() {
    g_permAllocator.Deinitialize();
    g_heapAllocator.Initialize( g_permAllocator.Begin(), SubPtr( m_end, g_permAllocator.Begin() ) );
    m_allocFn   = HeapAllocate;
    m_deallocFn = HeapDeallocate;
}

void MemoryManager::UnsetHeapAllocator() {
    g_heapAllocator.Deinitialize();
    m_allocFn   = PermAllocate;
    m_deallocFn = PermDeallocate;
}

void* MemoryManager::Allocate( size_t size ) {
    return m_allocFn( size );
}

void MemoryManager::Deallocate( void *ptr ) {
    m_deallocFn( ptr );
}
