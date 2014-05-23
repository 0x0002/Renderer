#include "Core/Memory.h"

#include <utility>

// constructors
template<typename T, typename A>
inline List<T, A>::List( uint16_t size, A &allocator, bool growable ) :
    m_allocator( allocator ),
    m_size( size ),
    m_list( (Node*)allocator.Allocate( size * sizeof( Node ) ) ),
    m_headIdx( Node::kNullIdx ),
    m_tailIdx( Node::kNullIdx ),
    m_freeIdx( 0 ),
    m_length( 0 ),
    m_growable( growable ) {
    //Assert( size <= MaxSize() ); &&&
    Init();
}

template<typename T, typename A>
List<T, A>::List( List<T, A> const &list ) :
    m_allocator( list.m_allocator ),
    m_size( list.m_size ),
    m_list( (Node*)list.m_allocator.Allocate( list.m_size * sizeof( Node ) ) ),
    m_headIdx( list.m_headIdx ),
    m_tailIdx( list.m_tailIdx ),
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
    m_size( list.m_size ),
    m_list( (Node*)list.m_allocator.Allocate( list.m_size * sizeof( Node ) ) ),
    m_headIdx( list.m_headIdx ),
    m_tailIdx( list.m_tailIdx ),
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
    return iterator( m_list, m_headIdx );
}

template<typename T, typename A>
inline typename List<T, A>::const_iterator List<T, A>::begin() const {
    return const_iterator( m_list, m_headIdx );
}

template<typename T, typename A>
inline typename List<T, A>::iterator List<T, A>::end() {
    return iterator( m_list, Node::kNullIdx );
}

