
// constructors
ForceInline Scalar::Scalar() {}

ForceInline Scalar::Scalar( __m128 const &s ) :m_value( s ) {}

ForceInline Scalar::Scalar( float s ) {
    m_value = _mm_set_ps1( s );
}

ForceInline Scalar Scalar::Zero() {
    return _mm_setzero_ps();
}

// assignment operators
ForceInline Scalar& Scalar::operator+=( Scalar const &s ) {
    m_value = _mm_add_ps( m_value, s.m_value );
    return *this;
}

ForceInline Scalar& Scalar::operator-=( Scalar const &s ) {
    m_value = _mm_sub_ps( m_value, s.m_value );
    return *this;
}

ForceInline Scalar& Scalar::operator*=( Scalar const &s ) {
    m_value = _mm_mul_ps( m_value, s.m_value );
    return *this;
}

ForceInline Scalar& Scalar::operator/=( Scalar const &s ) {
    __m128 rcp = _mm_rcp_ps( s.m_value );
    m_value = _mm_mul_ps( m_value, rcp );
    return *this;
}

// unary operators
ForceInline Scalar Scalar::operator+() const {
    return Scalar( m_value );
}

ForceInline Scalar Scalar::operator-() const {
    return _mm_sub_ps( _mm_xor_ps( m_value, m_value ), m_value );
}

// binary operators
ForceInline Scalar Scalar::operator+( Scalar const &s ) const {
    return _mm_add_ps( m_value, s.m_value );
}

ForceInline Scalar Scalar::operator-( Scalar const &s ) const {
    return _mm_sub_ps( m_value, s.m_value );
}

ForceInline Scalar Scalar::operator*( Scalar const &s ) const {
    return _mm_mul_ps( m_value, s.m_value );
}

ForceInline Scalar Scalar::operator/( Scalar const &s ) const {
    __m128 rcp = _mm_rcp_ps( s.m_value );
    return _mm_mul_ps( m_value, rcp );
}

//ForceInline Scalar operator*( Mat44 m ) const {
// &&&
//}

// comparison operators
ForceInline Bool Scalar::operator==( Scalar const &s ) const {
    return _mm_cmpeq_ps( m_value, s.m_value );
}

ForceInline Bool Scalar::operator!=( Scalar const &s ) const {
    return _mm_cmpneq_ps( m_value, s.m_value );
}

ForceInline Bool Scalar::operator<( Scalar const &s ) const {
    return _mm_cmplt_ps( m_value, s.m_value );
}

ForceInline Bool Scalar::operator>( Scalar const &s ) const {
    return _mm_cmpgt_ps( m_value, s.m_value );
}

ForceInline Bool Scalar::operator<=( Scalar const &s ) const {
    return _mm_cmple_ps( m_value, s.m_value );
}

ForceInline Bool Scalar::operator>=( Scalar const &s ) const {
    return _mm_cmpge_ps( m_value, s.m_value );
}

// accessors
ForceInline Scalar::operator float() const {
    return union_cast<float>( _mm_extract_ps( m_value, 0 ) );
}