#ifndef ITERATOR_H
#define ITERATOR_H

#include <xutility>

template<typename T>
class Iterator;

template<typename T>
class ConstIterator {
public:
    ConstIterator();
    ConstIterator( Iterator<T> const &it );
    ConstIterator( T const *value );

    ConstIterator<T>& operator++();
    ConstIterator<T>& operator--();
    ConstIterator<T> operator++( int );
    ConstIterator<T> operator--( int );

    ConstIterator operator+( size_t i ) const;
    ConstIterator operator-( size_t i ) const;

    ConstIterator& operator+=( size_t i );
    ConstIterator& operator-=( size_t i );

    bool operator==( ConstIterator const &it ) const;
    bool operator!=( ConstIterator const &it ) const;
    bool operator<( ConstIterator const &it ) const;
    bool operator>( ConstIterator const &it ) const;
    bool operator<=( ConstIterator const &it ) const;
    bool operator>=( ConstIterator const &it ) const;

    T const& operator*() const;
    T const& operator[]( size_t i ) const;

    typedef size_t                          difference_type;
    typedef T const                         value_type;
    typedef T const*                        pointer;
    typedef T const&                        reference;
    typedef std::random_access_iterator_tag iterator_category;

    T const* Value() const;

private:
    T const *m_value;
};

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

    T* Value();

private:
    T *m_value;

    friend class ConstIterator<T>;
};

#include "Iterator.inl"

#endif // ITERATOR_H