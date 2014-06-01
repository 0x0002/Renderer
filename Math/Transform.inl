
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
}

ForceInline Transform Transform::operator*( Transform const &t ) const {
    return Transform( m_scale * t.m_scale,
                      m_rotation * t.m_rotation,
                      t.m_translation + ( m_translation * t.m_scale ) * t.m_rotation );
}

#if 0
ForceInline Vec4 Transform::operator*( Vec4 const &v ) const {
    m_translation + ( v * m_scale ) * m_rotation;
}

ForceInline Vec4 Transform::operator*( Normal const &n ) const {
    return n * Transpose( Inverse( *this ) );
}
#endif

ForceInline Transform::operator Mat44() const {
    return Scaling( m_scale.X(), m_scale.Y(), m_scale.Z() ) * Mat44( m_rotation ) * Translation( m_translation );
}

ForceInline Transform Inverse( Transform const &transform ) {
    return Transform( Vec4( 1.0f / transform.m_scale.X(), 1.0f / transform.m_scale.Y(), 1.0f / transform.m_scale.Z(), 0.0f ),
                      Inverse( transform.m_rotation ),
                      -transform.m_translation );
}