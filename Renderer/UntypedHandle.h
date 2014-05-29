#ifndef UNTYPED_HANDLE_H
#define UNTYPED_HANDLE_H

#include "Renderer/ComponentTypes.h"

#include "Core/StdTypes.h"

template<typename T>
class Handle;

class UntypedHandle {
public:
    UntypedHandle();
    UntypedHandle( size_t generation, uint32_t id, Component::Type type );

    bool operator==( UntypedHandle const &handle ) const;
    bool operator!=( UntypedHandle const &handle ) const;

protected:
    uint64_t        m_generation;
    uint32_t        m_id;
    Component::Type m_type;

    // friends
    friend class ComponentManager;
    template<typename T> friend class Handle;
};

#endif // UNTYPED_HANDLE_H