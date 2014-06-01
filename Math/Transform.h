#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math/Vec4.h"
#include "Math/Quat.h"
#include "Math/Mat44.h"

class Transform {
public:
    Transform();
    Transform( Vec4 const &scale, Quat const &rotation, Vec4 const &translation );

    Transform operator*=( Transform const &t );
    Transform operator*( Transform const &t ) const;

    operator Mat44() const;

private:
    Vec4 m_scale;
    Quat m_rotation;
    Vec4 m_translation;

    // friends
    friend class Vec4;
    friend class Normal;
    friend Transform Inverse( Transform const &transform );
};

Transform Inverse( Transform const &transform );

#endif // TRANSFORM_H
