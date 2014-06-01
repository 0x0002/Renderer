#include "Component/ObjectManager.h"
#include "Component/ComponentManager.h"

// global instance
ObjectManager g_objectManager;

enum {
    kMaxObjects = 256
};

void ObjectManager::Initialize() {
    m_objects = new List<GameObject>( kMaxObjects, false, g_permAllocator );
}

void ObjectManager::Deinitialize() {
    delete m_objects;
}

List<GameObject>::iterator ObjectManager::Create() {
    return m_objects->Insert( m_objects->begin(), GameObject( g_componentManager.FrontHandle() ) );
}

void ObjectManager::Destroy( List<GameObject>::const_iterator it ) {
    m_objects->Erase( it );
}