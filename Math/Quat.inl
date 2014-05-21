
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
    // no attempt to optimize
    Scalar trace = m.Elem( 0, 0 ) + m.Elem( 1, 1 ) + m.Elem( 2, 2 );
    if( trace > 0.0f ) {
        SetX( m.Elem( 1, 2 ) - m.Elem( 2, 1 ) );
        SetY( m.Elem( 2, 0 ) - m.Elem( 0, 2 ) );
        SetZ( m.Elem( 0, 1 ) - m.Elem( 1, 0 ) );
        SetW( trace + 1.0f );
    }
    else if ( m.Elem( 0, 0 ) > m.Elem( 1, 1 ) && m.Elem( 0, 0 ) > m.Elem( 2, 2 ) ) {
        SetX( m.Elem( 0, 0 ) - m.Elem( 1, 1 ) - m.Elem( 2, 2 ) + 1.0f );
        SetY( m.Elem( 1, 0 ) + m.Elem( 0, 1 ) );
        SetZ( m.Elem( 2, 0 ) + m.Elem( 0, 2 ) );
        SetW( m.Elem( 1, 2 ) - m.Elem( 2, 1 ) );
    }
    else if ( m.Elem( 1, 1 ) > m.Elem( 2, 2 ) ) {
        SetX( m.Elem( 1, 1 ) - m.Elem( 0, 0 ) - m.Elem( 2, 2 ) + 1.0f );
        SetY( m.Elem( 1, 0 ) + m.Elem( 0, 1 ) );
        SetZ( m.Elem( 2, 1 ) + m.Elem( 1, 2 ) );
        SetW( m.Elem( 2, 0 ) - m.Elem( 0, 2 ) );
    }
    else {
        SetX( m.Elem( 2, 2 ) - m.Elem( 0, 0 ) - m.Elem( 1, 1 ) + 1.0f );
        SetY( m.Elem( 2, 0 ) + m.Elem( 0, 2 ) );
        SetZ( m.Elem( 1, 2 ) + m.Elem( 2, 1 ) );
        SetW( m.Elem( 0, 1 ) - m.Elem( 1, 0 ) );
    }

    *this = Normalize( *this );
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
    /* Quat( q.w * x + q.x * w + q.y * z - q.z * y,
             q.w * y + q.y * w + q.z * x - q.x * z,
             q.w * z + q.z * w + q.x * y - q.y * x,
             q.w * w - q.x * x - q.y * y - q.z * z); */

    __m128 q_wwww = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 3, 3, 3, 3 ) );
    __m128 q_xyzx = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 0, 1, 2, 0 ) );
    __m128 q_yzxy = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 1, 2, 0, 1 ) );
    __m128 q_zxyz = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 2, 0, 1, 2 ) );

    __m128 wwwx = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 0 ) );
    __m128 zxyy = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 0, 1, 1 ) );
    __m128 yzxz = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 2, 0, 2 ) );

    __m128 temp0 = _mm_mul_ps( q_wwww, m_value );
    __m128 temp1 = _mm_mul_ps( q_xyzx, wwwx );
    __m128 temp2 = _mm_mul_ps( q_yzxy, zxyy );
    __m128 temp3 = _mm_mul_ps( q_zxyz, yzxz );

    __m128 temp4 = _mm_sub_ps( temp2, temp3 );
    __m128 xyz_ = _mm_add_ps( temp0, _mm_add_ps( temp1, _mm_sub_ps( temp2, temp3 ) ) );
    __m128 ___w = _mm_sub_ps( temp0, _mm_add_ps( temp1, _mm_add_ps( temp2, temp3 ) ) );

    // the result should be normalized if both quaternions were normalized (assuming we are only using unit quaternions)
    // but because of floating point error we will renormalize anyway
    *this = Normalize( Quat( _mm_insert_ps( xyz_, ___w, INSERT( 3, 3 ) ) ) );
    return *this;
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
    /* Quat( q.w * x + q.x * w + q.y * z - q.z * y,
             q.w * y + q.y * w + q.z * x - q.x * z,
             q.w * z + q.z * w + q.x * y - q.y * x,
             q.w * w - q.x * x - q.y * y - q.z * z); */

    __m128 q_wwww = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 3, 3, 3, 3 ) );
    __m128 q_xyzx = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 0, 1, 2, 0 ) );
    __m128 q_yzxy = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 1, 2, 0, 1 ) );
    __m128 q_zxyz = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 2, 0, 1, 2 ) );

    __m128 wwwx = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 0 ) );
    __m128 zxyy = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 0, 1, 1 ) );
    __m128 yzxz = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 2, 0, 2 ) );

    __m128 temp0 = _mm_mul_ps( q_wwww, m_value );
    __m128 temp1 = _mm_mul_ps( q_xyzx, wwwx );
    __m128 temp2 = _mm_mul_ps( q_yzxy, zxyy );
    __m128 temp3 = _mm_mul_ps( q_zxyz, yzxz );

    __m128 temp4 = _mm_sub_ps( temp2, temp3 );
    __m128 xyz_ = _mm_add_ps( temp0, _mm_add_ps( temp1, _mm_sub_ps( temp2, temp3 ) ) );
    __m128 ___w = _mm_sub_ps( temp0, _mm_add_ps( temp1, _mm_add_ps( temp2, temp3 ) ) );

    // the result should be normalized if both quaternions were normalized (assuming we are only using unit quaternions)
    // but because of floating point error we will renormalize anyway
    return Normalize( Quat( _mm_insert_ps( xyz_, ___w, INSERT( 3, 3 ) ) ) );
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
    m_value = _mm_insert_ps( m_value, x.m_value, INSERT( 0, 0 ) );
}

