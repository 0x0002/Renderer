#ifndef COMPONENT_BASE_H
#define COMPONENT_BASE_H

#include "Component/ComponentTypes.h"
#include "Component/UntypedHandle.h"
#include "Component/GameObject.h"

#include "Core/StdTypes.h"




#include "Core/Print.h"

class ComponentBase {
public:
    static Component::Type const kType;

    ComponentBase( GameObject *object, uint32_t id ) : m_object( object ), m_id( id ), m_type( kType ) {PrintLine( "ComponentBase::Constructor" );}
    virtual ~ComponentBase() { PrintLine( "ComponentBase::Destructor" ); }

    virtual void Initialize() { PrintLine( "ComponentBase::Initialize" ); }
    virtual void Update( float dt ) {}
    virtual void Uninitialize() {}

    // non-virtual
    GameObject* Object();
    UntypedHandle Handle() const;

    Transform& Tform();
    Transform const& Tform() const;

    Vec4& Scale();
    Vec4 const& Scale() const;

    Quat& Rotation();
    Quat const& Rotation() const;

    Vec4& Translation();
    Vec4 const& Translation() const;

private:
    GameObject     *m_object;
    uint32_t        m_id;
    Component::Type m_type;

    friend class ComponentManager;
};

#endif // COMPONENT_BASE_H