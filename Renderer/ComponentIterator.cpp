#include "Renderer/ComponentIterator.h"

template<typename T>
ComponentIterator<T>::ComponentIterator( uint8_t *(&componentData )[Component::kCount],
                                         size_t const (&componentCount)[Component::kCount],
                                         size_t const (&componentSize )[Component::kCount],
                                         Vector<Component::Type> * const &inheritanceLookup ) :
    m_componentData( componentData ),
    m_componentCount( componentCount ),
    m_componentSize( componentSize ),
    m_inheritanceLookup( inheritanceLookup ),
    m_data( componentData[T::kType] ),
    m_stride( componentSize[T::kType] ),
    m_i( 0 ),
    m_count( componentCount[T::kType] ),
    m_inheritanceIdx( 0 ) {

    Component::Type endType = inheritanceLookup->Back();
    uint8_t *endData = componentData[endType];
    size_t endSize = componentSize[endType];
    size_t endCount = componentCount[endType];
    m_end = endData + endCount * endSize;
}

// instantiate iterator types
#define DeclareComponent( typeName, baseTypeName, max ) template<typename T> class ComponentIterator;
#include "ComponentDeclarations.h"
#undef DeclareComponent