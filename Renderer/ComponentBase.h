#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include "Renderer/ComponentTypes.h"

#include "Core/StdTypes.h"

#include "Container/FilePath.h"

class GameObject;

class ComponentBase {
public:
    static Component::Type const kType;

    virtual void Initialize() {}
    virtual void Update( float dt ) {}
    virtual void Uninitialize() {}

private:
    GameObject *m_object;
    uint32_t    m_type;
};

#endif // COMPONENT_BASE_H