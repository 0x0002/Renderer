#include "Container/Iterator.h"

#include "Core/StdTypes.h"

// const iterator
template<typename T>
ConstIterator<T>::ConstIterator() : m_value( nullptr ) {}

template<typename T>
ConstIterator<T>::ConstIterator( Iterator<T> const &it ) : m_value( it.m_value ) {}

template<typename T>
ConstIterator<T>::ConstIterator( T const *value ) : m_value( value ) {}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    ++m_value;
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator--() {
    --m_value;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator++( int ) {
    ConstIterator<T> copy = *this;
    ++m_value;
    return copy;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator--( int ) {
    ConstIterator<T> copy = *this;
    --m_value;
    return copy;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator+( size_t i ) const {
    return m_value + i;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator-( size_t i ) const {
    return m_value - i;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator+=( size_t i ) {
    m_value += i;
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator-=( size_t i ) {
    m_value -= i;
    return *this;
}

template<typename T>
bool ConstIterator<T>::operator==( ConstIterator<T> const &it ) const {
    return m_value == it.m_value;
}

template<typename T>
bool ConstIterator<T>::operator!=( ConstIterator<T> const &it ) const {
    return m_value != it.m_value;
}

template<typename T>
bool ConstIterator<T>::operator<( ConstIterator<T> const &it ) const {
    return m_value < it.m_value;
}

template<typename T>
bool ConstIterator<T>::operator>( ConstIterator<T> const &it ) const {
    return m_value > it.m_value;
}

template<typename T>
bool ConstIterator<T>::operator<=( ConstIterator<T> const &it ) const {
    return m_value <= it.m_value;
}

template<typename T>
bool ConstIterator<T>::operator>=( ConstIterator<T> const &it ) const {
    return m_value >= it.m_value;
}

template<typename T>
T const& ConstIterator<T>::operator*() const {
    return *m_value;
}

template<typename T>
T const* ConstIterator<T>::operator->() const {
    return m_value;
}

template<typename T>
T const& ConstIterator<T>::operator[]( size_t i ) const {
    return m_value[i];
}

template<typename T>
T const* ConstIterator<T>::Value() const {
    return m_value;
}

// iterator
template<typename T>
Iterator<T>::Iterator() : m_value( nullptr ) {}

template<typename T>
Iterator<T>::Iterator( T *value ) : m_value( value ) {}

template<typename T>
Iterator<T>& Iterator<T>::operator++() {
    ++m_value;
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator--() {
    --m_value;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++( int ) {
    Iterator<T> copy = *this;
    ++m_value;
    return copy;
}

template<typename T>
Iterator<T> Iterator<T>::operator--( int ) {
    Iterator<T> copy = *this;
    --m_value;
    return copy;
}

template<typename T>
Iterator<T> Iterator<T>::operator+( size_t i ) const {
    return m_value + i;
}

template<typename T>
Iterator<T> Iterator<T>::operator-( size_t i ) const {
    return m_value - i;
}

template<typename T>
Iterator<T>& Iterator<T>::operator+=( size_t i ) {
    m_value += i;
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator-=( size_t i ) {
    m_value -= i;
    return *this;
}

template<typename T>
bool Iterator<T>::operator==( Iterator<T> const &it ) const {
    return m_value == it.m_value;
}

template<typename T>
bool Iterator<T>::operator!=( Iterator<T> const &it ) const {
    return m_value != it.m_value;
}

template<typename T>
bool Iterator<T>::operator<( Iterator<T> const &it ) const {
    return m_value < it.m_value;
}

template<typename T>
bool Iterator<T>::operator>( Iterator<T> const &it ) const {
    return m_value > it.m_value;
}

template<typename T>
bool Iterator<T>::operator<=( Iterator<T> const &it ) const {
    return m_value <= it.m_value;
}

template<typename T>
bool Iterator<T>::operator>=( Iterator<T> const &it ) const {
    return m_value >= it.m_value;
}

template<typename T>
T& Iterator<T>::operator*() {
    return *m_value;
}

template<typename T>
T* Iterator<T>::operator->() {
    return m_value;
}

template<typename T>
T& Iterator<T>::operator[]( size_t i ) {
    return m_value[i];
}

template<typename T>
T* Iterator<T>::Value() {
    return m_value;
}