#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "Renderer/ComponentTypes.h"
#include "Renderer/ComponentIterator.h"
#include "Renderer/ComponentMultiTypeIterator.h"
#include "Renderer/UntypedHandle.h"

#include "Container/Vector.h"
#include "Container/List.h"

#include "Core/StdTypes.h"

class ComponentManager {
public:
    void Initialize();
    void Deinitialize();

    template<typename T>
    ComponentMultiTypeIteratorHelper<T> AllComponents(); // returns iterator for components of type T and all types that inherit from T

    template<typename T>
    ComponentIteratorHelper<T> Components(); // returns iterator for only type T components

    List<UntypedHandle>::iterator BeginHandle() const;
    List<UntypedHandle>::iterator Create( Component::Type type );
    List<UntypedHandle>::iterator Destroy( UntypedHandle const &handle );
    //void Destroy( uint16_t 

private:
    uint8_t                 *m_data             [Component::kCount + 1];   // actual component data
    uint64_t                *m_generation       [Component::kCount + 1];   // whenever a component is destroyed, this is incremented. used to invalidate handles
    uint32_t                *m_idToData         [Component::kCount + 1];   // used to look up data using a handle
    uint32_t                *m_availableId      [Component::kCount + 1];   // used to track which ids are available
    uint32_t                 m_availableIdCount [Component::kCount + 1];   // number of available ids for each type
    uint32_t                 m_count            [Component::kCount + 1];   // number in use
    uint32_t                 m_max              [Component::kCount + 1];   // number allocated
    size_t                   m_size             [Component::kCount + 1];   // size of each type (bytes)
    Vector<Component::Type> *m_inheritanceLookup[Component::kCount + 1];   // used to iterate through components

    List<UntypedHandle>     *m_handles; // preallocated pool of handles

    // friends
    //template<typename T> friend class Handle;
};

template<typename T>
inline ComponentMultiTypeIteratorHelper<T> ComponentManager::AllComponents() {
    return ComponentMultiTypeIteratorHelper<T>( &m_data, &m_count, &m_size, m_inheritanceLookup[T::kType] );
}

template<typename T>
inline ComponentMultiTypeIteratorHelper<T> AllComponents() {
    // so i don't need to type as much
    return g_componentManager.AllComponents<T>();
}

template<typename T>
inline ComponentIteratorHelper<T> ComponentManager::Components() {
    return ComponentIteratorHelper<T>( (T*)m_data[T::kType], m_count[T::kType] );
}

template<typename T>
inline ComponentIteratorHelper<T> Components() {
    return g_componentManager.Components<T>();
}

// global instance
extern ComponentManager g_componentManager;

#endif // COMPONENT_MANAGER_H