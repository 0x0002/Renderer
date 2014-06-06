#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include "Math/Math.h"
#include "Component/ComponentBase.h"

class Ray;
class CameraSample;
class RayDifferential;

class CameraBase : public ComponentBase {
public:
    static Component::Type const kType;

    CameraBase( GameObject *object, uint32_t id, Component::Type type ) : ComponentBase( object, id, type ) {}
    virtual ~CameraBase() {}

    virtual float GenerateRay( CameraSample const &sample, Ray *ray ) const;
    float GenerateRayDifferential( CameraSample const &sample, RayDifferential *rayDifferential ) const;

protected:
    float m_shutterOpen;
    float m_shutterClose;
};

#endif // CAMERA_BASE_H