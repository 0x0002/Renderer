#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "Component/GameObject.h"

class ObjectManager {
public:
    void Initialize();
    void Deinitialize();

    List<GameObject>::iterator Create();
    void Destroy( List<GameObject>::const_iterator it );

private:
    List<GameObject> *m_objects;
};

// global instance
extern ObjectManager g_objectManager;

#endif // OBJECT_MANAGER_H