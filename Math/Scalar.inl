
// constructors
ForceInline Scalar::Scalar() {}

ForceInline Scalar::Scalar( __m128 const &s ) :m_value( s ) {}

ForceInline Scalar::Scalar( float s ) : m_value( _mm_set_ps1( s ) ) {}

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
    m_value = _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
    return *this;
}

// unary operators
ForceInline Scalar Scalar::operator+() const {
    return Scalar( m_value );
}

ForceInline Scalar Scalar::operator-() const {
    return _mm_xor_ps( _mm_set_ps1( union_cast<float>( 0x80000000 ) ), m_value );
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
    return _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
}

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

ForceInline Bool Scalar::operator==( float const &f ) const {
    return *this == Scalar( f );
}

ForceInline Bool Scalar::operator!=( float const &f ) const {
    return *this != Scalar( f );
}

ForceInline Bool Scalar::operator<( float const &f ) const {
    return *this < Scalar( f );
}

ForceInline Bool Scalar::operator>( float const &f ) const {
    return *this > Scalar( f );
}

ForceInline Bool Scalar::operator<=( float const &f ) const {
    return *this <= Scalar( f );
}

ForceInline Bool Scalar::operator>=( float const &f ) const {
    return *this >= Scalar( f );
}

// accessors
ForceInline Scalar::operator float() const {
    return union_cast<float>( _mm_extract_ps( m_value, 0 ) );
}

// misc
ForceInline Scalar Abs( Scalar const &s ) {
    return _mm_and_ps( _mm_set_ps1( union_cast<float>( 0x7fffffff ) ), s.m_value );
}

ForceInline Scalar Min( Scalar const &a, Scalar const &b ) {
    return _mm_min_ps( a.m_value, b.m_value );
}

ForceInline Scalar Max( Scalar const &a, Scalar const &b ) {
    return _mm_max_ps( a.m_value, b.m_value );
}