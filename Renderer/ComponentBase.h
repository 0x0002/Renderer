#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include "Renderer/ComponentTypes.h"
#include "Renderer/UntypedHandle.h"

#include "Core/StdTypes.h"

#include "Container/FilePath.h"

#include "Core/Print.h"

class GameObject;

class ComponentBase {
public:
    static Component::Type const kType;

    ComponentBase( uint32_t id ) : m_object( nullptr ), m_id( id ), m_type( kType ) {PrintLine( "ComponentBase::Constructor" );}
    virtual ~ComponentBase() { PrintLine( "ComponentBase::Destructor" ); }

    virtual void Initialize() { PrintLine( "ComponentBase::Initialize" ); }
    virtual void Update( float dt ) {}
    virtual void Uninitialize() {}


    // non-virtual
    GameObject* Object();
    UntypedHandle Handle() const;

private:
    GameObject     *m_object;
    uint32_t        m_id;
    Component::Type m_type;

    friend class ComponentManager;
};

#endif // COMPONENT_BASE_H