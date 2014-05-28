#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Renderer/ComponentIncludes.h"
#include "Renderer/ComponentTypes.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

class ComponentManager {
public:
    void Initialize();
    void Deinitialize();

    template<typename T>
    void Components();

private:
    uint8_t                 *m_componentData    [Component::kCount];   // actual component data
    size_t                   m_componentCount   [Component::kCount];   // number in use
    size_t                   m_componentSize    [Component::kCount];   // size of each type

    Vector<Component::Type> *m_inheritanceLookup[Component::kCount];

    // stuff
};

// global instance
extern ComponentManager g_componentManager;

#endif // COMPONENT_MANAGER_H