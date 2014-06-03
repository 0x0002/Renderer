#ifndef SHAPE_H
#define SHAPE_H

#include "Math/Math.h"
#include "Component/ComponentBase.h"

class Ray;
class DifferentialGeometry;

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

    virtual bool Intersect( Ray const &ray, float *tHit, float *epsilon, DifferentialGeometry *geom ) const;
    virtual bool Intersect( Ray const &objSpaceRay, float *tHit ) const;

    virtual void GetShadingGeom( DifferentialGeometry const &intersectGeom, DifferentialGeometry *shadingGeom ) const;
    virtual float GetArea() const;
};

#endif // SHAPE_H