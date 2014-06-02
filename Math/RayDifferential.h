#ifndef RAY_DIFFERENTIAL_H
#define RAY_DIFFERENTIAL_H

#include "Math/Ray.h"

class RayDifferential : public Ray {
public:
    RayDifferential();
    RayDifferential( Vec4 const &origin, Vec4 const &direction, Scalar const &start, Scalar const &end = kInfinity, Scalar const &t = 0.0f, int d = 0 );
    RayDifferential( Vec4 const &origin, Vec4 const &direction, Ray const &parent, Scalar const &start, Scalar const &end = kInfinity );
    RayDifferential( Ray const &ray );

    void ScaleDifferentials( Scalar const &s );

public:
    bool m_hasDifferentials;
    Vec4 m_rxOrigin;
    Vec4 m_rxDirection;
    Vec4 m_ryOrigin;
    Vec4 m_ryDirection;
};

#endif // RAY_DIFFERENTIAL_H