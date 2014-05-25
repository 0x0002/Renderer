#ifndef VECTOR_H
#define VECTOR_H

#include "Core/StdTypes.h"
#include "Core/HeapAllocator.h"

#include "Container/Iterator.h"

template<typename T, typename A = Allocator>
class Vector {
private:
    enum {
        kDefaultCapacity = 0,
        kGrowSize = 20
    };

public:
    // constructors
    Vector( size_t capacity = kDefaultCapacity, bool growable = true, A &allocator = g_heapAllocator );
    Vector( Vector<T, A> const &vec );
    Vector& operator=( Vector<T, A> vec );
    ~Vector();

    // iterators
    typedef Iterator<T> iterator;
    typedef ConstIterator<T> const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // capacity
    size_t Size() const;
    size_t MaxSize() const;

    void Resize( size_t size );
    void Reserve( size_t capacity );
    size_t Capacity() const;

    size_t Empty() const;

    // modifiers
    void PushBack( T const &val );

    void PopBack();
    void Erase( const_iterator const &pos );
    void Clear();

    // accessors
    T& operator[]( size_t i );
    T const& operator[]( size_t i ) const;

    T& Front();
    T const& Front() const;

    T& Back();
    T const& Back() const;

    uint8_t* Data();
    uint8_t const* Data() const;
    size_t DataSize() const;

private:
    template<typename T, typename A>
    friend void Swap( Vector<T, A> &a, Vector<T, A> &b );

    // iterators are invalidated if vector grows
    void Grow( size_t n = kGrowSize );

private:
    Allocator &m_allocator;
    T         *m_data;
    size_t     m_capacity;
    size_t     m_size;
    bool       m_growable;
};

#include "Vector.inl"

#endif // VECTOR_H