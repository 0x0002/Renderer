#ifndef NORMAL_H
#define NORMAL_H

#include "Math/SSE.h"
#include "Math/Vec4.h"
#include "Math/Scalar.h"

class Normal {
public:
    // constructors
    Normal();
    Normal( Vec4 const &v );

private:
    __m128 m_value;

    // friends
    friend class Vec4;
};

#endif // NORMAL_H