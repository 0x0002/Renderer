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
    //Scalar operator*( Mat44 m ) const;

    // comparison operators
    Bool operator==( Scalar const &s ) const;
    Bool operator!=( Scalar const &s ) const;
    Bool operator<( Scalar const &s ) const;
    Bool operator>( Scalar const &s ) const;
    Bool operator<=( Scalar const &s ) const;
    Bool operator>=( Scalar const &s ) const;

    // accessors
    operator float() const;

private:
    Scalar( __m128 const &s );

private:
    __m128 m_value;

    // friends
    friend class Vec4;
    friend class Mat44;
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
};

#endif // SCALAR_H