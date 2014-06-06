#include "Component/Handle.h"
#include "Component/ComponentManager.h"
#include "Component/ComponentIncludes.h"
#include "Core/Assert.h"

template<typename T>
Handle<T>::Handle() :
    m_handle() {
}

template<typename T>
Handle<T>::Handle( UntypedHandle const &handle ) :
    m_handle( handle.m_generation, handle.m_id, handle.m_type ) {

    // check that this is a valid type
#ifdef _DEBUG
    Assert( handle.m_type != Component::kNone, "Invalid handle." );

    bool validTypeConversion = false;
    for( Component::Type t : *g_componentManager.m_baseToDerived[T::kType] ) {
        if( t == handle.m_type ) {
            validTypeConversion = true;
            break;
        }
    }
    Assert( validTypeConversion, "Cannot convert between component types." );
#endif
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
    if( g_componentManager.m_generation[m_handle.m_type][m_handle.m_id] != m_handle.m_generation )
        return nullptr;

    uint32_t componentIdx = g_componentManager.m_idToData[m_handle.m_type][m_handle.m_id];
    return (T*)( g_componentManager.m_data[m_handle.m_type] + componentIdx * g_componentManager.m_size[m_handle.m_type] );
}

template<typename T>
T* Handle<T>::operator->() const {
    // check the generation to see if this handle is still valid
    if( g_componentManager.m_generation[m_handle.m_type][m_handle.m_id] != m_handle.m_generation )
        return nullptr;

    uint32_t componentIdx = g_componentManager.m_idToData[m_handle.m_type][m_handle.m_id];
    return (T*)( g_componentManager.m_data[m_handle.m_type] + componentIdx * g_componentManager.m_size[m_handle.m_type] );
}

template<typename T>
Handle<T>::operator UntypedHandle() const {
    return m_handle;
}

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) \
    template class Handle<typeName>;

#include "Component/ComponentDeclarations.h"

#undef DeclareComponent