#include "Component/GameObject.h"
#include "Component/ComponentManager.h"

GameObject::GameObject() {}

GameObject::GameObject( List<UntypedHandle>::iterator it ) :
    m_transform(),
    m_componentBegin( it ),
    m_componentEnd( it ) {
}

UntypedHandle GameObject::AddComponent( Component::Type type ) {
    m_componentBegin = g_componentManager.Create( type, this );
    return *m_componentBegin;
}

void GameObject::RemoveComponent( UntypedHandle const &handle ) {
    auto it = std::find( m_componentBegin, m_componentEnd, handle );
    Assert( it != m_componentEnd, "Component not found on this object." );
    
    if( it == m_componentBegin )
        m_componentBegin = g_componentManager.Destroy( it );
    else
        g_componentManager.Destroy( it );
}

Transform& GameObject::Tform() {
    return m_transform;
}

Transform const& GameObject::Tform() const {
    return m_transform;
}

Vec4& GameObject::Scale() {
    return m_transform.Scale();
}

Vec4 const& GameObject::Scale() const {
    return m_transform.Scale();
}

Quat& GameObject::Rotation() {
    return m_transform.Rotation();
}

Quat const& GameObject::Rotation() const {
    return m_transform.Rotation();
}

Vec4& GameObject::Translation() {
    return m_transform.Translation();
}

Vec4 const& GameObject::Translation() const {
    return m_transform.Translation();
}