
// DeclareComponent( typeName, baseTypeName, max )
// Don't put anything except DeclareComponent( ... ) lines in this file.
DeclareComponent( ComponentBase,     None,             0 )

DeclareComponent( ShapeBase,         ComponentBase,    0 )
DeclareComponent( Sphere,            ShapeBase,      100 )

DeclareComponent( CameraBase,        ComponentBase,    0 )
DeclareComponent( PerspectiveCamera, CameraBase,       1 )
