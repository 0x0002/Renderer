#include "Component/ComponentBase.h"
#include "Component/GameObject.h"

Component::Type const ComponentBase::kType = Component::kComponentBase;

GameObject* ComponentBase::Object() {
    return m_object;
}

UntypedHandle ComponentBase::Handle() const {
    return UntypedHandle( m_id, m_type );
}

Transform& ComponentBase::Tform() {
    return m_object->Tform();
}

Transform const& ComponentBase::Tform() const {
    return m_object->Tform();
}

Vec4& ComponentBase::Scale() {
    return m_object->Scale();
}

Vec4 const& ComponentBase::Scale() const {
    return m_object->Scale();
}

Quat& ComponentBase::Rotation() {
    return m_object->Rotation();
}

Quat const& ComponentBase::Rotation() const {
    return m_object->Rotation();
}

Vec4& ComponentBase::Translation() {
    return m_object->Translation();
}

Vec4 const& ComponentBase::Translation() const {
    return m_object->Translation();
}