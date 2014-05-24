#ifndef STRING_H
#define STRING_H

#include "Container/Iterator.h"

#include "Core/StdTypes.h"

class String {
public:
    // constructors
    String();
    String( char const *s );

    // iterators
    typedef Iterator<char> iterator;
    typedef Iterator<char const> const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // capacity
    size_t Length() const;
    size_t MaxLength() const;

    bool Empty() const;

    // modifiers
    String operator+( String const &s );
    String& operator+=( String const &s );

    // accessors
    char& operator[]( size_t i );
    char const& operator[]( size_t i ) const;

    operator char*();
    operator char const*() const;

    char* Data();
    char const* Data() const;
    size_t DataSize() const;

private:
    enum { kSize = 512 };
    char m_string[kSize];
};

#endif // STRING_H