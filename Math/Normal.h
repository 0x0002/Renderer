#ifndef NORMAL_H
#define NORMAL_H

#include "Math/SSE.h"

class Vec4;
class Transform;

class Normal {
public:
    // constructors
    Normal();
    explicit Normal( Vec4 const &v );

    Normal& operator*=( Transform const &t );
    Normal operator*( Transform const &t ) const;

private:
    __m128 m_value;

    // friends
    friend class Vec4;
};

#endif // NORMAL_H