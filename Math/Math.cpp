#include "Math/Math.h"

struct IEEE754Float {
    IEEE754Float( float f ) {
        uint32_t u = union_cast<uint32_t>( f );
        m_sign     = ( u & 0x80000000 ) >> 31;
        m_exponent = ( u & 0x7f800000 ) >> 23;
        m_mantissa = ( u & 0x007fffff );
    }

    float Value() const {
        return union_cast<float>( ( m_sign << 31 ) | ( m_exponent << 23 ) | m_mantissa );
    }

    uint32_t m_sign : 1;
    uint32_t m_exponent : 8;
    uint32_t m_mantissa : 23;
};

bool IsNaN( float f ) {
    IEEE754Float ieee( f );
    return ieee.m_exponent == 0xff && ieee.m_mantissa != 0;
}

bool IsInf( float f ) {
    IEEE754Float ieee( f );
    return ieee.m_exponent == 0xff && ieee.m_mantissa == 0;
}

bool IsNonNumber( float f ) {
    IEEE754Float ieee( f );
    return ieee.m_exponent == 0xff;
}

float NaN() {
    IEEE754Float ieee( 0.0f );
    ieee.m_exponent = 0xff;
    ieee.m_mantissa = 1;
    return ieee.Value();
}

float Inf() {
    IEEE754Float ieee( 0.0f );
    ieee.m_exponent = 0xff;
    return ieee.Value();
}

struct IEEE754Double {
    IEEE754Double( double d ) {
        uint64_t u = union_cast<uint64_t>( d );
        m_sign     = ( u & 0x8000000000000000 ) >> 63;
        m_exponent = ( u & 0x7ff0000000000000 ) >> 52;
        m_mantissa = ( u & 0x000fffffffffffff );
    }

    double Value() const {
        return union_cast<double>( ( m_sign << 63 ) | ( m_exponent << 52 ) | m_mantissa );
    }

    uint64_t m_sign : 1;
    uint64_t m_exponent : 11;
    uint64_t m_mantissa : 52;
};

bool IsNaN( double d ) {
    IEEE754Double ieee( d );
    return ieee.m_exponent == 0x7ff && ieee.m_mantissa != 0;
}

bool IsInf( double d ) {
    IEEE754Double ieee( d );
    return ieee.m_exponent == 0x7ff && ieee.m_mantissa == 0;
}

bool IsNonNumber( double d ) {
    IEEE754Double ieee( d );
    return ieee.m_exponent == 0x7ff;
}