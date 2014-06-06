#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Math/Math.h"
#include "Game/CameraBase.h"

class Ray;
class CameraSample;
class RayDifferential;

static size_t sizeX = 1280;
static size_t sizeY = 720;

class PerspectiveCamera : public CameraBase {
public:
    static Component::Type const kType;

    PerspectiveCamera( GameObject *object, uint32_t id, Component::Type type ) : CameraBase( object, id, type ) {
        // &&& move out of constructor
        m_projection = Mat44PerspectiveFov( ToRadian( 60.0f ), (float)sizeX / sizeY, 1.0f, 100.0f );
        m_invProjection = Inverse( m_projection );
    }
    virtual ~PerspectiveCamera() {}

    virtual float GenerateRay( CameraSample const &sample, Ray *ray ) const override;

    Mat44 ProjTForm() const;
    Mat44 InvProjTform() const;

private:
    Mat44 m_projection;
    Mat44 m_invProjection;
};

#endif // PERSPECTIVE_CAMERA_H