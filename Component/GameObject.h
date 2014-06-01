#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Transform.h"
#include "ComponentBase.h"

class GameObject {
public:
    GameObject();



private:
    // &&& parent
    Transform *m_transform;
    List<Component*> 
};

#endif // GAME_OBJECT_H