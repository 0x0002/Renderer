#ifndef BOOL_H
#define BOOL_H

#include "SSE.h"
#include "StdTypes.h"
#include "Align.h"

class Bool {
public:
    // constructors
    Bool();
    Bool( bool b );
    Bool( bool x, bool y, bool z, bool w );
    Bool( int32_t i );

    // unary operators
    Bool operator!();

    // comparison operators
    Bool operator==( Bool const &b ) const;
    Bool operator!=( Bool const &b ) const;

    // accessors
    operator bool() const;

private:
    Bool( __m128 const &b );

private:
    __m128 m_value;

    // friends
    friend class Vec4;
    friend class Scalar;
    friend class Mat44;
    friend __m128 Select( __m128 const &a, __m128 const &b, Bool const &c );
};

__m128 Select( __m128 const &a, int32_t i ); // returns element i
__m128 Select( __m128 const &a, __m128 const &b, Bool const &c ); // blends elements of b into a where c is true

#endif // BOOL_H