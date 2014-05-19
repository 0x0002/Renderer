
// constructors
ForceInline Bool::Bool() {}

ForceInline Bool::Bool( __m128 const &b ) : m_value( b ) {}

ForceInline Bool::Bool( bool b ) {
    m_value = _mm_castsi128_ps( _mm_set1_epi32( -(int32_t)b ) );
}

ForceInline Bool::Bool( bool x, bool y, bool z, bool w ) {
    m_value = _mm_castsi128_ps( _mm_setr_epi32( -(int32_t)x, -(int32_t)y, -(int32_t)z, -(int32_t)w ) );
}

ForceInline Bool::Bool( int32_t i ) {
    m_value =_mm_castsi128_ps( _mm_setr_epi32( -(int32_t)( i == 0 ), -(int32_t)( i == 1 ), -(int32_t)( i == 2 ), -(int32_t)( i == 3 ) ) );
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
ForceInline __m128 Select( __m128 const &a, int32_t i ) {
    __m128 temp1 = Select( _mm_setzero_ps(), a, i );
    __m128 temp2 = _mm_shuffle_ps( temp1, temp1, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 temp3 = _mm_or_ps( temp1, temp2 );
    __m128 temp4 = _mm_shuffle_ps( temp3, temp3, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_or_ps( temp3, temp4 );
}

ForceInline __m128 Select( __m128 const &a, __m128 const &b, Bool const &c ) {
    return _mm_blendv_ps( a, b, c.m_value );
}