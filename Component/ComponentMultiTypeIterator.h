#ifndef COMPONENT_MULTI_TYPE_ITERATOR_H
#define COMPONENT_MULTI_TYPE_ITERATOR_H

#include "Component/ComponentTypes.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

#include <xutility>

template<typename T>
class ComponentMultiTypeIterator;

template<typename T>
class ComponentMultiTypeConstIterator {
public:
    ComponentMultiTypeConstIterator();
    ComponentMultiTypeConstIterator( ComponentMultiTypeIterator<T> const &it );
    ComponentMultiTypeConstIterator( uint8_t *(*m_componentData)[Component::kCount + 1],
                                     uint32_t const (*m_componentCount)[Component::kCount + 1],
                                     size_t const (*m_componentSize)[Component::kCount + 1],
                                     Vector<Component::Type> const *m_inheritanceLookup,
                                     uint8_t *m_data, 
                                     size_t m_stride,
                                     uint32_t m_i,
                                     uint32_t m_count,
                                     uint32_t m_inheritanceIdx,
                                     uint32_t m_typeCount, 
                                     bool end );

    ComponentMultiTypeConstIterator<T>& operator++();
    ComponentMultiTypeConstIterator<T>& operator--();
    ComponentMultiTypeConstIterator<T> operator++( int );
    ComponentMultiTypeConstIterator<T> operator--( int );

    bool operator==( ComponentMultiTypeConstIterator const &it ) const;
    bool operator!=( ComponentMultiTypeConstIterator const &it ) const;

    T const* operator*() const;

    typedef size_t                          difference_type;
    typedef T const                         value_type;
    typedef T const*                        pointer;
    typedef T const&                        reference;
    typedef std::bidirectional_iterator_tag iterator_category;

private:
    void FindNextType();
    void FindPrevType();

private:
    // references to g_componentManager data
    uint8_t                        *(*m_componentData)[Component::kCount + 1];
    uint32_t                 const (*m_componentCount)[Component::kCount + 1];
    size_t                   const (*m_componentSize )[Component::kCount + 1];
    Vector<Component::Type>  const  *m_inheritanceLookup;

    // current position
    uint8_t *m_data;
    size_t   m_stride;
    uint32_t m_i;
    uint32_t m_count;
    uint32_t m_inheritanceIdx;
    uint32_t m_typeCount;
};

template<typename T>
class ComponentMultiTypeIterator {
public:
    ComponentMultiTypeIterator();
    ComponentMultiTypeIterator( uint8_t *(*m_componentData)[Component::kCount + 1],
                                uint32_t const (*m_componentCount)[Component::kCount + 1],
                                size_t const (*m_componentSize)[Component::kCount + 1],
                                Vector<Component::Type> const *m_inheritanceLookup,
                                uint8_t *m_data, 
                                size_t m_stride,
                                uint32_t m_i,
                                uint32_t m_count,
                                uint32_t m_inheritanceIdx,
                                uint32_t m_typeCount, 
                                bool end );

    ComponentMultiTypeIterator<T>& operator++();
    ComponentMultiTypeIterator<T>& operator--();
    ComponentMultiTypeIterator<T> operator++( int );
    ComponentMultiTypeIterator<T> operator--( int );

    bool operator==( ComponentMultiTypeIterator const &it ) const;
    bool operator!=( ComponentMultiTypeIterator const &it ) const;

    T* operator*();

    typedef size_t                          difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::bidirectional_iterator_tag iterator_category;

private:
    void FindNextType();
    void FindPrevType();

private:
    // references to g_componentManager data
    uint8_t                        *(*m_componentData)[Component::kCount + 1];
    uint32_t                 const (*m_componentCount)[Component::kCount + 1];
    size_t                   const (*m_componentSize )[Component::kCount + 1];
    Vector<Component::Type>  const  *m_inheritanceLookup;
    
    // current position
    uint8_t *m_data;
    size_t   m_stride;
    uint32_t m_i;
    uint32_t m_count;
    uint32_t m_inheritanceIdx;
    uint32_t m_typeCount;

    // friends
    friend class ComponentMultiTypeConstIterator<T>;
};

template<typename T>
class ComponentMultiTypeIteratorHelper {
public:
    ComponentMultiTypeIteratorHelper( uint8_t *(*componentData)[Component::kCount + 1],
                             uint32_t const (*componentCount)[Component::kCount + 1],
                             size_t const (*componentSize)[Component::kCount + 1],
                             Vector<Component::Type> const *inheritanceLookup );

    // iterators
    typedef ComponentMultiTypeIterator<T> iterator;
    typedef ComponentMultiTypeConstIterator<T> const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    uint8_t                       *(*m_componentData )[Component::kCount + 1];
    uint32_t                 const (*m_componentCount)[Component::kCount + 1];
    size_t                   const (*m_componentSize )[Component::kCount + 1];
    Vector<Component::Type> const   *m_inheritanceLookup;
};

#endif // COMPONENT_MULTI_TYPE_ITERATOR_H