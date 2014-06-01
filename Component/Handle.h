#ifndef COMPONENT_HANDLE_H
#define COMPONENT_HANDLE_H

#include "Component/ComponentTypes.h"
#include "Component/UntypedHandle.h"

template<typename T>
class Handle {
public:
    Handle();
    Handle( UntypedHandle const &handle );

    bool operator==( Handle const &handle ) const;
    bool operator!=( Handle const &handle ) const;

    T* operator*() const;

private:
    UntypedHandle m_handle;
};

#endif // COMPONENT_HANDLE_H