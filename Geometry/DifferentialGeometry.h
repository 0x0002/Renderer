#ifndef DIFFERENTIAL_GEOMETRY_H
#define DIFFERENTIAL_GEOMETRY_H

#include "Math/Math.h"
#include "Component/Handle.h"
#include "Geometry/ShapeBase.h"

class DifferentialGeometry {
public:
    DifferentialGeometry();
    DifferentialGeometry( Handle<ShapeBase> const &shape,
                          Vec4 const &p,
                          Vec4 const &dpdu, Vec4 const &dpdv,
                          Normal const &dndu, Normal const &dndv,
                          float u, float v );

public:
    Handle<ShapeBase> m_shape;
    Vec4   m_p;    // surface position
    Normal m_n;    // normalized surface normal
    float  m_u;    // parametric value
    float  m_v;    // parametric value
    Vec4   m_dpdu; // partial derivative of surface position
    Vec4   m_dpdv; // partial derivative of surface position
    Normal m_dndu; // partial derivative of surface normal
    Normal m_dndv; // partial derivative of surface normal
};

#endif // DIFFERENTIAL_GEOMETRY_H