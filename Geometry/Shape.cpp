#include "Geometry/Shape.h"
#include "Geometry/DifferentialGeometry.h"
#include "Core/Assert.h"

Component::Type const Shape::kType = Component::kShape;

// AABB Shape::GetWorldBounds() {
//
//}

bool Shape::Intersect( Ray const &/*ray*/, float * /*tHit*/, float * /*epsilon*/, DifferentialGeometry * /*geom*/ ) const {
    return false;
}

bool Shape::Intersect( Ray const &/*objSpaceRay*/, float * /*tHit*/ ) const {
    return false;
}

void Shape::GetShadingGeom( DifferentialGeometry const &/*intersectGeom*/, DifferentialGeometry *shadingGeom ) const {
    *shadingGeom = DifferentialGeometry();
}

float Shape::GetArea() const {
    return 0.0f;
}