#ifndef COMPONENT_TYPE_2_H
#define COMPONENT_TYPE_2_H

#include "Game/ComponentType1.h"

#include "Core/Print.h"

class ComponentType2 : public ComponentType1 {
public:
    static Component::Type const kType;

    ComponentType2( GameObject *object, uint32_t id ) : ComponentType1( object, id ) {PrintLine( "ComponentType2::Constructor" );}
    virtual ~ComponentType2() {PrintLine( "ComponentType2::Destructor" );}

    virtual void Initialize() override { PrintLine( "ComponentType2::Initialize" ); }
    virtual void Update( float dt ) override {}
    virtual void Uninitialize() override {}

private:
    float m_f;
    int m_i;
};

#endif // COMPONENT_TYPE_2_H