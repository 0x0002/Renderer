#ifndef IEEE754_H
#define IEEE754_H

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

#endif // IEEE754_H