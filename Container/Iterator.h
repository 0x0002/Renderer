#ifndef ITERATOR_H
#define ITERATOR_H

#include <xutility>

template<typename T>
class Iterator {
public:
    Iterator();
    Iterator( T *value );

    Iterator<T>& operator++();
    Iterator<T>& operator--();
    Iterator<T> operator++( int );
    Iterator<T> operator--( int );

    Iterator operator+( size_t i ) const;
    Iterator operator-( size_t i ) const;

    Iterator& operator+=( size_t i );
    Iterator& operator-=( size_t i );

    bool operator==( Iterator const &it ) const;
    bool operator!=( Iterator const &it ) const;
    bool operator<( Iterator const &it ) const;
    bool operator>( Iterator const &it ) const;
    bool operator<=( Iterator const &it ) const;
    bool operator>=( Iterator const &it ) const;

    T& operator*();
    T& operator[]( size_t i );

    typedef size_t                          difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;

    T* Value() const;

private:
    T *m_value;
};

#include "Iterator.inl"

#endif // ITERATOR_H