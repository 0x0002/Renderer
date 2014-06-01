#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Math/Transform.h"
#include "Component/UntypedHandle.h"

class GameObject {
public:



private:
    Transform                     m_transform;
    List<UntypedHandle>::iterator m_componentBegin;
    List<UntypedHandle>::iterator m_componentEnd;    
};

#endif // GAME_OBJECT_H