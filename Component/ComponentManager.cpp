#include "Component/ComponentManager.h"
#include "Component/ComponentIncludes.h"
#include "Core/Memory.h"
#include "Core/Assert.h"
#include <numeric>

// global instance
ComponentManager g_componentManager;

void ComponentManager::Initialize() {

    // preallocate lookup tables
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        m_baseToDerived[i] = new Vector<Component::Type>( Component::kCount + 1, false, g_permAllocator );
        m_baseToDerived[i]->PushBack( (Component::Type)i );
    }

    // add invalid type to make iterator simpler
    m_data             [Component::kNone] = new uint8_t[1];
    m_generation       [Component::kNone] = new uint64_t[1];
    m_idToData         [Component::kNone] = new uint32_t[1];
    m_availableId      [Component::kNone] = new uint32_t[1];
    m_count            [Component::kNone] = (uint32_t)-1; // important to be non-zero for multitype iterator to work properly
    m_max              [Component::kNone] = 0;
    m_size             [Component::kNone] = 0;
    m_baseToDerived[Component::kNone] = new Vector<Component::Type>( Component::kCount + 1, false, g_permAllocator );
    m_baseToDerived[Component::kNone]->PushBack( Component::kNone );

    // preallocate all component data
    for( int32_t i = 0; i < Component::kCount; ++i ) {

        #define DeclareComponent( typeName, baseTypeName, max ) \
        case Component::k##typeName: {                                         \
            m_data              [i] = new uint8_t[max * sizeof( typeName )];   \
            m_generation        [i] = new uint64_t[max];                       \
            m_idToData          [i] = new uint32_t[max];                       \
            m_availableId       [i] = new uint32_t[max];                       \
            Memset( m_generation[i], 0, max * sizeof( uint64_t ) );            \
            for( uint32_t j = 0; j < max; ++j )                                \
                m_availableId[i][j] = j;                                       \
            m_count[i] = 0;                                                    \
            m_max[i] = max;                                                    \
            m_size[i] = sizeof( typeName );                                    \
            m_baseToDerived[Component::k##baseTypeName]->PushBack( Component::k##typeName ); \
            break; \
        }

        switch( i ) {
        #include "Component/ComponentDeclarations.h"
        default: AssertAlways( "Invalid component type." ); break;	
        };

        #undef DeclareComponent
    }

    // finish inheritance lookup table
    for( int32_t i = 0; i < Component::kCount; ++i ) {

        Vector<Component::Type> *base = m_baseToDerived[i];
        for( size_t baseIdx = 1; baseIdx < base->Size(); ++baseIdx ) {

            Vector<Component::Type> *derived = m_baseToDerived[(*base)[baseIdx]];
            for( size_t derivedIdx = 1; derivedIdx < derived->Size(); ++derivedIdx ) {
                Component::Type derivedType = (*derived)[derivedIdx];
                if( derivedType != Component::kNone )
                    base->PushBack( derivedType );
            }
        }
    }

    // make sure all lookup tables end with invalid type
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        if( m_baseToDerived[i]->Back() != Component::kNone )
            m_baseToDerived[i]->PushBack( Component::kNone );
    }

    Assert( m_baseToDerived[Component::kComponentBase]->Size() == Component::kCount + 1, "All component types must inherit from ComponentBase." );

    // preallocate all handles
    uint32_t total = std::accumulate( m_max, m_max + Component::kCount, 0 );
    m_handles = new List<UntypedHandle>( (uint16_t)total, false, g_permAllocator );
}

void ComponentManager::Deinitialize() {
    for( int32_t i = 0; i < Component::kCount + 1; ++i ) {
        delete[] m_data[i];
        delete[] m_generation[i];
        delete[] m_idToData[i];
        delete[] m_availableId[i];
        delete m_baseToDerived[i];
    }

    delete m_handles;
}

List<UntypedHandle>::iterator ComponentManager::FrontHandle() const {
    return m_handles->begin();
}

List<UntypedHandle>::iterator ComponentManager::Create( Component::Type type, GameObject *object ) {
    Assert( m_count[type] != m_max[type], "All components of type %i are in use.", type );

    // create component in the next available array index. components are always packed into the lower indices
    uint32_t componentIdx = m_count[type]; 
    uint8_t *data = m_data[type] + componentIdx * m_size[type];
    ++m_count[type];

    // assign an id
    // remove id from front of the array. when this component is destroyed, the id is placed at the back of the array
    uint32_t id = m_availableId[type][0]; 
    uint64_t generation = m_generation[type][id];
    m_idToData[type][id] = componentIdx;

    // shift available ids so we use all ids evenly
    size_t shiftSize = ( m_max[type] - m_count[type] ) * sizeof( uint32_t );
    Memmove( m_availableId[type], shiftSize, m_availableId[type] + 1, shiftSize );

    // construct the component
    #define DeclareComponent( typeName, baseTypeName, max ) \
    case Component::k##typeName: Construct( (typeName*)data, typeName( object, id, typeName##::kType ) ); break;

    switch( type ) {
    #include "Component/ComponentDeclarations.h"
    default: AssertAlways( "Invalid component type." ); break;	
    };

    #undef DeclareComponent

    return m_handles->Insert( m_handles->begin(), UntypedHandle( generation, id, type ) );
}

List<UntypedHandle>::iterator ComponentManager::Destroy( List<UntypedHandle>::const_iterator it ) {
    UntypedHandle handle = *it;
    Component::Type type = handle.m_type;

    // find the component data
    uint32_t componentIdx = m_idToData[type][handle.m_id];
    uint8_t *data = m_data[type] + componentIdx * m_size[type];
    --m_count[type];

    // destruct component then swap last component into it's array slot
    #define DeclareComponent( typeName, baseTypeName, max ) \
    case Component::k##typeName: {                                          \
        typeName *d = (typeName*)data;                                      \
        Destruct( d );                                                      \
        if( m_count[type] ) {                                               \
            uint8_t *endData = m_data[type] + m_count[type] * m_size[type]; \
            *d = *(typeName*)endData;                                       \
            m_idToData[type][d->m_id] = componentIdx;                       \
        }                                                                   \
        break; \
    }

    switch( handle.m_type ) {
    #include "Component/ComponentDeclarations.h"
    default: AssertAlways( "Invalid component type." ); break;	
    };

    #undef DeclareComponent

    // put the id at the back of the array
    m_availableId[type][m_max[type] - m_count[type] - 1] = handle.m_id;

    // increment the generation to invalidate handles
    ++m_generation[type][handle.m_id];

    return m_handles->Erase( it );
}