#ifndef COMPONENT_TYPE_2_H
#define COMPONENT_TYPE_2_H

#include "Renderer/ComponentType1.h"

class ComponentType2 : public ComponentType1 {
public:
    static Component::Type const kType;

    virtual void Initialize() override {}
    virtual void Update( float dt ) override {}
    virtual void Uninitialize() override {}

private:
    float m_f;
    int m_i;
};

#endif // COMPONENT_TYPE_2_H