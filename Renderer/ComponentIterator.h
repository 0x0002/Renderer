#ifndef COMPONENT_ITERATOR_H
#define COMPONENT_ITERATOR_H

#include "Renderer/ComponentTypes.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

#include <xutility>

template<typename T>
class ComponentIterator {
public:
    ComponentIterator( uint8_t *(&m_componentData )[Component::kCount],
                       size_t const (&m_componentCount)[Component::kCount],
                       size_t const (&m_componentSize )[Component::kCount],
                       Vector<Component::Type> * const &m_inheritanceLookup );

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
    // T::kType to get enum
    uint8_t                        *(&m_componentData )[Component::kCount];
    size_t                    const (&m_componentCount)[Component::kCount];
    size_t                    const (&m_componentSize )[Component::kCount];
    Vector<Component::Type> * const  &m_inheritanceLookup;
    
    uint8_t *m_data;
    size_t   m_stride;
    size_t   m_i;
    size_t   m_count;
    size_t   m_inheritanceIdx;

    uint8_t *m_end;
};

#endif // COMPONENT_ITERATOR_H