
#include "Core/Memory.h"
#include "Core/Assert.h"

#include <limits>
#include <utility>

// constructors
template<typename T, typename A>
inline Vector<T, A>::Vector( size_t capacity, bool growable, A &allocator ) :
    m_allocator( allocator ),
    m_data( (T*)m_allocator.Allocate( capacity * sizeof( T ) ) ), 
    m_capacity( capacity ),
    m_size( 0 ),
    m_growable( growable ) {
}

template<typename T, typename A>
inline Vector<T, A>::Vector( Vector<T, A> const &vec ) :
    m_allocator( vec.m_allocator ),
    m_data( (T*)m_allocator.Allocate( vec.m_capacity * sizeof( T ) ) ), 
    m_capacity( vec.m_size ),
    m_size( vec.m_size ),
    m_growable( vec.m_growable ) {
    size_t sizeBytes = m_capacity * sizeof( T );
    Memcpy( m_data, sizeBytes, vec.m_data, sizeBytes );
}

template<typename T, typename A>
inline Vector<T, A>& Vector<T, A>::operator=( Vector<T, A> vec ) {
    Swap( *this, vec );
    return *this;
}

template<typename T, typename A>
inline Vector<T, A>::~Vector() {
    m_allocator.Deallocate( m_data );
}

// iterators
template<typename T, typename A>
inline typename Vector<T, A>::iterator Vector<T, A>::begin() {
    return m_data;
}

template<typename T, typename A>
inline typename Vector<T, A>::const_iterator Vector<T, A>::begin() const {
    return m_data;
}

template<typename T, typename A>
inline typename Vector<T, A>::iterator Vector<T, A>::end() {
    return m_data + m_size;
}

template<typename T, typename A>
inline typename Vector<T, A>::const_iterator Vector<T, A>::end() const {
    return m_data + m_size;
}

// capacity
template<typename T, typename A>
inline size_t Vector<T, A>::Size() const {
    return m_size;
}

template<typename T, typename A>
inline size_t Vector<T, A>::MaxSize() const {
    return std::numeric_limits<size_t>::max();
}

template<typename T, typename A>
inline void Vector<T, A>::Resize( size_t size ) {
    Assert( m_capacity >= size || m_growable, "Cannot increase vector capacity to %llx. (Capacity = %llx)", size, m_capacity );

    if( size > m_capacity && m_growable ) {
        Grow( size - m_capacity );
        for( size_t i = m_size; i < size; ++i )
            m_data[i] = T();
    }

    m_size = size;
}

template<typename T, typename A>
inline void Vector<T, A>::Reserve( size_t capacity ) {
    Assert( m_capacity >= capacity || m_growable, "Cannot increase vector capacity to %llx. (Capacity = %llx)", capacity, m_capacity );

    if( capacity > m_capacity && m_growable )
        Grow( capacity - m_capacity );
}

template<typename T, typename A>
inline size_t Vector<T, A>::Capacity() const {
    return m_capacity;
}

template<typename T, typename A>
inline size_t Vector<T, A>::Empty() const {
    return m_size == 0;
}

// modifiers
template<typename T, typename A>
inline void Vector<T, A>::PushBack( T const &val ) {
    Assert( m_size != m_capacity || m_growable, "Cannot insert into full vector." );

    if( m_size == m_capacity && m_growable )
        Grow();

    m_data[m_size] = val;
    ++m_size;
}

template<typename T, typename A>
inline void Vector<T, A>::PopBack() {
    Assert( m_size != 0, "Cannot erase from empty vector." );
    --m_size;
}

template<typename T, typename A>
inline void Vector<T, A>::Erase( const_iterator const &pos ) {
    ptrdiff_t idx = pos.Value() - m_data;

    Assert( idx >= 0 && (size_t)idx < m_size, "Cannot erase from invalid index. (idx = %llx)", idx );

    Memmove( &m_data[idx], ( m_size - idx ) * sizeof( T ), &m_data[idx + 1], ( m_size - idx - 1 ) * sizeof( T ) );
    --m_size;
}

template<typename T, typename A>
inline void Vector<T, A>::Clear() {
    m_size = 0;
}

// accessors
template<typename T, typename A>
inline T& Vector<T, A>::operator[]( size_t i ) {
    Assert( i < m_size, "Cannot access invalid index. (idx = %llx)", i );
    return m_data[i];
}

template<typename T, typename A>
inline T const& Vector<T, A>::operator[]( size_t i ) const {
    Assert( i < m_size, "Cannot access invalid index. (idx = %llx)", i );
    return m_data[i];
}

template<typename T, typename A>
inline T& Vector<T, A>::Front() {
    Assert( m_size != 0, "Cannot access empty vector." );
    return m_data[0];
}

template<typename T, typename A>
inline T const& Vector<T, A>::Front() const {
    Assert( m_size != 0, "Cannot access empty vector." );
    return m_data[0];
}

template<typename T, typename A>
inline T& Vector<T, A>::Back() {
    Assert( m_size != 0, "Cannot access empty vector." );
    return m_data[m_size - 1];
}

template<typename T, typename A>
inline T const& Vector<T, A>::Back() const {
    Assert( m_size != 0, "Cannot access empty vector." );
    return m_data[m_size - 1];
}

template<typename T, typename A>
inline uint8_t* Vector<T, A>::Data() {
    return (uint8_t*)m_data;
}

template<typename T, typename A>
inline uint8_t const* Vector<T, A>::Data() const {
    return (uint8_t*)m_data;
}

template<typename T, typename A>
inline size_t Vector<T, A>::DataSize() const {
    return m_capacity * sizeof( T );
}

// misc
template<typename T, typename A>
inline void Swap( Vector<T, A> &a, Vector<T, A> &b ) {
    std::swap( a.m_allocator,           b.m_allocator );
    std::swap( a.m_data,                b.m_data );
    std::swap( a.m_capacity,            b.m_capacity );
    std::swap( a.m_size,                b.m_size );
    std::swap( a.m_growable,            b.m_growable );
}

template<typename T, typename A>
inline void Vector<T, A>::Grow( size_t n ) {
    Assert( m_capacity + n <= MaxSize(), "Vector cannot exceed maximum size of %llx elements.", MaxSize() );

    size_t oldCapacity = m_capacity;
    size_t newCapacity = oldCapacity + n;

    size_t newCapacityBytes = newCapacity * sizeof( T );

    T *oldData = m_data;
    T *newData = (T*)m_allocator.Allocate( newCapacityBytes );

    Memcpy( newData, newCapacityBytes, oldData, m_size * sizeof( T ) );

    m_capacity = newCapacity;
    m_data = newData;
    m_allocator.Deallocate( oldData );
}