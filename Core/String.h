#ifndef STRING_H
#define STRING_H

#include "Core/StdTypes.h"
#include "Core/Iterator.h"

class String {
public:
    // constructors
    String();
    String( char const *s );

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

    char* c_str();
    char const* c_str() const;

    char* data();
    char const* data() const;

    // iterators
    typedef Iterator<char> iterator;
    typedef Iterator<char const> const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    enum { kSize = 512 };
    char m_string[kSize];
};

#endif // STRING_H