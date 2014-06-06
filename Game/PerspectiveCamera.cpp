#include "Game/PerspectiveCamera.h"
#include "Game/CameraSample.h"
#include "Math/Ray.h"

Component::Type const PerspectiveCamera::kType = Component::kPerspectiveCamera;

float PerspectiveCamera::GenerateRay( CameraSample const &sample, Ray *ray ) const {
    // unproject points on near and far screen space planes to get view space direction
    float xSS = 2.0f * sample.m_imageX / sizeX - 1.0f;
    float ySS = -2.0f * sample.m_imageY / sizeY + 1.0f;

    Vec4 nearSS( xSS, ySS, 0.0f, 1.0f );
    Vec4 farSS( xSS, ySS, 1.0f, 1.0f );

    Vec4 nearVS = nearSS * m_invProjection;
    Vec4 farVS = farSS * m_invProjection;

    nearVS /= nearVS.W();
    farVS /= farVS.W();

    ray->m_origin = Vec4( 0.0f, 0.0f, 0.0f, 1.0f );
    ray->m_direction = farVS - nearVS;
    ray->m_time = Lerp( m_shutterOpen, m_shutterClose, sample.m_time );

    // transform ray to world space
    *ray *= InvViewTform();
    ray->m_direction = Normalize( ray->m_direction );
    return 1.0f;
}

Mat44 PerspectiveCamera::ProjTForm() const {
    return m_projection;
}

Mat44 PerspectiveCamera::InvProjTform() const {
    return m_invProjection;
}