#ifndef COMPONENT_HANDLE_H
#define COMPONENT_HANDLE_H

#include "Renderer/ComponentTypes.h"
#include "Renderer/UntypedHandle.h"

#include "Core/StdTypes.h"

template<typename T>
class Handle {
public:
    Handle();
    Handle( UntypedHandle const &handle );
    Handle( size_t generation, uint32_t id );

    bool operator==( Handle const &handle ) const;
    bool operator!=( Handle const &handle ) const;

    T* operator*() const;

private:
    UntypedHandle m_handle;
};

#endif // COMPONENT_HANDLE_H