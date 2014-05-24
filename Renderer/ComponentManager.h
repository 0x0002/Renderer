#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <Container/List.h>

class ComponentBase;

class ComponentManager {
public:



private:

    // list of arrays of component data. one list per type
    List<ComponentBase*> m_components;
};

#endif // COMPONENT_MANAGER_H