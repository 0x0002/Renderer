#include "Container/String.h"
#include <cstring>

// constructors
String::String() {
    m_string[0] = '\0';
}

String::String( char const *s ) {
    strcpy_s( m_string, s );
}

// iterators
String::iterator String::begin() {
    return m_string;
}

String::const_iterator String::begin() const {
    return m_string;
}

String::iterator String::end() {
    return m_string + Length();
}

String::const_iterator String::end() const {
    return m_string + Length();
}

// capacity
size_t String::Length() const {
    return strlen( m_string );
}

size_t String::MaxLength() const {
    return kSize - 1;
}

bool String::Empty() const {
    return m_string[0] == '\0';
}

// modifiers
String String::operator+( String const &s ) {
    String copy( *this );
    strcat_s( copy.m_string, s.m_string );
    return copy;
}

String& String::operator+=( String const &s ) {
    *this = *this + s;
    return *this;
}

// accessors
char& String::operator[]( size_t i ) {
    return m_string[i];
}

char const& String::operator[]( size_t i ) const {
    return m_string[i];
}

String::operator char*() {
    return m_string;
}

String::operator char const*() const {
    return m_string;
}

char* String::Data() {
    return m_string;
}

char const* String::Data() const {
    return m_string;
}

size_t String::DataSize() const {
    return kSize;
}