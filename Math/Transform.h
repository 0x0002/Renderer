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

    Vec4 Scale() const;
    Quat Rotation() const;
    Vec4 Translation() const;

    void SetScale( Vec4 const &s );
    void SetRotation( Quat const &q );
    void SetTranslation( Vec4 const &t );

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
