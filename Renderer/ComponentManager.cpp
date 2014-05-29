#include "Renderer/ComponentManager.h"
#include "Renderer/ComponentIncludes.h"

#include "Core/Memory.h"
#include "Core/Assert.h"

#include <numeric>

// global instance
ComponentManager g_componentManager;

void ComponentManager::Initialize() {

    // preallocate lookup tables
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        m_inheritanceLookup[i] = new Vector<Component::Type>( Component::kCount + 1, false, g_permAllocator );
        m_inheritanceLookup[i]->PushBack( (Component::Type)i );
    }

    // add invalid type to make iterator simpler
    m_data             [Component::kNone] = new uint8_t[1];
    m_generation       [Component::kNone] = new uint64_t[1];
    m_idToData         [Component::kNone] = new uint32_t[1];
    m_availableId      [Component::kNone] = new uint32_t[1];
    m_availableIdCount [Component::kNone] = 0;
    m_count            [Component::kNone] = 1; // important for iterator to work properly
    m_max              [Component::kNone] = 0;
    m_size             [Component::kNone] = 0;
    m_inheritanceLookup[Component::kNone] = new Vector<Component::Type>( Component::kCount + 1, false, g_permAllocator );
    m_inheritanceLookup[Component::kNone]->PushBack( Component::kNone );

    // preallocate all component data
    for( int32_t i = 0; i < Component::kCount; ++i ) {

        #define DeclareComponent( typeName, baseTypeName, max ) \
        case Component::k##typeName: {                                         \
            m_data              [i] = new uint8_t[max * sizeof( typeName )];   \
            m_generation        [i] = new uint64_t[max];                       \
            m_idToData          [i] = new uint32_t[max];                       \
            m_availableId       [i] = new uint32_t[max];                       \
            m_availableIdCount  [i] = max;                                     \
            Memset( m_generation[i], 0, max * sizeof( uint64_t ) );            \
            for( uint32_t j = 0; j < max; ++j )                                \
                m_availableId[i][j] = j;                                       \
            m_count[i] = 0;                                                    \
            m_max[i] = max;                                                    \
            m_size[i] = sizeof( typeName );                                    \
            m_inheritanceLookup[Component::k##baseTypeName]->PushBack( Component::k##typeName ); \
            break; \
        }

        switch( i ) {
        #include "ComponentDeclarations.h"
        default: AssertAlways( "Invalid component type." ); break;	
        };

        #undef DeclareComponent
    }

    // finish inheritance lookup table
    for( int32_t i = 0; i < Component::kCount; ++i ) {

        Vector<Component::Type> *base = m_inheritanceLookup[i];
        for( size_t baseIdx = 1; baseIdx < base->Size(); ++baseIdx ) {

            Vector<Component::Type> *derived = m_inheritanceLookup[(*base)[baseIdx]];
            for( size_t derivedIdx = 1; derivedIdx < derived->Size(); ++derivedIdx ) {
                Component::Type derivedType = (*derived)[derivedIdx];
                if( derivedType != Component::kNone )
                    base->PushBack( derivedType );
            }
        }
    }

    // make sure all lookup tables end with invalid type
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        if( m_inheritanceLookup[i]->Back() != Component::kNone )
            m_inheritanceLookup[i]->PushBack( Component::kNone );
    }

    Assert( m_inheritanceLookup[Component::kComponentBase]->Size() == Component::kCount + 1, "All component types must inherit from ComponentBase." );

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
        delete m_inheritanceLookup[i];
    }
}

List<UntypedHandle>::iterator ComponentManager::BeginHandle() const {
    return m_handles->begin();
}

List<UntypedHandle>::iterator ComponentManager::Create( Component::Type type ) {
    Assert( m_count[type] != m_max[type], "All components of type %i are in use.", type );

    // create component in the next available array index. components are always packed into the lower indices
    uint32_t componentIdx = m_count[type]; 
    uint8_t *data = m_data[componentIdx * m_size[type]];
    ++m_count[type];

    // construct the component
    #define DeclareComponent( typeName, baseTypeName, max ) \
    case Component::k##typeName: Construct( (typeName*)data, typeName() ); break;

    switch( type ) {
    #include "ComponentDeclarations.h"
    default: AssertAlways( "Invalid component type." ); break;	
    };

    #undef DeclareComponent

    // assign an id
    // remove id from front of the array. when this component is destroyed, the id is placed at the back of the array
    uint32_t id = m_availableId[type][0]; 
    uint64_t generation = m_generation[type][id];
    m_idToData[type][id] = componentIdx;

    return m_handles->Insert( m_handles->begin(), UntypedHandle( generation, id, type ) );
}
