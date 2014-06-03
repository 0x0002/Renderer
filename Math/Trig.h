#ifndef TRIG_H
#define TRIG_H

#include "Scalar.h"

#define kPi      ( 3.14159265358979323846f )
#define k2Pi     ( 6.28318530717958647692f )
#define kPiBy2   ( kPi / 2.0f )
#define kPiBy4   ( kPi / 4.0f )
#define kInvPi   ( 1.0f / kPi )
#define kInv2Pi  ( 1.0f / k2Pi )
#define kSqrtTwo ( 1.41421356237309504880f )

#define ToRadian( degree ) ( (degree) * ( kPi / 180.0f ) )
#define ToDegree( radian ) ( (radian) * ( 180.0f / kPi ) )

// &&& lol fix trig functions
#include <cmath>

ForceInline float Sin( float theta ) {
    return sinf( theta );
}

ForceInline float Cos( float theta ) {
    return cosf( theta );
}

ForceInline float Tan( float theta ) {
    return tanf( theta );
}

ForceInline void SinCos( float theta, float *sin, float *cos ) {
    *sin = sinf( theta );
    *cos = cosf( theta );
}

ForceInline float Asin( float s ) {
    return asinf( s );
}

ForceInline float Acos( float s ) {
    return acosf( s );
}

ForceInline float Atan2( float y, float x ) {
    return  atan2f( y, x );
}

#endif // TRIG_H