#ifndef VEC4_H
#define VEC4_H

#include "Core/StdTypes.h"
#include "Core/Align.h"
#include "Math/SSE.h"

class Mat44;
class Scalar;
class Bool;
class Normal;
class Quat;
class Transform;

class Vec4 {
public:
    // constructors
    Vec4();
    Vec4( float x, float y, float z, float w );
    Vec4( Scalar const &x, Scalar const &y, Scalar const &z, Scalar const &w );
    Vec4( Normal const &n );
    
    static Vec4 Zero();
    static Vec4 ZeroPoint();
    static Vec4 XAxis();
    static Vec4 YAxis();
    static Vec4 ZAxis();
    static Vec4 WAxis();

    // assignment operators
    Vec4& operator+=( Vec4 const &v );
    Vec4& operator-=( Vec4 const &v );
    Vec4& operator*=( Vec4 const &v );
    Vec4& operator*=( Mat44 const &m );
    Vec4& operator*=( Quat const &m );
    Vec4& operator*=( Transform const &t );
    Vec4& operator*=( Scalar const &s );
    Vec4& operator/=( Scalar const &s );

    // unary operators
    Vec4 operator+() const;
    Vec4 operator-() const;

    // binary operators
    Vec4 operator+( Vec4 const &v ) const;
    Vec4 operator-( Vec4 const &v ) const;
    Vec4 operator*( Vec4 const &v ) const;
    Vec4 operator*( Mat44 const &m ) const;
    Vec4 operator*( Quat const &q ) const;
    Vec4 operator*( Transform const &t ) const;
    Vec4 operator*( Scalar const &s ) const;
    Vec4 operator/( Scalar const &s ) const;

    friend Vec4 operator*( Scalar const &s, Vec4 const &v );

    // comparison operators
    Bool operator==( Vec4 const &v ) const;
    Bool operator!=( Vec4 const &v ) const;

    // accessors
    Scalar X() const;
    Scalar Y() const;
    Scalar Z() const;
    Scalar W() const;
    void XYZ( float xyz[3] ) const;
    void XYZW( float xyzw[4] ) const;
    Scalar Elem( int32_t i ) const; 

    void SetX( Scalar const &x );
    void SetY( Scalar const &y );
    void SetZ( Scalar const &z );
    void SetW( Scalar const &w );
    void SetXYZ( Scalar const &x, Scalar const &y, Scalar const &z );
    void SetXYZ( Vec4 const &xyz );
    void SetElem( int32_t i, Scalar const &s );

private:
    Vec4( __m128 const &v );

private:
    __m128 m_value;

    // friends
    friend class Mat44;
    friend class Normal;
    friend class Quat;
    friend Scalar Dot( Vec4 const &a, Vec4 const &b );
    friend Scalar Dot3( Vec4 const &a, Vec4 const &b );
    friend Vec4 Cross( Vec4 const &a, Vec4 const &b );
    friend Mat44 operator*( Scalar const &s, Mat44 const &m );
    friend Mat44 Mat44Scaling( Scalar const &sx, Scalar const &sy, Scalar const &sz );
    friend Mat44 Mat44Scaling( Vec4 const &s );
    friend Vec4 Select( Bool const &condition, Vec4 const &true_, Vec4 const &false_ );
    friend Quat QuatRotationAxisAngle( Vec4 const &axis, Scalar const &angle );
    friend Vec4 Normalize3w0( Vec4 const &v );
};

Vec4 Normalize( Vec4 const &v );
Vec4 Normalize3w0( Vec4 const &v );
Scalar Length( Vec4 const &v );
Scalar RcpLength( Vec4 const &v );
Scalar LengthSquared( Vec4 const &v );
Scalar Dot( Vec4 const &a, Vec4 const &b );
Scalar Dot3( Vec4 const &a, Vec4 const &b );
Vec4 Cross( Vec4 const &a, Vec4 const &b );

#endif // VEC4_H