template<typename T, typename A>
inline typename List<T, A>::const_iterator List<T, A>::end() const {
    return const_iterator( m_list, Node::kNullIdx );
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
inline size_t List<T, A>::Empty() const {
        return m_length == 0;
}

// modifiers
template<typename T, typename A>
inline void List<T, A>::Insert( const_iterator pos, T const &val ) {
    //Assert( m_length < m_size || m_growable ); &&&

    if( m_length == m_size && m_growable )
        Grow();

    ++m_length;

    // remove node from free list
    uint16_t nodeIdx = m_freeIdx;
    Node &node = m_list[nodeIdx];
    m_freeIdx = node.m_next;

    // add node to list
    uint16_t nextIdx = pos.Idx();

    if( nextIdx == Node::kNullIdx ) {
        PushBack( val );
    }
    else if( nextIdx == m_headIdx ) {
        PushFront( val );
    }
    else {
        Node &nextNode = m_list[nextIdx];

        node.m_next = nextIdx;
        node.m_prev = nextNode.m_prev;
        new ( &node.m_value ) T( val );

        m_list[nextNode.m_prev].m_next = nodeIdx;
        nextNode.m_prev = nodeIdx;
    }
}

template<typename T, typename A>
inline void List<T, A>::PushFront( T const &val ) {
    //Assert( m_length < m_size || m_growable ); &&&

    if( m_length == m_size && m_growable )
        Grow();

    ++m_length;

    // remove node from free list
    uint16_t nodeIdx = m_freeIdx;
    Node &node = m_list[nodeIdx];
    m_freeIdx = node.m_next;
    
    // add node to list
    node.m_next = m_headIdx;
    node.m_prev = Node::kNullIdx;
    new ( &node.m_value ) T( val );

    if( m_headIdx != Node::kNullIdx )
        m_list[m_headIdx].m_prev = nodeIdx;

    m_headIdx = nodeIdx;

    if( m_tailIdx == Node::kNullIdx )
        m_tailIdx = nodeIdx;
}

template<typename T, typename A>
inline void List<T, A>::PushBack( T const &val ) {
    //Assert( m_length < m_size || m_growable ); &&&

    if( m_length == m_size && m_growable )
        Grow();

    ++m_length;

    // remove node from free list
    uint16_t nodeIdx = m_freeIdx;
    Node &node = m_list[nodeIdx];
    m_freeIdx = node.m_next;

    // add node to list
    node.m_next = Node::kNullIdx;
    node.m_prev = m_tailIdx;
    new ( &node.m_value ) T( val );

    if( m_tailIdx != Node::kNullIdx )
        m_list[m_tailIdx].m_next = nodeIdx;

    m_tailIdx = nodeIdx;

    if( m_headIdx == Node::kNullIdx )
        m_headIdx = nodeIdx;
}

template<typename T, typename A>
inline void List<T, A>::PopFront() {
    //Assert( m_length != 0 ); &&&

    --m_length;

    // remove node from list
    uint16_t nodeIdx = m_headIdx;
    Node &node = m_list[nodeIdx];

    m_headIdx = node.m_next;

    if( m_headIdx != Node::kNullIdx )
        m_list[m_headIdx].m_prev = Node::kNullIdx;

    if( m_tailIdx == nodeIdx )
        m_tailIdx = Node::kNullIdx;

    // put node back on front free list
    node.m_next = m_freeIdx;
    node.m_prev = Node::kNullIdx;
    node.m_value.~T();
    
    if( m_freeIdx != Node::kNullIdx )
        m_list[m_freeIdx].m_prev = nodeIdx;

    m_freeIdx = nodeIdx;
}

template<typename T, typename A>
inline void List<T, A>::PopBack() {
    //Assert( m_length != 0 ); &&&

    --m_length;

    // remove node from list
    uint16_t nodeIdx = m_tailIdx;
    Node &node = m_list[nodeIdx];

    m_tailIdx = node.m_prev;

    if( m_tailIdx != Node::kNullIdx )
        m_list[m_tailIdx].m_next = Node::kNullIdx;

    if( m_headIdx == nodeIdx )
        m_headIdx = Node::kNullIdx;

    // put node back on front free list
    node.m_next = m_freeIdx;
    node.m_prev = Node::kNullIdx;
    node.m_value.~T();

    if( m_freeIdx != Node::kNullIdx )
        m_list[m_freeIdx].m_prev = nodeIdx;

    m_freeIdx = nodeIdx;
}

// accessors
template<typename T, typename A>
inline T& List<T, A>::Front() {
    return m_list[m_headIdx].m_value;
}

template<typename T, typename A>
inline T const& List<T, A>::Front() const {
    return m_list[m_headIdx].m_value;
}

template<typename T, typename A>
inline T& List<T, A>::Back() {
    return m_list[m_tailIdx].m_value;
}

template<typename T, typename A>
inline T const& List<T, A>::Back() const {
    return m_list[m_tailIdx].m_value;
}

// misc
template<typename T, typename A>
inline void Swap( List<T, A> &a, List<T, A> &b ) {
    std::swap( a.m_allocator,  b.m_allocator );
    std::swap( a.m_size,       b.m_size );
    std::swap( a.m_list,       b.m_list );
    std::swap( a.m_headIdx,    b.m_headIdx );
    std::swap( a.m_tailIdx,    b.m_tailIdx );
    std::swap( a.m_freeIdx,    b.m_freeIdx );
    std::swap( a.m_growable,   b.m_growable );
}

template<typename T, typename A>
inline void List<T, A>::Init() {
    // initialize free list of nodes
    uint16_t size = (uint16_t)m_size;
    for( uint16_t i = 0; i < size; ++i ) {
        m_list[i].m_next = i + 1;
        m_list[i].m_prev = i - 1;
    }
    m_list[size - 1].m_next = Node::kNullIdx;
    m_list[0].m_prev = Node::kNullIdx;
}

template<typename T, typename A>
inline void List<T, A>::Grow( uint16_t n = kGrowSize ) {
    //Assert( m_size + n <= MaxSize() ); &&&

    uint16_t oldSize = (uint16_t)m_size;
    uint16_t newSize = oldSize + n;

    Node *newList = (Node*)m_allocator.Allocate( newSize * sizeof( Node ) );

    // copy nodes
    for( uint16_t i = 0; i < oldSize; ++i )
        new ( &newList[i].m_value ) T( m_list[i].m_value );

    // initialize empty nodes
    for( uint16_t i = oldSize; i < newSize; ++i ) {
        newList[i].m_next = i + 1;
        newList[i].m_prev = i - 1;
    }
    newList[newSize - 1].m_next = Node::kNullIdx;
    newList[oldSize].m_prev = Node::kNullIdx;
    
    // destroy old nodes
    for( uint16_t i = 0; i < oldSize; ++i )
        m_list[i].m_value.~T();

    m_freeIdx = oldSize;
    m_size = newSize;
    m_list = newList;
    m_allocator.Deallocate( m_list );
}