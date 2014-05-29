#include "Renderer/Handle.h"
#include "Renderer/ComponentManager.h"
#include "Renderer/ComponentIncludes.h"

#include "Core/Assert.h"

template<typename T>
Handle<T>::Handle() :
    m_handle() {
}

template<typename T>
Handle<T>::Handle( UntypedHandle const &handle ) :
    m_handle( handle.m_generation, handle.m_id, T::kType ) {
    Assert( T::kType == handle.m_type, "Cannot convert between component types." );
}

template<typename T>
bool Handle<T>::operator==( Handle const &handle ) const {
    return m_handle == handle.m_handle;
}

template<typename T>
bool Handle<T>::operator!=( Handle const &handle ) const {
    return !( *this == handle );
}

template<typename T>
T* Handle<T>::operator*() const {
    // check the generation to see if this handle is still valid
    if( g_componentManager.m_generation[T::kType][m_handle.m_id] != m_handle.m_generation )
        return nullptr;

    uint32_t componentIdx = g_componentManager.m_idToData[T::kType][m_handle.m_id];
    return (T*)( g_componentManager.m_data[T::kType] + componentIdx * sizeof( T ) );
}

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class Handle<typeName>;

#include "ComponentDeclarations.h"

#undef DeclareComponent