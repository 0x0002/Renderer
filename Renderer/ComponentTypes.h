#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

namespace Component {

    #define DeclareComponent( typeName, baseTypeName ) k##typeName,

    enum Type {
        #include "Renderer/ComponentDeclarations.h"
        kCount,
        kNone
    };

    #undef DeclareComponent

}

#endif // COMPONENT_TYPE_H
