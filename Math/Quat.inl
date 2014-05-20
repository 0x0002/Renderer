
// constructors
ForceInline Quat::Quat() {}

ForceInline Quat::Quat( __m128 const &q ) : m_value( q ) {}

ForceInline Quat::Quat( float x, float y, float z, float w ) : m_value( _mm_setr_ps( x, y, z, w ) ) {}

ForceInline Quat::Quat( Scalar const &x, Scalar const &y, Scalar const &z, Scalar const &w ) {
    __m128 xxyy = _mm_shuffle_ps( x.m_value, y.m_value, SHUFFLE( 0, 0, 0, 0 ) );
    __m128 zzww = _mm_shuffle_ps( z.m_value, w.m_value, SHUFFLE( 0, 0, 0, 0 ) );
    m_value = _mm_shuffle_ps( xxyy, zzww, SHUFFLE( 0, 2, 0, 2 ) );
}

ForceInline Quat::Quat( Mat44 const &m ) {

}

ForceInline Quat Quat::Identity() {
    return _mm_setr_ps( 0.0f, 0.0f, 0.0f, 1.0f );
}

// assignment operators
ForceInline Quat& Quat::operator+=( Quat const &q ) {
    m_value = _mm_add_ps( m_value, q.m_value );
    return *this;
}

ForceInline Quat& Quat::operator-=( Quat const &q ) {
    m_value = _mm_sub_ps( m_value, q.m_value );
    return *this;
}

ForceInline Quat& Quat::operator*=( Quat const &q ) {

}

ForceInline Quat& Quat::operator*=( Scalar const &s ) {
    m_value = _mm_mul_ps( m_value, s.m_value );
    return *this;
}

ForceInline Quat& Quat::operator/=( Scalar const &s ) {
    m_value = _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
    return *this;
}

// unary operators
ForceInline Quat Quat::operator+() const {
    return Quat( m_value );
}

ForceInline Quat Quat::operator-() const {
    return _mm_xor_ps( _mm_set_ps1( union_cast<float>( 0x80000000 ) ), m_value );
}

// binary operators
ForceInline Quat Quat::operator+( Quat const &q ) const {
    return _mm_add_ps( m_value, q.m_value );
}

ForceInline Quat Quat::operator-( Quat const &q ) const {
    return _mm_sub_ps( m_value, q.m_value );
}

ForceInline Quat Quat::operator*( Quat const &q ) const {

}

ForceInline Quat Quat::operator*( Scalar const &s ) const {
    return _mm_mul_ps( m_value, s.m_value );
}

ForceInline Quat Quat::operator/( Scalar const &s ) const {
    return _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
}

ForceInline Quat operator*( Scalar const &s, Quat const &q ) {
    return _mm_mul_ps( q.m_value, s.m_value );
}

ForceInline Quat operator/( Scalar const &s, Quat const &q ) {
    return _mm_mul_ps( q.m_value, _mm_rcp_ps( s.m_value ) );
}

// comparison operators
ForceInline Bool Quat::operator==( Quat const &q ) const {
    return _mm_cmpeq_ps( m_value, q.m_value );
}

ForceInline Bool Quat::operator!=( Quat const &q ) const {
    return _mm_cmpneq_ps( m_value, q.m_value );
}

// accessors
ForceInline Scalar Quat::X() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 0, 0, 0, 0 ) );
}

ForceInline Scalar Quat::Y() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 1, 1, 1 ) );
}

ForceInline Scalar Quat::Z() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 2, 2, 2 ) );
}

ForceInline Scalar Quat::W() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 3 ) );
}

ForceInline void Quat::XYZW( float xyzw[4] ) const {
    Align( 16 ) float f[4];
    _mm_store_ps( f, m_value );
    xyzw[0] = f[0];
    xyzw[1] = f[1];
    xyzw[2] = f[2];
    xyzw[3] = f[3];
}

