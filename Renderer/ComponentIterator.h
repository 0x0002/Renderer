#ifndef COMPONENT_ITERATOR_H
#define COMPONENT_ITERATOR_H

#include "Renderer/ComponentTypes.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

#include <xutility>

template<typename T>
class ComponentIterator {
public:
    ComponentIterator( uint8_t *(*m_componentData )[Component::kCount],
                       size_t const (*m_componentCount)[Component::kCount],
                       size_t const (*m_componentSize )[Component::kCount],
                       Vector<Component::Type> * const *m_inheritanceLookup,
                       uint8_t *m_data, 
                       size_t m_stride,
                       size_t m_i,
                       size_t m_count,
                       size_t m_inheritanceIdx );

    ComponentIterator<T>& operator++();
    ComponentIterator<T>& operator--();
    ComponentIterator<T> operator++( int );
    ComponentIterator<T> operator--( int );

    bool operator==( ComponentIterator const &it ) const;
    bool operator!=( ComponentIterator const &it ) const;

    T* operator*();

    typedef size_t                          difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::bidirectional_iterator_tag iterator_category;

private:
    // references to g_componentManager data
    uint8_t                        *(*m_componentData )[Component::kCount];
    size_t                    const (*m_componentCount)[Component::kCount];
    size_t                    const (*m_componentSize )[Component::kCount];
    Vector<Component::Type> * const  *m_inheritanceLookup;
    
    // current position
    uint8_t *m_data;
    size_t   m_stride;
    size_t   m_i;
    size_t   m_count;
    size_t   m_inheritanceIdx;
};

template<typename T>
class ComponentIteratorHelper {
public:
    ComponentIteratorHelper();
    ComponentIteratorHelper( uint8_t *(*componentData )[Component::kCount],
                             size_t const (*componentCount)[Component::kCount],
                             size_t const (*componentSize )[Component::kCount],
                             Vector<Component::Type> * const *inheritanceLookup );

    // iterators
    typedef ComponentIterator<T> iterator;
    //typedef ConstComponentIterator<T> const_iterator; &&&

    iterator begin();
    //const_iterator begin() const;

    iterator end();
    //const_iterator end() const;

private:
    uint8_t                        *(*m_componentData )[Component::kCount];
    size_t                    const (*m_componentCount)[Component::kCount];
    size_t                    const (*m_componentSize )[Component::kCount];
    Vector<Component::Type> * const  *m_inheritanceLookup;
};

#endif // COMPONENT_ITERATOR_H