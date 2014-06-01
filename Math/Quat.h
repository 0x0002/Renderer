#ifndef QUAT_H
#define QUAT_H

#include "Math/SSE.h"
#include "Math/Trig.h"

class Vec4;
class Scalar;
class Bool;

class Quat {
public:
    // constructors
    Quat();
    Quat( float x, float y, float z, float w );
    Quat( Scalar const &x, Scalar const &y, Scalar const &z, Scalar const &w );
    Quat( Mat44 const &m );

    static Quat Identity();

    // assignment operators
    Quat& operator+=( Quat const &q );
    Quat& operator-=( Quat const &q );
    Quat& operator*=( Quat const &q );
    Quat& operator*=( Scalar const &s );
    Quat& operator/=( Scalar const &s );

    // unary operators
    Quat operator+() const;
    Quat operator-() const;

    // binary operators
    Quat operator+( Quat const &q ) const;
    Quat operator-( Quat const &q ) const;
    Quat operator*( Quat const &q ) const;
    Quat operator*( Scalar const &s ) const;
    Quat operator/( Scalar const &s ) const;

    friend Quat operator*( Scalar const &s, Quat const &q );
    friend Quat operator/( Scalar const &s, Quat const &q );

    // comparison operators
    Bool operator==( Quat const &q ) const;
    Bool operator!=( Quat const &q ) const;

    // accessors
    Scalar X() const;
    Scalar Y() const;
    Scalar Z() const;
    Scalar W() const;
    void XYZW( float xyzw[4] ) const;
    Scalar GetElem( int32_t i ) const;

    void SetX( Scalar const &x );
    void SetY( Scalar const &y );
    void SetZ( Scalar const &z );
    void SetW( Scalar const &w );
    void SetElem( int32_t i, Scalar const &s );

private:
    Quat( __m128 const &q );

private:
    __m128 m_value;

    // friends
    friend class Mat44;
    friend class Vec4;
    friend Scalar Length( Quat const &q );
    friend Scalar Dot( Quat const &a, Quat const &b );
    friend Quat Conjugate( Quat const &q );
    friend Quat Select( Bool const &condition, Quat const &true_, Quat const &false_ );
    friend Quat QuatRotationAxisAngle( Vec4 const &axis, Scalar const &angle );
    friend Quat QuatRotationYawPitchRoll( Scalar const &yaw, Scalar const &pitch, Scalar const &roll );
};

Quat Normalize( Quat const &q );
Scalar Length( Quat const &q );
Scalar RcpLength( Quat const &q );
Scalar LengthSquared( Quat const &q );

Scalar Dot( Quat const &a, Quat const &b );

Quat Conjugate( Quat const &q );
Quat Inverse( Quat const &q );

Quat Slerp( Quat const &a, Quat const &b, Scalar const &t );

// rotation quaternions
Quat QuatRotationAxisAngle( Vec4 const &axis, Scalar const &angle );
Quat QuatRotationYawPitchRoll( Scalar const &yaw, Scalar const &pitch, Scalar const &roll );

#endif // QUAT_H