
// constructors
ForceInline Normal::Normal() {}

ForceInline Normal::Normal( Vec4 const &v ) {
    m_value = _mm_insert_ps( v.m_value, _mm_setzero_ps(), _MM_MK_INSERTPS_NDX( 3, 3, 0 ) );
}