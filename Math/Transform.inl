
ForceInline Transform::Transform() :
    m_scale( 1.0f, 1.0f, 1.0f, 0.0f ),
    m_rotation( Quat::Identity() ),
    m_translation( Vec4::Zero() ) {
}

ForceInline Transform::Transform( Vec4 const &scale, Quat const &rotation, Vec4 const &translation ) :
    m_scale( scale ),
    m_rotation( rotation ),
    m_translation( translation ) {
}

ForceInline Transform Transform::operator*=( Transform const &t ) {
    m_scale *= t.m_scale;
    m_rotation *= t.m_rotation;
    m_translation = t.m_translation + ( m_translation * t.m_scale ) * t.m_rotation;
    return *this;
}

ForceInline Transform Transform::operator*( Transform const &t ) const {
    return Transform( m_scale * t.m_scale,
                      m_rotation * t.m_rotation,
                      t.m_translation + ( m_translation * t.m_scale ) * t.m_rotation );
}

ForceInline Transform::operator Mat44() const {
    return Mat44Scaling( m_scale ) * Mat44( m_rotation ) * Mat44Translation( m_translation );
}

ForceInline Transform Inverse( Transform const &t ) {
    Vec4 s( 1.0f / t.m_scale.X(), 1.0f / t.m_scale.Y(), 1.0f / t.m_scale.Z(), 0.0f );
    Quat q = Inverse( t.m_rotation );
    return Transform( s, q, ( -t.m_translation * s ) * q );
}

ForceInline Vec4& Transform::Scale() {
    return m_scale;
}

ForceInline Vec4 const& Transform::Scale() const {
    return m_scale;
}

ForceInline Quat& Transform::Rotation() {
    return m_rotation;
}

ForceInline Quat const& Transform::Rotation() const {
    return m_rotation;
}

ForceInline Vec4& Transform::Translation() {
    return m_translation;
}

ForceInline Vec4 const& Transform::Translation() const {
    return m_translation;
}