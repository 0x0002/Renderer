#include "Renderer/ComponentIterator.h"
#include "Renderer/ComponentIncludes.h"

// const iterator





// iterator
template<typename T>
ComponentIterator<T>::ComponentIterator( uint8_t *(*componentData)[Component::kCount],
                                         size_t const (*componentCount)[Component::kCount],
                                         size_t const (*componentSize )[Component::kCount],
                                         Vector<Component::Type> * const *inheritanceLookup,
                                         uint8_t *data, 
                                         size_t stride,
                                         size_t i,
                                         size_t count,
                                         size_t inheritanceIdx ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ),
    m_data( data ),
    m_stride( stride ),
    m_i( i ),
    m_count( count ),
    m_inheritanceIdx( inheritanceIdx ) {
}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator++() {

    return *this;
}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator--() {

    return *this;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator++( int ) {
    ComponentIterator<T> copy( *this );
    // increment
    return copy;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator--( int ) {
    ComponentIterator<T> copy( *this );
    // decrement
    return copy;
}

template<typename T>
bool ComponentIterator<T>::operator==( ComponentIterator const &it ) const {
    return m_componentData     == it.m_componentData &&
           m_componentCount    == it.m_componentCount &&
           m_componentSize     == it.m_componentSize &&
           m_inheritanceLookup == it.m_inheritanceLookup &&
           m_data              == it.m_data &&
           m_stride            == it.m_stride &&
           m_i                 == it.m_i &&
           m_count             == it.m_count &&
           m_inheritanceIdx    == it.m_inheritanceIdx;
}

template<typename T>
bool ComponentIterator<T>::operator!=( ComponentIterator const &it ) const {
    return !( *this == it );
}

template<typename T>
T* ComponentIterator<T>::operator*() {
    return (T*)( m_data + m_i * m_stride );
}

// helper
template<typename T>
ComponentIteratorHelper<T>::ComponentIteratorHelper() {}

template<typename T>
ComponentIteratorHelper<T>::ComponentIteratorHelper( uint8_t *(*componentData)[Component::kCount],
                                                     size_t const (*componentCount)[Component::kCount],
                                                     size_t const (*componentSize )[Component::kCount],
                                                     Vector<Component::Type> * const *inheritanceLookup ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ) {
}

// iterators
template<typename T>
typename ComponentIteratorHelper<T>::iterator ComponentIteratorHelper<T>::begin() {
    return ComponentIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                 (*m_componentData)[T::kType],
                                 (*m_componentSize)[T::kType],
                                 0,
                                 (*m_componentCount)[T::kType],
                                 0 );
}

//template<typename T>
//typename ComponentIteratorHelper<T>::const_iterator ComponentIteratorHelper<T>::begin() const;

template<typename T>
typename ComponentIteratorHelper<T>::iterator ComponentIteratorHelper<T>::end() {
    return ComponentIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                 (*m_componentData)[(*m_inheritanceLookup)->Back()],
                                 (*m_componentSize)[(*m_inheritanceLookup)->Back()],
                                 (*m_componentCount)[(*m_inheritanceLookup)->Back()],
                                 (*m_componentCount)[(*m_inheritanceLookup)->Back()],
                                 (*m_inheritanceLookup)->Size() - 1 );
}

//template<typename T>
//typename ComponentIteratorHelper<T>::const_iterator ComponentIteratorHelper<T>::end() const;

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class ComponentIterator<typeName>; \
    template class ComponentIteratorHelper<typeName>; 

#include "ComponentDeclarations.h"

#undef DeclareComponent