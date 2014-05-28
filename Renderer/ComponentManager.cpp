#include "Renderer/ComponentManager.h"

#include "Core/Memory.h"
#include "Core/Assert.h"

// global instance
ComponentManager g_componentManager;

void ComponentManager::Initialize() {

    // preallocate all component data
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        m_inheritanceLookup[i] = new Vector<Component::Type>( Component::kCount, false, g_permAllocator );
        m_inheritanceLookup[i]->PushBack( (Component::Type)i );
    }

    for( int32_t i = 0; i < Component::kCount; ++i ) {

        #define DeclareComponent( typeName, baseTypeName, max ) \
        case Component::k##typeName: { \
            m_componentData[i] = new uint8_t[ max * sizeof( typeName ) ]; \
            m_componentCount[i] = 0; \
            m_componentMax[i] = max; \
            m_componentSize[i] = sizeof( typeName ); \
            if( Component::k##baseTypeName != Component::kNone ) \
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
            for( size_t derivedIdx = 1; derivedIdx < derived->Size(); ++derivedIdx )
                base->PushBack( (*derived)[derivedIdx] );
        }
    }

    Assert( m_inheritanceLookup[Component::kComponentBase]->Size() == Component::kCount, "All component types must inherit from ComponentBase." );
}

void ComponentManager::Deinitialize() {
    for( int32_t i = 0; i < Component::kCount; ++i ) {
        delete[] m_componentData[i];
        delete m_inheritanceLookup[i];
    }
}