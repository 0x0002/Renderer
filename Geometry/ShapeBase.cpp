#include "Geometry/ShapeBase.h"
#include "Geometry/DifferentialGeometry.h"
#include "Core/Assert.h"

Component::Type const ShapeBase::kType = Component::kShapeBase;

// AABB Shape::GetWorldBounds() {
//
//}

bool ShapeBase::Intersect( Ray const &/*ray*/, float * /*tHit*/, float * /*epsilon*/, DifferentialGeometry * /*geom*/ ) const {
    return false;
}

bool ShapeBase::Intersect( Ray const &/*objSpaceRay*/, float * /*tHit*/ ) const {
    return false;
}

void ShapeBase::GetShadingGeom( DifferentialGeometry const &/*intersectGeom*/, DifferentialGeometry *shadingGeom ) const {
    *shadingGeom = DifferentialGeometry();
}

float ShapeBase::GetArea() const {
    return 0.0f;
}