ForceInline void Quat::SetY( Scalar const &y ) {
    m_value = _mm_insert_ps( m_value, y.m_value, INSERT( 1, 1 ) );
}

ForceInline void Quat::SetZ( Scalar const &z ) {
    m_value = _mm_insert_ps( m_value, z.m_value, INSERT( 2, 2 ) );
}

ForceInline void Quat::SetW( Scalar const &w ) {
    m_value = _mm_insert_ps( m_value, w.m_value, INSERT( 2, 3 ) );
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
    // we are assuming that all quaternions are normalized, so we won't renormalize here
    // otherwise: return Conjugate( q ) / LengthSquared( q );
    return Conjugate( q );
}

ForceInline Quat Slerp( Quat const &a, Quat const &b, Scalar const &t ) {
    Scalar cosOmega = Dot( a, b ); 

    Bool flip = cosOmega < Scalar::Zero();
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
ForceInline Quat QuatRotationAxisAngle( Vec4 const &axis, Scalar const &angle ) {
    Vec4 a = Normalize3w0( axis );
    Scalar s, c;
    SinCos( angle * 0.5f, &s, &c );

    Vec4 xyz_ = a * s;
    return Normalize( Quat( _mm_insert_ps( xyz_.m_value, c.m_value, INSERT( 3, 3 ) ) ) );
}

ForceInline Quat QuatRotationYawPitchRoll( Scalar const &yaw, Scalar const &pitch, Scalar const &roll ) {
    /* Quat( cy * sp * cr + sy * cp * sr,
             sy * cp * cr - cy * sp * sr,
             cy * cp * sr - sy * sp * cr,
             cy * cp * cr + sy * sp * sr); */

    Scalar sy, cy;
    SinCos( yaw * 0.5f, &sy, &cy );

    Scalar sp, cp;
    SinCos( pitch * 0.5f, &sp, &cp );

    Scalar sr, cr;
    SinCos( roll * 0.5f, &sr, &cr );

    __m128 cysycycy = _mm_blend_ps( cy.m_value, sy.m_value, BLEND( 0, 1, 0, 0 ) );
    __m128 spcpcpcp = _mm_blend_ps( sp.m_value, cp.m_value, BLEND( 0, 1, 1, 1 ) );
    __m128 crcrsrcr = _mm_blend_ps( cr.m_value, sr.m_value, BLEND( 0, 0, 1, 0 ) );

    __m128 sycysysy = _mm_shuffle_ps( cysycycy, cysycycy, SHUFFLE( 1, 0, 1, 1 ) );
    __m128 cpspspsp = _mm_shuffle_ps( spcpcpcp, spcpcpcp, SHUFFLE( 1, 0, 0, 0 ) );
    __m128 srsrcrsr = _mm_shuffle_ps( crcrsrcr, crcrsrcr, SHUFFLE( 2, 2, 0, 2 ) );

    __m128 temp0 = _mm_mul_ps( cysycycy, _mm_mul_ps( spcpcpcp, crcrsrcr ) );
    __m128 temp1 = _mm_mul_ps( sycysysy, _mm_mul_ps( cpspspsp, srsrcrsr ) );

    __m128 temp2 = _mm_add_ps( temp0, temp1 );
    __m128 temp3 = _mm_sub_ps( temp0, temp1 );

    return Quat( _mm_blend_ps( temp2, temp3, BLEND( 0, 1, 1, 0 ) ) );
}
