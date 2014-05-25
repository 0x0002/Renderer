#include "Core/Memory.h"
#include "Core/Assert.h"

#include <utility>

// constructors
template<typename T, typename A>
inline List<T, A>::List( uint16_t capacity, bool growable, A &allocator ) :
    m_allocator( allocator ),
    m_list( (Node*)allocator.Allocate( ( capacity + 1 ) * sizeof( Node ) ) ),
    m_capacity( capacity + 1 ),
    m_freeIdx( 1 ),
    m_size( 0 ),
    m_growable( growable ) {
    Assert( capacity <= MaxSize(), "Cannot create list of %i elements. (Max = %llx)", (int32_t)capacity, MaxSize() );
    Init();
}

template<typename T, typename A>
List<T, A>::List( List<T, A> const &list ) :
    m_allocator( list.m_allocator ),
    m_list( (Node*)list.m_allocator.Allocate( list.m_capacity * sizeof( Node ) ) ),
    m_capacity( list.m_capacity ),
    m_freeIdx( 1 ),
    m_size( 0 ),
    m_growable( list.m_growable ) {
    
    Init();

    for( T const &val : list )
        PushBack( val );
}

template<typename T, typename A>
inline List<T, A>& List<T, A>::operator=( List<T, A> list ) {
    Assert( list.m_allocator == m_allocator, "Cannot assign list created with different allocator" );
    Swap( *this, list );
    return *this;
}

template<typename T, typename A>
inline List<T, A>::~List() {

    while( !Empty() )
        PopBack();

    m_allocator.Deallocate( m_list );
}

// iterators
template<typename T, typename A>
inline typename List<T, A>::iterator List<T, A>::begin() {
    return iterator( m_list, HeadIdx() );
}

template<typename T, typename A>
inline typename List<T, A>::const_iterator List<T, A>::begin() const {
    return const_iterator( m_list, HeadIdx() );
}

template<typename T, typename A>
inline typename List<T, A>::iterator List<T, A>::end() {
    return iterator( m_list, kEndIdx );
}

template<typename T, typename A>
inline typename List<T, A>::const_iterator List<T, A>::end() const {
    return const_iterator( m_list, kEndIdx );
}

// capacity
template<typename T, typename A>
inline size_t List<T, A>::Size() const {
    return m_size;
}

template<typename T, typename A>
inline size_t List<T, A>::MaxSize() const {
    return 0xffff - 1;
}

template<typename T, typename A>
inline size_t List<T, A>::Capacity() const {
    return m_capacity - 1;
}

template<typename T, typename A>
inline size_t List<T, A>::Empty() const {
        return m_size == 0;
}

// modifiers
template<typename T, typename A>
inline void List<T, A>::Insert( const_iterator const &pos, T const &val ) {
    Assert( m_size < Capacity() || m_growable, "Cannot insert into full list. (Capacity = %llx)", Capacity() );

    if( m_size == Capacity() && m_growable )
        Grow();

    ++m_size;

    // remove node from free list
    uint16_t nodeIdx = m_freeIdx;
    Node &node = m_list[nodeIdx];
    m_freeIdx = node.m_next;

    // add node to list
    uint16_t nextIdx = pos.Idx();
    Node &nextNode = m_list[nextIdx];

    Construct( &node.m_value, val );
    node.m_next = nextIdx;
    node.m_prev = nextNode.m_prev;

    m_list[nextNode.m_prev].m_next = nodeIdx;
    nextNode.m_prev = nodeIdx;
}

template<typename T, typename A>
inline void List<T, A>::PushFront( T const &val ) {
    Insert( begin(), val );
}

template<typename T, typename A>
inline void List<T, A>::PushBack( T const &val ) {
    Insert( end(), val );
}

template<typename T, typename A>
inline void List<T, A>::PopFront() {
    Erase( begin() );
}

template<typename T, typename A>
inline void List<T, A>::PopBack() {
    Erase( --end() );
}

template<typename T, typename A>
inline void List<T, A>::Erase( const_iterator const &pos ) {
    Assert( m_size != 0, "Cannot erase from empty list." );

    --m_size;

    // remove node from list
    uint16_t nodeIdx = pos.Idx();
    Node &node = m_list[nodeIdx];
    Destroy( &node.m_value );

    m_list[node.m_next].m_prev = node.m_prev;
    m_list[node.m_prev].m_next = node.m_next;

    // put node back on front free list
    node.m_next = m_freeIdx;
    m_freeIdx = nodeIdx;
}

// accessors
template<typename T, typename A>
inline T& List<T, A>::Front() {
    return m_list[HeadIdx()].m_value;
}

template<typename T, typename A>
inline T const& List<T, A>::Front() const {
    return m_list[HeadIdx()].m_value;
}

template<typename T, typename A>
inline T& List<T, A>::Back() {
    return m_list[TailIdx()].m_value;
}

template<typename T, typename A>
inline T const& List<T, A>::Back() const {
    return m_list[TailIdx()].m_value;
}

// misc
template<typename T, typename A>
inline void Swap( List<T, A> &a, List<T, A> &b ) {
    std::swap( a.m_allocator, b.m_allocator );
    std::swap( a.m_list,      b.m_list );
    std::swap( a.m_capacity,      b.m_capacity );
    std::swap( a.m_freeIdx,   b.m_freeIdx );
    std::swap( a.m_size,    b.m_size );
    std::swap( a.m_growable,  b.m_growable );
}

template<typename T, typename A>
inline void List<T, A>::Init() {
    // initialize free list of nodes
    uint16_t size = m_capacity;
    for( uint16_t i = 1; i < size; ++i ) {
        m_list[i].m_next = i + 1;
    }

    // initialize head/tail node
    m_list[kEndIdx].m_next = kEndIdx;
    m_list[kEndIdx].m_prev = kEndIdx;
}

template<typename T, typename A>
inline uint16_t List<T, A>:: HeadIdx() const {
    return m_list[kEndIdx].m_next;
}

template<typename T, typename A>
inline uint16_t List<T, A>:: TailIdx() const {
    return m_list[kEndIdx].m_prev;
}

template<typename T, typename A>
inline void List<T, A>::Grow( uint16_t n ) {
    Assert( (size_t)( m_capacity + n ) <= MaxSize(), "List cannot exceed maximum size of %llx elements.", MaxSize() );

    uint16_t oldCapacity = m_capacity;
    uint16_t newCapacity = oldCapacity + n;

    size_t newSizeBytes = newCapacity * sizeof( Node );

    Node *oldList = m_list;
    Node *newList = (Node*)m_allocator.Allocate( newSizeBytes );

    newList[kEndIdx].m_next = oldList[kEndIdx].m_next;
    newList[kEndIdx].m_prev = oldList[kEndIdx].m_prev;
    for( uint16_t i = 1; i < oldCapacity; ++i ) {
        Node &n = newList[i];
        Node &o = oldList[i];
        n.m_next = o.m_next;
        n.m_prev = o.m_prev;
        Construct( &n.m_value, o.m_value );
        Destroy( &o.m_value );
    }

    // initialize empty nodes
    for( uint16_t i = oldCapacity; i < newCapacity; ++i )
        newList[i].m_next = i + 1;

    m_freeIdx = oldCapacity;
    m_capacity = newCapacity;
    m_list = newList;
    m_allocator.Deallocate( oldList );
}