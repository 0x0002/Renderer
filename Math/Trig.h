#ifndef TRIG_H
#define TRIG_H

#include "Scalar.h"

#define kPi      3.14159265358979323846f
#define k2Pi     6.28318530717958647692f
#define kPiBy2   ( kPi / 2.0f )
#define kPiBy4   ( kPi / 4.0f )
#define kInvPi   ( 1.0f / kPi )
#define kInv2Pi  ( 1.0f / k2Pi )
#define kSqrtTwo 1.41421356237309504880f

#define ToRadian( degree ) ( (degree) * ( kPi / 180.0f ) )
#define ToDegree( radian ) ( (radian) * ( 180.0f / kPi ) )

// &&& lol fix trig functions
#include <math.h>

ForceInline Scalar Sin( Scalar const &theta ) {
    return sinf( theta );
}

ForceInline float SinF( float theta ) {
    return sinf( theta );
}

ForceInline Scalar Cos( Scalar const &theta ) {
    return cosf( theta );
}

ForceInline float CosF( float theta ) {
    return cosf( theta );
}

ForceInline Scalar Tan( Scalar const &theta ) {
    return tanf( theta );
}

ForceInline float TanF( float theta ) {
    return tanf( theta );
}

ForceInline void SinCos( Scalar const &theta, Scalar *sin, Scalar *cos ) {
    *sin = sinf( theta );
    *cos = cosf( theta );
}

ForceInline void SinCosF( float theta, float *sin, float *cos ) {
    *sin = sinf( theta );
    *cos = cosf( theta );
}

ForceInline Scalar Asin( Scalar const &s ) {
    return asinf( s );
}

ForceInline float AsinF( float f ) {
    return asinf( f );
}

ForceInline Scalar Acos( Scalar const &s ) {
    return acosf( s );
}

ForceInline float AcosF( float f ) {
    return acosf( f );
}

ForceInline Scalar Atan2( Scalar const &y, Scalar const &x ) {
    return  atan2f( y, x );
}

ForceInline float Atan2F( float y, float x ) {
    return atan2f( y, x );
}

#endif // TRIG_H