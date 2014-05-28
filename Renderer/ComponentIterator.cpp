#include "Renderer/ComponentIterator.h"
#include "Renderer/ComponentIncludes.h"

// const iterator
template<typename T>
ComponentMultiTypeConstIterator<T>::ComponentMultiTypeConstIterator() :
    m_componentData( nullptr ),
    m_componentCount( nullptr ),
    m_componentSize( nullptr ),
    m_inheritanceLookup( nullptr ),
    m_data( nullptr ),
    m_stride( 0 ),
    m_i( 0 ),
    m_count( 0 ),
    m_inheritanceIdx( 0 ),
    m_typeCount( 0 ) {
}

template<typename T>
ComponentMultiTypeConstIterator<T>::ComponentMultiTypeConstIterator( ComponentMultiTypeIterator<T> const &it ) :
    m_componentData( it.m_componentData ),
    m_componentCount( it.m_componentCount ),
    m_componentSize( it.m_componentSize ),
    m_inheritanceLookup( it.m_inheritanceLookup ),
    m_data( it.m_data ),
    m_stride( it.m_stride ),
    m_i( it.m_i ),
    m_count( it.m_count ),
    m_inheritanceIdx( it.m_inheritanceIdx ),
    m_typeCount( it.m_typeCount ) {
}

template<typename T>
ComponentMultiTypeConstIterator<T>::ComponentMultiTypeConstIterator( uint8_t *(*componentData)[Component::kCount + 1],
                                                                     size_t const (*componentCount)[Component::kCount + 1],
                                                                     size_t const (*componentSize)[Component::kCount + 1],
                                                                     Vector<Component::Type> const *inheritanceLookup,
                                                                     uint8_t *data, 
                                                                     size_t stride,
                                                                     size_t i,
                                                                     size_t count,
                                                                     size_t inheritanceIdx,
                                                                     size_t typeCount,
                                                                     bool end ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ),
    m_data( data ),
    m_stride( stride ),
    m_i( i ),
    m_count( count ),
    m_inheritanceIdx( inheritanceIdx ),
    m_typeCount( typeCount ) {

        if( !end && m_count == 0 )
            FindNextType();
}

template<typename T>
ComponentMultiTypeConstIterator<T>& ComponentMultiTypeConstIterator<T>::operator++() {
    ++m_i;

    if( m_i == m_count )
        FindNextType();

    return *this;
}

template<typename T>
ComponentMultiTypeConstIterator<T>& ComponentMultiTypeConstIterator<T>::operator--() {
    --m_i;

    if( m_i == (size_t)(-1) )
        FindPrevType();

    return *this;
}

template<typename T>
ComponentMultiTypeConstIterator<T> ComponentMultiTypeConstIterator<T>::operator++( int ) {
    ComponentMultiTypeConstIterator<T> copy( *this );
    ++(*this);
    return copy;
}

template<typename T>
ComponentMultiTypeConstIterator<T> ComponentMultiTypeConstIterator<T>::operator--( int ) {
    ComponentMultiTypeConstIterator<T> copy( *this );
    --(*this);
    return copy;
}

template<typename T>
bool ComponentMultiTypeConstIterator<T>::operator==( ComponentMultiTypeConstIterator const &it ) const {
    return m_data == it.m_data && m_i == it.m_i;
}

template<typename T>
bool ComponentMultiTypeConstIterator<T>::operator!=( ComponentMultiTypeConstIterator const &it ) const {
    return !( *this == it );
}

template<typename T>
T const* ComponentMultiTypeConstIterator<T>::operator*() const {
    return (T*)( m_data + m_i * m_stride );
}

template<typename T>
inline void ComponentMultiTypeConstIterator<T>::FindNextType() {
    Component::Type type;

    do {
        ++m_inheritanceIdx;
        type = (*m_inheritanceLookup)[m_inheritanceIdx];
        m_count  = (*m_componentCount)[type];
    } while( m_count == 0 );

    m_data   = (*m_componentData)[type];
    m_stride = (*m_componentSize)[type];
    m_i      = 0;
}

template<typename T>
inline void ComponentMultiTypeConstIterator<T>::FindPrevType() {
    Component::Type type;

    do {
        --m_inheritanceIdx;
        type = (*m_inheritanceLookup)[m_inheritanceIdx];
        m_count  = (*m_componentCount)[type];
    } while( m_count == 0 );

    m_data   = (*m_componentData)[type];
    m_stride = (*m_componentSize)[type];
    m_i      = (*m_componentCount)[type] - 1;
}

// iterator
template<typename T>
ComponentMultiTypeIterator<T>::ComponentMultiTypeIterator() :
    m_componentData( nullptr ),
    m_componentCount( nullptr ),
    m_componentSize( nullptr ),
    m_inheritanceLookup( nullptr ),
    m_data( nullptr ),
    m_stride( 0 ),
    m_i( 0 ),
    m_count( 0 ),
    m_inheritanceIdx( 0 ),
    m_typeCount( 0 ) {
}

