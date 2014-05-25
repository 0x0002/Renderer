#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Renderer/ComponentIncludes.h"
#include "Renderer/ComponentTypes.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

class ComponentManager {
public:
    void Initialize();


private:
    uint8_t                 **m_componentData    [Component::kCount];
    size_t                    m_componentSize    [Component::kCount];

    Vector<Component::Type>  *m_derivedTypeLookup[Component::kCount];

    // stuff
};

// global instance
extern ComponentManager g_componentManager;

#endif // COMPONENT_MANAGER_H