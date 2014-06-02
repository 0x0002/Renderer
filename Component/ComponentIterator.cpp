#include "Component/ComponentIterator.h"
#include "Component/ComponentIncludes.h"
#include "Container/Iterator.h"
#include "Core/StdTypes.h"
#include "Core/Assert.h"

// const iterator
template<typename T>
ComponentConstIterator<T>::ComponentConstIterator() : m_value( nullptr ) {}

template<typename T>
ComponentConstIterator<T>::ComponentConstIterator( ComponentIterator<T> const &it ) : m_value( it.m_value ) {}

template<typename T>
ComponentConstIterator<T>::ComponentConstIterator( T const *value ) : m_value( value ) {}

template<typename T>
ComponentConstIterator<T>& ComponentConstIterator<T>::operator++() {
    ++m_value;
    return *this;
}

template<typename T>
ComponentConstIterator<T>& ComponentConstIterator<T>::operator--() {
    --m_value;
    return *this;
}

template<typename T>
ComponentConstIterator<T> ComponentConstIterator<T>::operator++( int ) {
    ComponentConstIterator<T> copy = *this;
    ++m_value;
    return copy;
}

template<typename T>
ComponentConstIterator<T> ComponentConstIterator<T>::operator--( int ) {
    ComponentConstIterator<T> copy = *this;
    --m_value;
    return copy;
}

template<typename T>
ComponentConstIterator<T> ComponentConstIterator<T>::operator+( size_t i ) const {
    return m_value + i;
}

template<typename T>
ComponentConstIterator<T> ComponentConstIterator<T>::operator-( size_t i ) const {
    return m_value - i;
}

template<typename T>
ComponentConstIterator<T>& ComponentConstIterator<T>::operator+=( size_t i ) {
    m_value += i;
    return *this;
}

template<typename T>
ComponentConstIterator<T>& ComponentConstIterator<T>::operator-=( size_t i ) {
    m_value -= i;
    return *this;
}

template<typename T>
bool ComponentConstIterator<T>::operator==( ComponentConstIterator<T> const &it ) const {
    return m_value == it.m_value;
}

template<typename T>
bool ComponentConstIterator<T>::operator!=( ComponentConstIterator<T> const &it ) const {
    return m_value != it.m_value;
}

template<typename T>
bool ComponentConstIterator<T>::operator<( ComponentConstIterator<T> const &it ) const {
    return m_value < it.m_value;
}

template<typename T>
bool ComponentConstIterator<T>::operator>( ComponentConstIterator<T> const &it ) const {
    return m_value > it.m_value;
}

template<typename T>
bool ComponentConstIterator<T>::operator<=( ComponentConstIterator<T> const &it ) const {
    return m_value <= it.m_value;
}

template<typename T>
bool ComponentConstIterator<T>::operator>=( ComponentConstIterator<T> const &it ) const {
    return m_value >= it.m_value;
}

template<typename T>
T const* ComponentConstIterator<T>::operator*() const {
    return m_value;
}

template<typename T>
T const* ComponentConstIterator<T>::operator->() const {
    return m_value;
}

template<typename T>
T const* ComponentConstIterator<T>::operator[]( size_t i ) const {
    return m_value + i;
}

// iterator
template<typename T>
ComponentIterator<T>::ComponentIterator() : m_value( nullptr ) {}

template<typename T>
ComponentIterator<T>::ComponentIterator( T *value ) : m_value( value ) {}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator++() {
    ++m_value;
    return *this;
}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator--() {
    --m_value;
    return *this;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator++( int ) {
    ComponentIterator<T> copy = *this;
    ++m_value;
    return copy;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator--( int ) {
    ComponentIterator<T> copy = *this;
    --m_value;
    return copy;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator+( size_t i ) const {
    return m_value + i;
}

template<typename T>
ComponentIterator<T> ComponentIterator<T>::operator-( size_t i ) const {
    return m_value - i;
}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator+=( size_t i ) {
    m_value += i;
    return *this;
}

template<typename T>
ComponentIterator<T>& ComponentIterator<T>::operator-=( size_t i ) {
    m_value -= i;
    return *this;
}

template<typename T>
bool ComponentIterator<T>::operator==( ComponentIterator<T> const &it ) const {
    return m_value == it.m_value;
}

template<typename T>
bool ComponentIterator<T>::operator!=( ComponentIterator<T> const &it ) const {
    return m_value != it.m_value;
}

template<typename T>
bool ComponentIterator<T>::operator<( ComponentIterator<T> const &it ) const {
    return m_value < it.m_value;
}

template<typename T>
bool ComponentIterator<T>::operator>( ComponentIterator<T> const &it ) const {
    return m_value > it.m_value;
}

template<typename T>
bool ComponentIterator<T>::operator<=( ComponentIterator<T> const &it ) const {
    return m_value <= it.m_value;
}

template<typename T>
bool ComponentIterator<T>::operator>=( ComponentIterator<T> const &it ) const {
    return m_value >= it.m_value;
}

template<typename T>
T* ComponentIterator<T>::operator*() {
    return m_value;
}

template<typename T>
T* ComponentIterator<T>::operator->() {
    return m_value;
}

template<typename T>
T* ComponentIterator<T>::operator[]( size_t i ) {
    return m_value + i;
}

// helper
template<typename T>
ComponentIteratorHelper<T>::ComponentIteratorHelper( T *data, size_t count ) :
    m_data( data ),
    m_count( count ) {
}

// iterators
template<typename T>
typename ComponentIteratorHelper<T>::iterator ComponentIteratorHelper<T>::begin() {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return m_data;
}

template<typename T>
typename ComponentIteratorHelper<T>::const_iterator ComponentIteratorHelper<T>::begin() const {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return m_data;
}

template<typename T>
typename ComponentIteratorHelper<T>::iterator ComponentIteratorHelper<T>::end() {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return m_data + m_count;
}

template<typename T>
typename ComponentIteratorHelper<T>::const_iterator ComponentIteratorHelper<T>::end() const {
    Assert( T::kType < Component::kNone, "Invalid component type." );
    return m_data + m_count;
}

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class ComponentIterator<typeName>; \
    template class ComponentConstIterator<typeName>; \
    template class ComponentIteratorHelper<typeName>; 

#include "Component/ComponentDeclarations.h"

#undef DeclareComponent