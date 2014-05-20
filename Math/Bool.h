#ifndef BOOL_H
#define BOOL_H

#include "Core/StdTypes.h"
#include "Core/Align.h"

#include "Math/SSE.h"

class Bool {
public:
    // constructors
    Bool();
    Bool( bool b );
    Bool( bool x, bool y, bool z, bool w );
    explicit Bool( int32_t i );

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
    friend class Quat;
    friend __m128 Select( Bool const &condition, __m128 const &true_, __m128 const &false_ );
    friend Mat44 RotationQuaternion( Quat const &q );
};

__m128 SelectElem( __m128 const &a, int32_t i ); // returns element i

__m128 Select( Bool const &condition, __m128 const &true_, __m128 const &false_ ); // blends elements of false_ into true_ where c is false
Scalar Select( Bool const &condition, Scalar const &true_, Scalar const &false_ );
Vec4 Select( Bool const &condition, Vec4 const &true_, Vec4 const &false_ );
Quat Select( Bool const &condition, Quat const &true_, Quat const &false_ );

#endif // BOOL_H