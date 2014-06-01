#ifndef COMPONENT_ITERATOR_H
#define COMPONENT_ITERATOR_H

#include <xutility>

template<typename T>
class ComponentIterator;

template<typename T>
class ComponentConstIterator {
public:
    ComponentConstIterator();
    ComponentConstIterator( ComponentIterator<T> const &it );
    ComponentConstIterator( T const *value );

    ComponentConstIterator<T>& operator++();
    ComponentConstIterator<T>& operator--();
    ComponentConstIterator<T> operator++( int );
    ComponentConstIterator<T> operator--( int );

    ComponentConstIterator operator+( size_t i ) const;
    ComponentConstIterator operator-( size_t i ) const;

    ComponentConstIterator& operator+=( size_t i );
    ComponentConstIterator& operator-=( size_t i );

    bool operator==( ComponentConstIterator const &it ) const;
    bool operator!=( ComponentConstIterator const &it ) const;
    bool operator<( ComponentConstIterator const &it ) const;
    bool operator>( ComponentConstIterator const &it ) const;
    bool operator<=( ComponentConstIterator const &it ) const;
    bool operator>=( ComponentConstIterator const &it ) const;

    T const* operator*() const;
    T const* operator[]( size_t i ) const;

    typedef size_t                          difference_type;
    typedef T const                         value_type;
    typedef T const*                        pointer;
    typedef T const&                        reference;
    typedef std::random_access_iterator_tag iterator_category;

private:
    T const *m_value;
};

template<typename T>
class ComponentIterator {
public:
    ComponentIterator();
    ComponentIterator( T *value );

    ComponentIterator<T>& operator++();
    ComponentIterator<T>& operator--();
    ComponentIterator<T> operator++( int );
    ComponentIterator<T> operator--( int );

    ComponentIterator operator+( size_t i ) const;
    ComponentIterator operator-( size_t i ) const;

    ComponentIterator& operator+=( size_t i );
    ComponentIterator& operator-=( size_t i );

    bool operator==( ComponentIterator const &it ) const;
    bool operator!=( ComponentIterator const &it ) const;
    bool operator<( ComponentIterator const &it ) const;
    bool operator>( ComponentIterator const &it ) const;
    bool operator<=( ComponentIterator const &it ) const;
    bool operator>=( ComponentIterator const &it ) const;

    T* operator*();
    T* operator[]( size_t i );

    typedef size_t                          difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;

private:
    T *m_value;

    friend class ComponentConstIterator<T>;
};

template<typename T>
class ComponentIteratorHelper {
public:
    ComponentIteratorHelper( T *data, size_t count );

    // iterators
    typedef ComponentIterator<T> iterator;
    typedef ComponentConstIterator<T> const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    T     *m_data;
    size_t m_count;
};

#endif // COMPONENT_ITERATOR_H