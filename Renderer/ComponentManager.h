#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <Container/List.h>
#include <Container/Vector.h>

class ComponentBase;

class ComponentManager {
public:



private:

    // list of arrays of component data. one list per type
    List<ComponentBase*> m_components;

    Vector<Vector<uint8_t*>> m_components;
};

#endif // COMPONENT_MANAGER_H