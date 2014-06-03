#ifndef MATH_H
#define MATH_H

#include "Math/Vec4.h"
#include "Math/Mat44.h"
#include "Math/Scalar.h"
#include "Math/Bool.h"
#include "Math/Normal.h"
#include "Math/Quat.h"
#include "Math/Transform.h"

#define kEpsilon 0.00001f
#define kInfinity 3.402823466e+38f

/*------------------------------------------------------------------------------
float == float comparison within an epsilon

absolute tolerance test
if(fabs(x-y) <= absTol) ...
fails when a and b are large

relative tolerance test
if(fabs(x-y) <= relTol * max(fabs(x), fabs(y)) ...
fails when a and be are small

need to use both absolute and relative comparisons

see http://realtimecollisiondetection.net/blog/?p=89 for more info
------------------------------------------------------------------------------*/
ForceInline Bool AlmostEqual( Scalar const &a, Scalar const &b, Scalar const &absTol = 0.000001f, Scalar const &relTol = 0.01f ) {
    // absolute and relative comparisons are combined into a single comparison
    return Abs( a - b ) <= Max( absTol, relTol * Max( Abs( a ), Abs( b ) ) );
}

#include "Math/Vec4.inl"
#include "Math/Mat44.inl"
#include "Math/Scalar.inl"
#include "Math/Bool.inl"
#include "Math/Normal.inl"
#include "Math/Quat.inl"
#include "Math/Transform.inl"

#include "Math/Trig.h"

ForceInline Bool Quadratic( Scalar const &a, Scalar const &b, Scalar const &c, Scalar *t0, Scalar *t1 ) {
    Scalar discrim = ( b * b ) - ( 4.0f * a * c );
    if( discrim < 0.0f )
        return false;

    Scalar sqrtDiscrim = Sqrt( discrim );

    // -B +- sqrtDiscrim can cause loss of precision so we use alternate form
    Scalar temp0 = -0.5f * ( b - sqrtDiscrim );
    Scalar temp1 = -0.5f * ( b + sqrtDiscrim );
    Scalar q = Select( b < 0.0f, temp0, temp1 );

    Scalar e = q / a;
    Scalar f = c / q;

    *t0 = Min( e, f );
    *t1 = Max( e, f );

    return true;
}

ForceInline float Abs( float f ) {
    return f >= 0.0f ? f : -f;
}

ForceInline float Min( float a, float b ) {
    return a < b ? a : b;
}

ForceInline float Max( float a, float b ) {
    return a > b : a : b;
}

ForceInline float Sqrt( float f ) {
    return sqrtf( f );
}

ForceInline float Clamp( float f, float min, float max ) {
    return Min( max, Max( f, min ) );
}

#endif // MATH_H