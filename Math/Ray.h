#ifndef RAY_H
#define RAY_H

#include "Math/Math.h"

class Ray {
public:
    Ray();
    Ray( Vec4 const &origin, Vec4 const &direction, Scalar const &start, Scalar const &end = kInfinity, Scalar const &t = 0.0f, int d = 0 );
    Ray( Vec4 const &origin, Vec4 const &direction, Ray const &parent, Scalar const &start, Scalar const &end = kInfinity );

    Ray& operator*=( Transform const &t );
    Ray operator*( Transform const &t ) const;

    Vec4 Point( Scalar const &t ) const;

public:
    Vec4 m_origin;
    Vec4 m_direction;

    mutable Scalar m_mint;  // nearest intersection
    mutable Scalar m_maxt;  // furthest intersection

    Scalar m_time;          // for motion blur
    int    m_depth;         // for terminating recursion
};

#endif // RAY_H