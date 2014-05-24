#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math/Math.h"

class Transform {
public:
    Transform();

    Transform operator*=( Transform const &t );

    Transform operator*( Transform const &t );
    friend Vec4 operator*( Vec4 const &v );
    friend Vec4 operator*( Normal const &n );

    Mat44 Matrix() const;

private:
    Mat44  m_transform;

    // parent*??
    //Vec4 m_scale;
    //Quat m_rotation;
    //Vec4 m_translation;
};

Transform Inverse( Transform const &t );

#endif // TRANSFORM_H