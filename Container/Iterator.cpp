#include "Container/Iterator.h"

#include "Core/StdTypes.h"

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
T& Iterator<T>::operator[]( size_t i ) {
    return m_value[i];
}

// type definitions
template class Iterator<char>;
template class Iterator<int8_t>;
template class Iterator<int16_t>;
template class Iterator<int32_t>;
template class Iterator<int64_t>;
template class Iterator<uint8_t>;
template class Iterator<uint16_t>;
template class Iterator<uint32_t>;
template class Iterator<uint64_t>;
template class Iterator<float>;
template class Iterator<double>;

template class Iterator<char const>;
template class Iterator<int8_t const>;
template class Iterator<int16_t const>;
template class Iterator<int32_t const>;
template class Iterator<int64_t const>;
template class Iterator<uint8_t const>;
template class Iterator<uint16_t const>;
template class Iterator<uint32_t const>;
template class Iterator<uint64_t const>;
template class Iterator<float const>;
template class Iterator<double const>;