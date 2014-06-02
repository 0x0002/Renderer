#ifndef SHAPE_H
#define SHAPE_H

#include "Component/ComponentBase.h"
#include "Geometry/DifferentialGeometry.h"

class Ray;
class Scalar;

class Shape : public ComponentBase {
public:
    static Component::Type const kType;

    Shape( GameObject *object, uint32_t id, Component::Type type ) : ComponentBase( object, id, type ) {}
    virtual ~Shape() {}

    virtual void Initialize() {}
    virtual void Update( float /*dt*/ ) {}
    virtual void Uninitialize() {}

    //virtual AABB GetBounds();
    //virtual AABB GetWorldBounds();

    virtual bool Intersect( Ray const &ray, Scalar *tHit, Scalar *epsilon, DifferentialGeometry *geom ) const;
    virtual bool Intersect( Ray const &ray ) const;

    virtual DifferentialGeometry GetShadingGeom( DifferentialGeometry const &intersectGeom );
    virtual Scalar GetArea() const; // surface area
};

#endif // SHAPE_H