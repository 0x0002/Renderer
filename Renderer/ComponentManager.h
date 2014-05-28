#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Renderer/ComponentIncludes.h"
#include "Renderer/ComponentTypes.h"
#include "Renderer/ComponentIterator.h"

#include "Container/Vector.h"

#include "Core/StdTypes.h"

class ComponentManager {
public:
    void Initialize();
    void Deinitialize();

    template<typename T>
    ComponentIteratorHelper<T> Components();

private:
    uint8_t                 *m_componentData    [Component::kCount];   // actual component data
    size_t                   m_componentCount   [Component::kCount];   // number in use
    size_t                   m_componentMax     [Component::kCount];   // number allocated
    size_t                   m_componentSize    [Component::kCount];   // size of each type (bytes)
    Vector<Component::Type> *m_inheritanceLookup[Component::kCount];   // used to iterate through components
};

template<typename T>
inline ComponentIteratorHelper<T> ComponentManager::Components() {
    return ComponentIteratorHelper<T>( &m_componentData, &m_componentCount, &m_componentSize, &m_inheritanceLookup[T::kType] );
}

// global instance
extern ComponentManager g_componentManager;

#endif // COMPONENT_MANAGER_H