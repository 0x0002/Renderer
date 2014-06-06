#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry/ShapeBase.h"

class Sphere : public ShapeBase {
public:
    static Component::Type const kType;

    Sphere( GameObject *object, uint32_t id, Component::Type type ) : ShapeBase( object, id, type ) {}
    virtual ~Sphere() {}

    virtual void Initialize() override {}
    virtual void Update( float /*dt*/ ) override  {}
    virtual void Uninitialize() override {}

    //virtual AABB GetBounds();
    //virtual AABB GetWorldBounds();

    virtual bool Intersect( Ray const &ray, float *tHit, float *epsilon, DifferentialGeometry *geom ) const override;
    virtual bool Intersect( Ray const &objSpaceRay, float *tHit ) const override;

    virtual void GetShadingGeom( DifferentialGeometry const &intersectGeom, DifferentialGeometry *shadingGeom ) const override;
    virtual float GetArea() const override;

private:
    float m_radius;
};

#endif // SPHERE_H