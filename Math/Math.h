#ifndef MATH_H
#define MATH_H

#include "Math/Vec4.h"
#include "Math/Mat44.h"
#include "Math/Scalar.h"
#include "Math/Bool.h"
#include "Math/Normal.h"
#include "Math/Quat.h"

#define kEpsilon Scalar( 0.00001f )

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

#include "Math/Trig.h"

#endif // MATH_H