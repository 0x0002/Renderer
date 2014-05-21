#ifndef TRIG_H
#define TRIG_H

#include "Scalar.h"

#define kPi      Scalar( 3.14159265358979323846f )
#define k2Pi     Scalar( 6.28318530717958647692f )
#define kPiBy2   Scalar( 3.14159265358979323846f / 2.0f )
#define kPiBy4   Scalar( 3.14159265358979323846f / 4.0f )
#define kInvPi   Scalar( 1.0f / 3.14159265358979323846f )
#define kInv2Pi  Scalar( 1.0f / 6.28318530717958647692f )
#define kSqrtTwo Scalar( 1.41421356237309504880f )

#define ToRadian( degree ) ( (degree) * Scalar( 3.14159265358979323846f / 180.0f ) )
#define ToDegree( radian ) ( (radian) * Scalar( 180.0f / 3.14159265358979323846f ) )

// &&& lol fix trig functions
#include <math.h>

ForceInline Scalar Sin( Scalar const &theta ) {
    return sinf( theta );
}

ForceInline Scalar Cos( Scalar const &theta ) {
    return cosf( theta );
}

ForceInline Scalar Tan( Scalar const &theta ) {
    return tanf( theta );
}

ForceInline void SinCos( Scalar const &theta, Scalar *sin, Scalar *cos ) {
    *sin = sinf( theta );
    *cos = cosf( theta );
}

ForceInline Scalar Asin( Scalar const &s ) {
    return asinf( s );
}

ForceInline Scalar Acos( Scalar const &s ) {
    return acosf( s );
}

ForceInline Scalar Atan2( Scalar const &y, Scalar const &x ) {
    return  atan2f( y, x );
}

#endif // TRIG_H