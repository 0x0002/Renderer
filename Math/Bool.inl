
// constructors
ForceInline Bool::Bool() {}

ForceInline Bool::Bool( __m128 const &b ) : m_value( b ) {}

ForceInline Bool::Bool( bool b ) :
    m_value( _mm_set_ps1( union_cast<float>( -(int32_t)b ) ) ) {
}

ForceInline Bool::Bool( bool x, bool y, bool z, bool w ) :
    m_value( _mm_setr_ps( union_cast<float>( -(int32_t)x ),
                          union_cast<float>( -(int32_t)y ),
                          union_cast<float>( -(int32_t)z ),
                          union_cast<float>( -(int32_t)w ) ) ) {
}

ForceInline Bool::Bool( int32_t i ) :
    m_value( _mm_setr_ps( union_cast<float>( -(int32_t)( i == 0 ) ),
                          union_cast<float>( -(int32_t)( i == 1 ) ),
                          union_cast<float>( -(int32_t)( i == 2 ) ),
                          union_cast<float>( -(int32_t)( i == 3 ) ) ) ) {
}

// unary operators
ForceInline Bool Bool::operator!() {
    m_value = _mm_xor_ps( m_value, m_value );
}

// comparison operators
ForceInline Bool Bool::operator==( Bool const &b ) const {
    return _mm_cmpeq_ps( m_value, b.m_value );
}

ForceInline Bool Bool::operator!=( Bool const &b ) const {
    return _mm_cmpneq_ps( m_value, b.m_value );
}

// accessors
ForceInline Bool::operator bool() const {
    return _mm_test_all_ones( _mm_castps_si128( m_value ) ) != 0;
}

// misc
ForceInline __m128 SelectElem( __m128 const &a, int32_t i ) {
    __m128 temp1 = Select( Bool( i ), a, _mm_setzero_ps() );
    __m128 temp2 = _mm_shuffle_ps( temp1, temp1, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 temp3 = _mm_or_ps( temp1, temp2 );
    __m128 temp4 = _mm_shuffle_ps( temp3, temp3, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_or_ps( temp3, temp4 );
}

ForceInline __m128 Select( Bool const &condition, __m128 const &true_, __m128 const &false_ ) {
    return _mm_blendv_ps( false_, true_, condition.m_value );
}

ForceInline Scalar Select( Bool const &condition, Scalar const &true_, Scalar const &false_ ) {
    return Select( condition, true_.m_value, false_.m_value );
}

ForceInline Vec4 Select( Bool const &condition, Vec4 const &true_, Vec4 const &false_ ) {
    return Select( condition, true_.m_value, false_.m_value );
}

ForceInline Quat Select( Bool const &condition, Quat const &true_, Quat const &false_ ) {
    return Select( condition, true_.m_value, false_.m_value );
}