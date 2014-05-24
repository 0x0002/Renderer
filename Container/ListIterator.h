#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "Container/ListNode.h"

#include <xutility>

template<typename T>
class ListIterator;

template<typename T>
class ListConstIterator {
public:
    ListConstIterator();
    ListConstIterator( ListIterator<T> const &it );
    ListConstIterator( ListNode<T> const *list, uint16_t idx );

    ListConstIterator<T>& operator++();
    ListConstIterator<T>& operator--();
    ListConstIterator<T> operator++( int );
    ListConstIterator<T> operator--( int );

    bool operator==( ListConstIterator const &it ) const;
    bool operator!=( ListConstIterator const &it ) const;

    T const& operator*() const;

    typedef size_t                          difference_type;
    typedef T const                         value_type;
    typedef T const*                        pointer;
    typedef T const&                        reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    uint16_t Idx() const;

private:
    ListNode<T> const *m_list;
    uint16_t           m_idx;
};

template<typename T>
class ListIterator {
public:
    ListIterator();
    ListIterator( ListNode<T> *list, uint16_t idx );

    ListIterator<T>& operator++();
    ListIterator<T>& operator--();
    ListIterator<T> operator++( int );
    ListIterator<T> operator--( int );

    bool operator==( ListIterator const &it ) const;
    bool operator!=( ListIterator const &it ) const;

    T& operator*();

    typedef size_t                          difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    uint16_t Idx() const;

private:
    ListNode<T> *m_list;
    uint16_t     m_idx;

    friend class ListConstIterator<T>;
};

#include "ListIterator.inl"

#endif // LIST_ITERATOR_H