#ifndef SHAPE_BASE_H
#define SHAPE_BASE_H

#include "Math/Math.h"
#include "Component/ComponentBase.h"

class Ray;
class DifferentialGeometry;

class ShapeBase : public ComponentBase {
public:
    static Component::Type const kType;

    ShapeBase( GameObject *object, uint32_t id, Component::Type type ) : ComponentBase( object, id, type ) {}
    virtual ~ShapeBase() {}

    //virtual AABB GetBounds();
    //virtual AABB GetWorldBounds();

    virtual bool Intersect( Ray const &ray, float *tHit, float *epsilon, DifferentialGeometry *geom ) const;
    virtual bool Intersect( Ray const &objSpaceRay, float *tHit ) const;

    virtual void GetShadingGeom( DifferentialGeometry const &intersectGeom, DifferentialGeometry *shadingGeom ) const;
    virtual float GetArea() const;
};

#endif // SHAPE_H