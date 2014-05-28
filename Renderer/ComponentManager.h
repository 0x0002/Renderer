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
    ComponentMultiTypeIteratorHelper<T> AllComponents(); // returns iterator for components of type T and all types that inherit from T



private:
    uint8_t                 *m_componentData    [Component::kCount + 1];   // actual component data
    size_t                   m_componentCount   [Component::kCount + 1];   // number in use
    size_t                   m_componentMax     [Component::kCount + 1];   // number allocated
    size_t                   m_componentSize    [Component::kCount + 1];   // size of each type (bytes)
    Vector<Component::Type> *m_inheritanceLookup[Component::kCount + 1];   // used to iterate through components
};

template<typename T>
inline ComponentMultiTypeIteratorHelper<T> ComponentManager::AllComponents() {
    return ComponentMultiTypeIteratorHelper<T>( &m_componentData, &m_componentCount, &m_componentSize, m_inheritanceLookup[T::kType] );
}

// global instance
extern ComponentManager g_componentManager;

#endif // COMPONENT_MANAGER_H