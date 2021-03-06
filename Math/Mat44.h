#ifndef MAT44_H
#define MAT44_H

#include "Core/StdTypes.h"
#include "Core/Align.h"
#include "Math/SSE.h"

class Scalar;
class Vec4;
class Bool;
class Quat;

class Mat44 {
public:
    // constructors
    Mat44();
    Mat44( float const f[16] );
    Mat44( float _00, float _01, float _02, float _03,
           float _10, float _11, float _12, float _13,
           float _20, float _21, float _22, float _23,
           float _30, float _31, float _32, float _33 );
    Mat44( Vec4 const &r0, Vec4 const &r1, Vec4 const &r2, Vec4 const &r3 );
    Mat44( Quat const &q );

    static Mat44 Identity();
    static Mat44 Zero();

    // assignment operators
    Mat44& operator+=( Mat44 const &m );
    Mat44& operator-=( Mat44 const &m );
    Mat44& operator*=( Mat44 const &m );
    Mat44& operator*=( Scalar const &s );
    Mat44& operator/=( Scalar const &s );

    // unary operators
    Mat44 operator+() const;
    Mat44 operator-() const;

    // binary operators
    Mat44 operator+( Mat44 const &m ) const;
    Mat44 operator-( Mat44 const &m ) const;
    Mat44 operator*( Mat44 const &m ) const;
    Mat44 operator*( Scalar const &s ) const;
    Mat44 operator/( Scalar const &s ) const;

    friend Mat44 operator*( Scalar const &s, Mat44 const &m );

    // comparison operators
    Bool operator==( Mat44 const &m ) const;
    Bool operator!=( Mat44 const &m ) const;

    // accessors
    Vec4 Row0() const;
    Vec4 Row1() const;
    Vec4 Row2() const;
    Vec4 Row3() const;
    Vec4 Row( int32_t i ) const;
    Scalar Elem( int32_t r, int32_t c ) const;

    void SetRow0( Vec4 const &r0 );
    void SetRow1( Vec4 const &r1 );
    void SetRow2( Vec4 const &r2 );
    void SetRow3( Vec4 const &r3 );
    void SetRow( int32_t i, Vec4 const &r );
    void SetElem( int32_t r, int32_t c, Scalar const &s );

private:
    Mat44( __m128 const &r0, __m128 const &r1, __m128 const &r2, __m128 const &r3 );

private:
    __m128 m_r[4];

    // friends
    friend class Vec4;
    friend Mat44 Transpose( Mat44 const &m );
    friend Mat44 Abs( Mat44 const &m );
    friend Mat44 Inverse( Mat44 const &m, float *determinant );
    friend Mat44 Mat44Scaling( float sx, float sy, float sz );
    friend Mat44 Mat44Scaling( Vec4 const &s );
    friend Mat44 RotationQuaternion( Quat const &q );
};

Mat44 Transpose( Mat44 const &m );
Mat44 Abs( Mat44 const &m );
Mat44 Inverse( Mat44 const &m, float *determinant = nullptr );

// transformation matrices
Mat44 Mat44Translation( float tx, float ty, float tz );
Mat44 Mat44Translation( Vec4 const &t );
Mat44 Mat44RotationX( float angle ); // angle is in radians
Mat44 Mat44RotationY( float angle ); // angle is in radians
Mat44 Mat44RotationZ( float angle ); // angle is in radians
Mat44 Mat44RotationYawPitchRoll( float yaw, float pitch, float roll ); // angle is in radians
Mat44 Mat44RotationAxisAngle( Vec4 const &axis, float angle ); // angle is in radians
Mat44 Mat44Scaling( float s );
Mat44 Mat44Scaling( float sx, float sy, float sz );
Mat44 Mat44Scaling( Vec4 const &s );
Mat44 Mat44LookAtRH( Vec4 const &eye, Vec4 const &at, Vec4 const &up );

// projection matrices
Mat44 Mat44OrthographicRH( float width, float height, float zNear, float zFar );
Mat44 Mat44PerspectiveFov( float fov, float aspectRatio, float zNear, float zFar );

#endif // MAT44_H