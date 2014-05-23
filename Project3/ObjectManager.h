#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

class FilePath;
class GameObject;

class ObjectManager {
public:
    void Load( FilePath const &path );

    GameObject* Create();
    void Destroy( GameObject *object );

private:
    // memory pool of game objects
};

// global instance
extern ObjectManager g_objectManager;

#endif // OBJECT_MANAGER_H