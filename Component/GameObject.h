#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Math/Math.h"

#include "Component/UntypedHandle.h"

#include "Container/List.h"

class GameObject {
public:
    GameObject( List<UntypedHandle>::iterator it );

     UntypedHandle AddComponent( Component::Type type );
     void RemoveComponent( UntypedHandle const &handle );

     bool HasComponent( Component::Type type );
     UntypedHandle GetComponent( Component::Type type );

     Transform& Tform();
     Transform const& Tform() const;

     Vec4& Scale();
     Vec4 const& Scale() const;

     Quat& Rotation();
     Quat const& Rotation() const;

     Vec4& Translation();
     Vec4 const& Translation() const;

private:
    GameObject();

private:
    Transform                     m_transform;
    List<UntypedHandle>::iterator m_componentBegin;
    List<UntypedHandle>::iterator m_componentEnd;    
};

#endif // GAME_OBJECT_H