ForceInline Scalar Quat::GetElem( int32_t i ) const {
    return SelectElem( m_value, i );
}


ForceInline void Quat::SetX( Scalar const &x ) {
    m_value = _mm_insert_ps( m_value, x.m_value, _MM_MK_INSERTPS_NDX( 0, 0, 0 ) );
}

ForceInline void Quat::SetY( Scalar const &y ) {
    m_value = _mm_insert_ps( m_value, y.m_value, _MM_MK_INSERTPS_NDX( 0, 1, 0 ) );
}

ForceInline void Quat::SetZ( Scalar const &z ) {
    m_value = _mm_insert_ps( m_value, z.m_value, _MM_MK_INSERTPS_NDX( 0, 2, 0 ) );
}

ForceInline void Quat::SetW( Scalar const &w ) {
    m_value = _mm_insert_ps( m_value, w.m_value, _MM_MK_INSERTPS_NDX( 0, 3, 0 ) );
}

ForceInline void Quat::SetElem( int32_t i, Scalar const &s ) {
    m_value = Select( Bool( i ), s.m_value, m_value );
}

// misc 
ForceInline Quat Normalize( Quat const &q ) {
    return q * RcpLength( q );
}

ForceInline Scalar Length( Quat const &q ) {
    return _mm_sqrt_ps( LengthSquared( q ).m_value );
}

ForceInline Scalar RcpLength( Quat const &q ) {
    return _mm_rsqrt_ps( LengthSquared( q ).m_value );
}

ForceInline Scalar LengthSquared( Quat const &q ) {
    return Dot( q, q );
}

ForceInline Scalar Dot( Quat const &a, Quat const &b ) {
    // use _mm_dp_ps instead?

    // 8 instructions
    __m128 product = _mm_mul_ps( a.m_value, b.m_value );
    __m128 wzyx = _mm_shuffle_ps( product, product, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 xw_yz_zy_wx = _mm_add_ps( product, wzyx ); // (xx+ww), (yy+zz), (zz+yy), (ww+xx)
    __m128 zy_wx_xw_yz = _mm_shuffle_ps( xw_yz_zy_wx, xw_yz_zy_wx, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_add_ps( xw_yz_zy_wx, zy_wx_xw_yz );    // (xx+ww+yy+zz), (yy+zz+ww+xx), (zz+yy+xx+ww), (ww+xx+yy+zz)
}

ForceInline Quat Conjugate( Quat const &q ) {
    float mask = union_cast<float>( 0x80000000 );
    return _mm_xor_ps( _mm_setr_ps( mask, mask, mask, 0.0f ), q.m_value );
}

ForceInline Quat Inverse( Quat const &q ) {
    return Conjugate( q ) / LengthSquared( q );
}

ForceInline Quat Slerp( Quat const &a, Quat const &b, Scalar t ) {
    Scalar cosOmega = Dot( a, b ); 

    Bool flip = cosOmega < 0.0f;
    cosOmega = Select( flip, -cosOmega, cosOmega );

    Scalar omega = Acos( cosOmega );
    Scalar invSinOmega = 1.0f / Sin( omega );
    Scalar alpha = Sin( ( 1.0f - t ) * omega ) * invSinOmega;
    Scalar beta = Sin( t * omega ) * invSinOmega;

    // if a and b are nearly the same direction, just lerp instead
    Bool lerp = ( 1.0f - cosOmega ) > kEpsilon;
    alpha = Select( lerp, ( 1.0f - t ), alpha );
    beta = Select( lerp, t, beta );

    beta = Select( flip, -beta, beta );
    return alpha * a + beta * b;
}


// transformation quaternions
ForceInline Quat QuaternionRotationAxisAngle( Vec4 const &axis, Scalar angle ) {

}

ForceInline Quat QuaternionRotationYawPitchRoll( Scalar yaw, Scalar pitch, Scalar roll ) {

}
