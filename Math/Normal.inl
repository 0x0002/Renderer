
// constructors
ForceInline Normal::Normal() {}

ForceInline Normal::Normal( Vec4 const &v ) {
    m_value = _mm_insert_ps( v.m_value, v.m_value, INSERT_ZERO( 3 ) );
}

ForceInline Normal& Normal::operator*=( Transform const &t ) {
    Vec4 s( 1.0f / t.m_scale.X(), 1.0f / t.m_scale.Y(), 1.0f / t.m_scale.Z(), 0.0f );
    Quat q = Inverse( t.m_rotation );
    m_value = ( Vec4( *this ) * Transpose( (Mat44)q * Mat44Scaling( s ) ) ).m_value;
    return *this;
} 

ForceInline Normal Normal::operator*( Transform const &t ) const {
    Vec4 s( 1.0f / t.m_scale.X(), 1.0f / t.m_scale.Y(), 1.0f / t.m_scale.Z(), 0.0f );
    Quat q = Inverse( t.m_rotation );
    return Vec4( *this ) * Transpose( (Mat44)q * Mat44Scaling( s ) );
}