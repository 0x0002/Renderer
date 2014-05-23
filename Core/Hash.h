#ifndef HASH_H
#define HASH_H

#include "Core/StdTypes.h"

class Hash32 {
public:
    Hash32();
    Hash32( char const *string );
    Hash32( uint8_t const *data, size_t size );

    bool operator==( Hash32 const &h );
    bool operator!=( Hash32 const &h );

    operator uint32_t() const;

private:
    uint32_t m_value;
};

#endif // HASH_H