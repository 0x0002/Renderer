#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include "ComponentType.h"

#include "Core/StdTypes.h"
#include "Container/FilePath.h"

class GameObject;

class ComponentBase {
public:
    virtual void Initialize() {}
    virtual void Update( float dt ) {}
    virtual void Uninitialize() {}

private:
    GameObject *m_object;
    uint32_t    m_type;
};

#endif // COMPONENT_BASE_H