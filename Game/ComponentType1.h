#ifndef COMPONENT_TYPE_1_H
#define COMPONENT_TYPE_1_H

#include "Component/ComponentBase.h"

#include "Core/Print.h"

class ComponentType1 : public ComponentBase {
public:
    static Component::Type const kType;

    ComponentType1( GameObject *object, uint32_t id ) : ComponentBase( object, id ) {PrintLine( "ComponentType1::Constructor" );}
    virtual ~ComponentType1() {PrintLine( "ComponentType1::Destructor" );}

    virtual void Initialize() override { PrintLine( "ComponentType1::Initialize" ); }
    virtual void Update( float dt ) override {}
    virtual void Uninitialize() override {}

private:
    float m_f;
    int m_i;
};

#endif // COMPONENT_TYPE_1_H