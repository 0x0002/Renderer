#include "Game/CameraBase.h"
#include "Game/CameraSample.h"
#include "Math/Ray.h"
#include "Geometry/RayDifferential.h"
#include "Core/Assert.h"

Component::Type const CameraBase::kType = Component::kCameraBase;

float CameraBase::GenerateRay( CameraSample const &/*sample*/, Ray * /*ray*/ ) const {
    AssertAlways( "Must override Camera::GenerateRay" );
    return 0.0f;
}

float CameraBase::GenerateRayDifferential( CameraSample const &sample, RayDifferential *rayDifferential ) const {
    float weight = GenerateRay( sample, rayDifferential );

    // just find rays one pixel to the right and one pixel up
    CameraSample sampleX = sample;
    sampleX.m_imageX += 1.0f;
    Ray rayX;
    float weightX = GenerateRay( sampleX, &rayX );
    rayDifferential->m_rxOrigin = rayX.m_origin;
    rayDifferential->m_rxDirection = rayX.m_direction;

    CameraSample sampleY = sample;
    sampleY.m_imageY += 1.0f;
    Ray rayY;
    float weightY = GenerateRay( sampleY, &rayY );
    rayDifferential->m_ryOrigin = rayY.m_origin;
    rayDifferential->m_ryDirection = rayY.m_direction;

    if( weightX == 0.0f || weightY == 0.0f )
        return 0.0f;

    rayDifferential->m_hasDifferentials = true;
    return weight;
}
 
Transform CameraBase::ViewTform() const {
    return Inverse( Tform() );
}

Transform CameraBase::InvViewTform() const {
    return Tform();
}