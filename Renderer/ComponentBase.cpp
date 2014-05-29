#include "Renderer/ComponentBase.h"

Component::Type const ComponentBase::kType = Component::kComponentBase;

UntypedHandle ComponentBase::Handle() const {
    return UntypedHandle( m_id, m_type );
}