#include "Game/PerspectiveCamera.h"
#include "Game/CameraSample.h"
#include "Math/Ray.h"

Component::Type const PerspectiveCamera::kType = Component::kCameraBase;

float PerspectiveCamera::GenerateRay( CameraSample const &sample, Ray *ray ) const {
    // unproject points on near and far screen space planes to get view space direction
    Vec4 nearSS( sample.m_imageX, sample.m_imageY, 0.0f, 1.0f );
    Vec4 farSS( sample.m_imageX, sample.m_imageY, 1.0f, 1.0f );

    Vec4 nearVS = nearSS * m_invProjection;
    Vec4 farVS = farSS * m_invProjection;

    nearVS /= nearVS.W();
    farVS /= farVS.W();

    ray->m_origin = Vec4( 0.0f, 0.0f, 0.0f, 0.1f );
    ray->m_direction = Normalize( farVS - nearVS );
    ray->m_time = Lerp( m_shutterOpen, m_shutterClose, sample.m_time );

    // transform ray to world space
    *ray *= Inverse( Tform() );
    ray->m_direction = Normalize( ray->m_direction );
    return 1.0f;
}