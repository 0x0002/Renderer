#include "Renderer/ComponentHandle.h"
#include "Renderer/ComponentManager.h"

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
Handle<T>::Handle( size_t generation, uint32_t id ) :
    m_handle( generation, id, T::kType ) {
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

    return nullptr;
}

#if 0
// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class Handle<typeName>;

#include "ComponentDeclarations.h"

#undef DeclareComponent

#endif