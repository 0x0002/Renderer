#ifndef COMPONENT_TYPE_1_H
#define COMPONENT_TYPE_1_H

#include "Renderer/ComponentBase.h"

class ComponentType1 : public ComponentBase {
public:
    static Component::Type const kType;

    virtual void Initialize() override {}
    virtual void Update( float dt ) override {}
    virtual void Uninitialize() override {}

private:
    float m_f;
    int m_i;
};

#endif // COMPONENT_TYPE_1_H