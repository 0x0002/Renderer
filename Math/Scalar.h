#ifndef SCALAR_H
#define SCALAR_H

#include "Core/Align.h"
#include "Core/Union.h"

#include "Math/SSE.h"
#include "Math/Bool.h"

class Scalar {
public:
    // constructors
    Scalar();
    Scalar( float s );

    static Scalar Zero();

    // assignment operators
    Scalar& operator+=( Scalar const &s );
    Scalar& operator-=( Scalar const &s );
    Scalar& operator*=( Scalar const &s );
    Scalar& operator/=( Scalar const &s );

    // unary operators
    Scalar operator+() const;
    Scalar operator-() const;

    // binary operators
    Scalar operator+( Scalar const &s ) const;
    Scalar operator-( Scalar const &s ) const;
    Scalar operator*( Scalar const &s ) const;
    Scalar operator/( Scalar const &s ) const;
    Scalar operator+( float f ) const;
    Scalar operator-( float f ) const;
    Scalar operator*( float f ) const;
    Scalar operator/( float f ) const;

    // comparison operators
    Bool operator==( Scalar const &s ) const;
    Bool operator!=( Scalar const &s ) const;
    Bool operator<( Scalar const &s ) const;
    Bool operator>( Scalar const &s ) const;
    Bool operator<=( Scalar const &s ) const;
    Bool operator>=( Scalar const &s ) const;
    Bool operator==( float f ) const;
    Bool operator!=( float f ) const;
    Bool operator<( float f ) const;
    Bool operator>( float f ) const;
    Bool operator<=( float f ) const;
    Bool operator>=( float f ) const;

    // accessors
    operator float() const;

private:
    Scalar( __m128 const &s );

private:
    __m128 m_value;

    // friends
    friend class Vec4;
    friend class Mat44;
    friend class Quat;
    friend Vec4 operator*( Scalar const &s, Vec4 const &v );
    friend Vec4 operator/( Scalar const &s, Vec4 const &v );
    friend Vec4 Normalize( Vec4 const &v );
    friend Scalar Length( Vec4 const &v );
    friend Scalar RcpLength( Vec4 const &v );
    friend Scalar Dot( Vec4 const &a, Vec4 const &b );
    friend Scalar Dot3( Vec4 const &a, Vec4 const &b );
    friend Mat44 operator*( Scalar const &s, Mat44 const &m );
    friend Mat44 Inverse( Mat44 const &m, Scalar *determinant );
    friend Mat44 Scaling( Scalar const &sx, Scalar const &sy, Scalar const &sz );
    friend Quat operator*( Scalar const &s, Quat const &q );
    friend Quat operator/( Scalar const &s, Quat const &q );
    friend Scalar Length( Quat const &q );
    friend Scalar RcpLength( Quat const &q );
    friend Scalar Dot( Quat const &a, Quat const &b );
    friend Scalar Select( Bool const &condition, Scalar const &true_, Scalar const &false_ );
    friend Scalar Abs( Scalar const &s );
    friend Scalar Min( Scalar const &a, Scalar const &b );
    friend Scalar Max( Scalar const &a, Scalar const &b );
    friend Quat QuatRotationAxisAngle( Vec4 const &axis, Scalar const &angle );
};

Scalar Abs( Scalar const &s );
Scalar Min( Scalar const &a, Scalar const &b );
Scalar Max( Scalar const &a, Scalar const &b );

#endif // SCALAR_H