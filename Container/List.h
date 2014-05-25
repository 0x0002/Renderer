#ifndef LIST_H
#define LIST_H

#include "Core/StdTypes.h"
#include "Core/HeapAllocator.h"

#include "Container/ListNode.h"
#include "Container/ListIterator.h"

template<typename T, typename A = HeapAllocator>
class List {
private:
    enum {
        kDefaultCapacity = 0,
        kGrowSize = 20
    };

    typedef ListNode<T> Node;

public:
    // constructors
    List( uint16_t capacity = kDefaultCapacity, bool growable = true, A &allocator = g_heapAllocator );
    List( List<T, A> const &list );
    List& operator=( List<T, A> list );
    ~List();

    // iterators
    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;
    
    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // capacity
    size_t Size() const;
    size_t MaxSize() const;
    size_t Capacity() const;
    
    size_t Empty() const;

    // modifiers
    void Insert( const_iterator const &pos, T const &val );
    void PushFront( T const &val );
    void PushBack( T const &val );

    void PopFront();
    void PopBack();
    void Erase( const_iterator const &pos );

    // accessors
    T& Front();
    T const& Front() const;

    T& Back();
    T const& Back() const;

private:
    enum {
        kEndIdx = 0
    };

    void Init();

    uint16_t HeadIdx() const;
    uint16_t TailIdx() const;

    template<typename T, typename A>
    friend void Swap( List<T, A> &a, List<T, A> &b );

    // iterators are invalidated if list grows
    void Grow( uint16_t n = kGrowSize );

private:
    A        &m_allocator;
    Node     *m_list;
    uint16_t  m_capacity;       // number of elements allocated
    uint16_t  m_freeIdx;
    uint16_t  m_size;
    bool      m_growable;
};

#include "List.inl"

#endif // LIST_H