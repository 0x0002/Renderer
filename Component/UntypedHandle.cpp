#include "Component/UntypedHandle.h"
#include "Component/ComponentManager.h"

UntypedHandle::UntypedHandle() : m_generation( (uint64_t)-1 ), m_id( 0 ), m_type( Component::kNone ) {}

UntypedHandle::UntypedHandle( uint32_t id, Component::Type type ) :
    m_generation( g_componentManager.m_generation[type][id] ),
    m_id( id ),
    m_type( type ) {
}

UntypedHandle::UntypedHandle( uint64_t generation, uint32_t id, Component::Type type ) :
    m_generation( generation ),
    m_id( id ),
    m_type( type ) {
}



bool UntypedHandle::operator==( UntypedHandle const &handle ) const {
    return m_generation == handle.m_generation && m_id == handle.m_id && m_type == handle.m_type;
}

bool UntypedHandle::operator!=( UntypedHandle const &handle ) const {
    return !( *this == handle );
}