#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Math/Vec4.h"
#include "Math/Quat.h"
#include "Math/Mat44.h"

class Transform {
public:
    // constructors
    Transform();
    Transform( Vec4 const &scale, Quat const &rotation, Vec4 const &translation );

    // binary operators
    Transform operator*=( Transform const &t );
    Transform operator*( Transform const &t ) const;

    // accessors
    operator Mat44() const;

    Vec4& Scale();
    Vec4 const& Scale() const;

    Quat& Rotation();
    Quat const& Rotation() const;
    
    Vec4& Translation();
    Vec4 const& Translation() const;

private:
    Vec4 m_scale;
    Quat m_rotation;
    Vec4 m_translation;

    // friends
    friend class Vec4;
    friend class Normal;
    friend Transform Inverse( Transform const &t );
};

Transform Inverse( Transform const &t );

#endif // TRANSFORM_H
