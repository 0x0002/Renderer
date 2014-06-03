#ifndef RAY_H
#define RAY_H

#include "Math/Math.h"

class Ray {
public:
    Ray();
    Ray( Vec4 const &origin, Vec4 const &direction, float start, float end = kInfinity, float t = 0.0f, int d = 0 );
    Ray( Vec4 const &origin, Vec4 const &direction, Ray const &parent, float start, float end = kInfinity );

    Ray& operator*=( Transform const &t );
    Ray operator*( Transform const &t ) const;

    Vec4 Point( float t ) const;

public:
    Vec4 m_origin;
    Vec4 m_direction;

    mutable float m_mint;  // nearest intersection
    mutable float m_maxt;  // furthest intersection

    float m_time;          // for motion blur
    int   m_depth;         // for terminating recursion
};

#endif // RAY_H