#include "Core/Memory.h"

#include <utility>

// constructors
template<typename T, typename A>
inline List<T, A>::List( uint16_t size, A &allocator, bool growable ) :
    m_allocator( allocator ),
    m_size( size + 1 ),
    m_list( (Node*)allocator.Allocate( m_size * sizeof( Node ) ) ),
    m_freeIdx( 1 ),
    m_length( 0 ),
    m_growable( growable ) {
    //Assert( m_size <= MaxSize() ); &&&
    Init();
}

template<typename T, typename A>
List<T, A>::List( List<T, A> const &list ) :
    m_allocator( list.m_allocator ),
    m_size( list.m_size + 1 ),
    m_list( (Node*)list.m_allocator.Allocate( m_size * sizeof( Node ) ) ),
    m_freeIdx( list.m_freeIdx ),
    m_length( list.m_length ),
    m_growable( list.m_growable ) {
    uint16_t size = (uint16_t)m_size;
    for( uint16_t i = 0; i < size; ++i )
        new ( &m_list[i].m_value ) T( list.m_list[i].m_value );
}

template<typename T, typename A>
//inline List<T, A>::List( List<T, A> const &&list ) : List() { &&& use delegated constructor
inline List<T, A>::List( List<T, A> &&list ) :
    m_allocator( list.m_allocator ),
    m_size( list.m_size + 1 ),
    m_list( (Node*)list.m_allocator.Allocate( m_size * sizeof( Node ) ) ),
    m_freeIdx( list.m_freeIdx ),
    m_length( list.m_length ),
    m_growable( list.m_growable ) {
    Init();
    Swap( *this, list );
}

template<typename T, typename A>
inline List<T, A>& List<T, A>::operator=( List<T, A> list ) {
    Swap( *this, list );
    return *this;
}

template<typename T, typename A>
inline List<T, A>::~List() {
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
    return m_length;
}

template<typename T, typename A>
inline size_t List<T, A>::MaxSize() const {
    return 0xffff - 1;
}

template<typename T, typename A>
inline size_t List<T, A>::Capacity() const {
    return m_size - 1;
}

template<typename T, typename A>
inline size_t List<T, A>::Empty() const {
        return m_length == 0;
}

// modifiers
template<typename T, typename A>
inline void List<T, A>::Insert( const_iterator const &pos, T const &val ) {
    //Assert( m_length < Capacity() || m_growable ); &&&

    if( m_length == Capacity() && m_growable )
        Grow();

    ++m_length;

    // remove node from free list
    uint16_t nodeIdx = m_freeIdx;
    Node &node = m_list[nodeIdx];
    m_freeIdx = node.m_next;

    // add node to list
    uint16_t nextIdx = pos.Idx();
    Node &nextNode = m_list[nextIdx];

    node.m_next = nextIdx;
    node.m_prev = nextNode.m_prev;
    new ( &node.m_value ) T( val );

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
    //Assert( m_length != 0 ); &&&

    --m_length;

    // remove node from list
    uint16_t nodeIdx = pos.Idx();
    Node &node = m_list[nodeIdx];

    m_list[node.m_next].m_prev = node.m_prev;
    m_list[node.m_prev].m_next = node.m_next;

    // put node back on front free list
    node.m_next = m_freeIdx;
    node.m_value.~T();

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
    std::swap( a.m_size,      b.m_size );
    std::swap( a.m_freeIdx,   b.m_freeIdx );
    std::swap( a.m_growable,  b.m_growable );
    std::swap( a.m_growable,  b.m_growable );
}

template<typename T, typename A>
inline void List<T, A>::Init() {
    // initialize free list of nodes
    uint16_t size = m_size;
    for( uint16_t i = 0; i < size; ++i ) {
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
inline void List<T, A>::Grow( uint16_t n = kGrowSize ) {
    //Assert( m_size + n <= MaxSize() ); &&&

    uint16_t oldSize = m_size;
    uint16_t newSize = oldSize + n;

    Node *newList = (Node*)m_allocator.Allocate( newSize * sizeof( Node ) );

    // copy nodes
    for( uint16_t i = 0; i < oldSize; ++i )
        new ( &newList[i].m_value ) T( m_list[i].m_value );

    // initialize empty nodes
    for( uint16_t i = oldSize; i < newSize; ++i )
        newList[i].m_next = i + 1;
    
    // destroy old nodes
    for( uint16_t i = 0; i < oldSize; ++i )
        m_list[i].m_value.~T();

    m_freeIdx = oldSize;
    m_size = newSize;
    m_list = newList;
    m_allocator.Deallocate( m_list );
}