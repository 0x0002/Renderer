
// constructors
ForceInline Normal::Normal() {}

ForceInline Normal::Normal( Vec4 const &v ) {
    m_value = _mm_insert_ps( v.m_value, v.m_value, INSERT_ZERO( 3 ) );
}