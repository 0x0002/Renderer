
// constructors
ForceInline Normal::Normal() {}

ForceInline Normal::Normal( Vec4 const &v ) {
    m_value = _mm_insert_ps( v.m_value, v.m_value, INSERT_ZERO( 3 ) );
}

ForceInline Normal& Normal::operator*=( Transform const &t ) {
    m_value = ( Vec4( *this ) * Transpose( Inverse( t ) ) ).m_value;
    return *this;
} 

ForceInline Normal Normal::operator*( Transform const &t ) const {
    return Vec4( *this ) * Transpose( Inverse( t ) );
}