template<typename T>
ComponentMultiTypeIterator<T>::ComponentMultiTypeIterator( uint8_t *(*componentData)[Component::kCount + 1],
                                                           size_t const (*componentCount)[Component::kCount + 1],
                                                           size_t const (*componentSize)[Component::kCount + 1],
                                                           Vector<Component::Type> const *inheritanceLookup,
                                                           uint8_t *data, 
                                                           size_t stride,
                                                           size_t i,
                                                           size_t count,
                                                           size_t inheritanceIdx,
                                                           size_t typeCount,
                                                           bool end ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ),
    m_data( data ),
    m_stride( stride ),
    m_i( i ),
    m_count( count ),
    m_inheritanceIdx( inheritanceIdx ),
    m_typeCount( typeCount ) {

    if( !end && m_count == 0 )
        FindNextType();
}

template<typename T>
ComponentMultiTypeIterator<T>& ComponentMultiTypeIterator<T>::operator++() {
    ++m_i;

    if( m_i == m_count )
        FindNextType();

    return *this;
}

template<typename T>
ComponentMultiTypeIterator<T>& ComponentMultiTypeIterator<T>::operator--() {
    --m_i;

    if( m_i == (size_t)(-1) )
        FindPrevType();

    return *this;
}

template<typename T>
ComponentMultiTypeIterator<T> ComponentMultiTypeIterator<T>::operator++( int ) {
    ComponentMultiTypeIterator<T> copy( *this );
    ++(*this);
    return copy;
}

template<typename T>
ComponentMultiTypeIterator<T> ComponentMultiTypeIterator<T>::operator--( int ) {
    ComponentMultiTypeIterator<T> copy( *this );
    --(*this);
    return copy;
}

template<typename T>
bool ComponentMultiTypeIterator<T>::operator==( ComponentMultiTypeIterator const &it ) const {
    return m_data == it.m_data && m_i == it.m_i;
}

template<typename T>
bool ComponentMultiTypeIterator<T>::operator!=( ComponentMultiTypeIterator const &it ) const {
    return !( *this == it );
}

template<typename T>
T* ComponentMultiTypeIterator<T>::operator*() {
    return (T*)( m_data + m_i * m_stride );
}

template<typename T>
inline void ComponentMultiTypeIterator<T>::FindNextType() {
    Component::Type type;

    do {
        ++m_inheritanceIdx;
        type = (*m_inheritanceLookup)[m_inheritanceIdx];
        m_count  = (*m_componentCount)[type];
    } while( m_count == 0 );

    m_data   = (*m_componentData)[type];
    m_stride = (*m_componentSize)[type];
    m_i      = 0;
}

template<typename T>
inline void ComponentMultiTypeIterator<T>::FindPrevType() {
    Component::Type type;

    do {
        --m_inheritanceIdx;
        type = (*m_inheritanceLookup)[m_inheritanceIdx];
        m_count  = (*m_componentCount)[type];
    } while( m_count == 0 );

    m_data   = (*m_componentData)[type];
    m_stride = (*m_componentSize)[type];
    m_i      = (*m_componentCount)[type] - 1;
}

// helper
template<typename T>
ComponentMultiTypeIteratorHelper<T>::ComponentMultiTypeIteratorHelper( uint8_t *(*componentData)[Component::kCount + 1],
                                                                       size_t const (*componentCount)[Component::kCount + 1],
                                                                       size_t const (*componentSize)[Component::kCount + 1],
                                                                       Vector<Component::Type> const *inheritanceLookup ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ) {
}

// iterators
template<typename T>
typename ComponentMultiTypeIteratorHelper<T>::iterator ComponentMultiTypeIteratorHelper<T>::begin() {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return ComponentMultiTypeIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                          (*m_componentData)[T::kType],
                                          (*m_componentSize)[T::kType],
                                          0,
                                          (*m_componentCount)[T::kType],
                                          0,
                                          (*m_inheritanceLookup).Size(),
                                          false );
}

template<typename T>
typename ComponentMultiTypeIteratorHelper<T>::const_iterator ComponentMultiTypeIteratorHelper<T>::begin() const {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return ComponentMultiTypeIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                          (*m_componentData)[T::kType],
                                          (*m_componentSize)[T::kType],
                                          0,
                                          (*m_componentCount)[T::kType],
                                          0,
                                          (*m_inheritanceLookup).Size(),
                                          false );
}

template<typename T>
typename ComponentMultiTypeIteratorHelper<T>::iterator ComponentMultiTypeIteratorHelper<T>::end() {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return ComponentMultiTypeIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                          (*m_componentData)[Component::kNone],
                                          (*m_componentSize)[Component::kNone],
                                          0,
                                          (*m_componentCount)[Component::kNone],
                                          0,
                                          (*m_inheritanceLookup).Size(),
                                          true );
}

template<typename T>
typename ComponentMultiTypeIteratorHelper<T>::const_iterator ComponentMultiTypeIteratorHelper<T>::end() const {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return ComponentMultiTypeIterator<T>( m_componentData, m_componentCount, m_componentSize, m_inheritanceLookup,
                                          (*m_componentData)[Component::kNone],
                                          (*m_componentSize)[Component::kNone],
                                          0,
                                          (*m_componentCount)[Component::kNone],
                                          0,
                                          (*m_inheritanceLookup).Size(),
                                          true );
}

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class ComponentMultiTypeIterator<typeName>; \
    template class ComponentMultiTypeConstIterator<typeName>; \
    template class ComponentMultiTypeIteratorHelper<typeName>; 

#include "ComponentDeclarations.h"

#undef DeclareComponent