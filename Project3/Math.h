#ifndef MATH_H
#define MATH_H

#include "StdTypes.h"
#include "Vec4.h"
#include "Mat44.h"
#include "Scalar.h"
#include "Bool.h"

namespace Math {

    // IEEE754 float
    bool IsNaN( float f );
    bool IsInf( float f );
    bool IsNonNumber( float f );
    float NaN();
    float Inf();

    // IEEE754 double
    bool IsNaN( double d );
    bool IsInf( double d );
    bool IsNonNumber( double d );

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

}

#include "Vec4.inl"
#include "Mat44.inl"
#include "Scalar.inl"
#include "Bool.inl"

#endif // MATH_H