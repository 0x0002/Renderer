#ifndef UNTYPED_HANDLE_H
#define UNTYPED_HANDLE_H

#include "Component/ComponentTypes.h"
#include "Core/StdTypes.h"

template<typename T>
class Handle;

class UntypedHandle {
public:
    UntypedHandle();

    bool operator==( UntypedHandle const &handle ) const;
    bool operator!=( UntypedHandle const &handle ) const;

    Component::Type Type() const;

private:
    UntypedHandle( uint32_t id, Component::Type type );
    UntypedHandle( uint64_t generation, uint32_t id, Component::Type type );

private:
    uint64_t        m_generation;
    uint32_t        m_id;
    Component::Type m_type;

    // friends
    friend class ComponentManager;
    template<typename T> friend class Handle;
    friend class ComponentBase;
};

#endif // UNTYPED_HANDLE_H