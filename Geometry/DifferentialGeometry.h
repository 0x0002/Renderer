#ifndef DIFFERENTIAL_GEOMETRY_H
#define DIFFERENTIAL_GEOMETRY_H

#include "Math/Vec4.h"
#include "Math/Normal.h"
#include "Math/Scalar.h"
#include "Geometry/Shape.h"
#include "Component/Handle.h"

class DifferentialGeometry {
public:
    DifferentialGeometry();
    DifferentialGeometry( Handle<Shape> const &shape,
                          Vec4 const &p,
                          Vec4 const &dpdu, Vec4 const &dpdv,
                          Normal const &dndu, Normal const &dndv,
                          Scalar const &u, Scalar const &v );

public:
    Handle<Shape> m_shape;
    Vec4   m_p;    // surface position
    Normal m_n;    // normalized surface normal
    Scalar m_u;    // parametric value
    Scalar m_v;    // parametric value
    Vec4   m_dpdu; // partial derivative of surface position
    Vec4   m_dpdv; // partial derivative of surface position
    Normal m_dndu; // partial derivative of surface normal
    Normal m_dndv; // partial derivative of surface normal
};

#endif // DIFFERENTIAL_GEOMETRY_H