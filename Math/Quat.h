#ifndef QUAT_H
#define QUAT_H

#include "Math/SSE.h"
#include "Math/Vec4.h"
#include "Math/Scalar.h"
#include "Math/Bool.h"

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
    Quat( __m128 const &v );

private:
    __m128 m_value;
};

Quat Normalize( Quat const &q );
Scalar Length( Quat const &q );
Scalar RcpLength( Quat const &q );
Scalar LengthSquared( Quat const &q );

Quat Conjugate( Quat const &q );
Quat Inverse( Quat const &q );

Quat Slerp( Quat const &a, Quat const &b, Scalar t );

// transformation quaternions
Quat QuaternionRotationAxisAngle( Vec4 const &axis, Scalar angle );
Quat QuaternionRotationYawPitchRoll( Scalar yaw, Scalar pitch, Scalar roll );

#endif // QUAT_H