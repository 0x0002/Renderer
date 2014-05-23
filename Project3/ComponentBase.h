#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include "ComponentType.h"

class GameObject;

class ComponentBase {
public:
    virtual void Load() {}
    virtual void Initialize() {}
    virtual void Update( float dt ) {}
    virtual void Uninitialize() {}

private:
    GameObject *m_object;
    Component::Type m_type;
};

#endif // COMPONENT_BASE_H