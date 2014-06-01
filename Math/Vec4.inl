
// constructors
ForceInline Vec4::Vec4() {}

ForceInline Vec4::Vec4( __m128 const &v ) : m_value( v ) {}

ForceInline Vec4::Vec4( float x, float y, float z, float w ) :
    m_value( _mm_setr_ps( x, y, z, w ) ) {
}

ForceInline Vec4::Vec4( Scalar const &x, Scalar const &y, Scalar const &z, Scalar const &w ) :
    m_value( _mm_shuffle_ps( _mm_shuffle_ps( x.m_value, y.m_value, SHUFFLE( 0, 0, 0, 0 ) ),
                             _mm_shuffle_ps( z.m_value, w.m_value, SHUFFLE( 0, 0, 0, 0 ) ), SHUFFLE( 0, 2, 0, 2 ) ) ) {
}

ForceInline Vec4::Vec4( Normal const &n ) : m_value( n.m_value ) {}

ForceInline Vec4 Vec4::Zero() {
    return _mm_setzero_ps();
}

ForceInline Vec4 Vec4::ZeroPoint() {
    return _mm_setr_ps( 0.0f, 0.0f, 0.0f, 1.0f );
}

ForceInline Vec4 Vec4::XAxis() {
    return _mm_setr_ps( 1.0f, 0.0f, 0.0f, 0.0f );
}

ForceInline Vec4 Vec4::YAxis() {
    return _mm_setr_ps( 0.0f, 1.0f, 0.0f, 0.0f );
}

ForceInline Vec4 Vec4::ZAxis() {
    return _mm_setr_ps( 0.0f, 0.0f, 1.0f, 0.0f );
}

ForceInline Vec4 Vec4::WAxis() {
    return _mm_setr_ps( 0.0f, 0.0f, 0.0f, 1.0f );
}

// assignment operators
ForceInline Vec4& Vec4::operator+=( Vec4 const &v ) {
    m_value = _mm_add_ps( m_value, v.m_value );
    return *this;
}

ForceInline Vec4& Vec4::operator-=( Vec4 const &v ) {
    m_value = _mm_sub_ps( m_value, v.m_value );
    return *this;
}

ForceInline Vec4& Vec4::operator*=( Vec4 const &v ) {
    m_value = _mm_mul_ps( m_value, v.m_value );
    return *this;
}

ForceInline Vec4& Vec4::operator*=( Mat44 const &m ) {
    __m128 x = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 0, 0, 0, 0 ) );
    __m128 x_mr0 = _mm_mul_ps( x, m.m_r[0] );                                        // (x*m00),                         (x*m01),                        (x*m02),                        (x*m03)
    __m128 y = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 1, 1, 1 ) ); 
    __m128 x_mr0_y_mr1 = _mm_add_ps( x_mr0, _mm_mul_ps( y, m.m_r[1] ) );             // (x*m00 + y*m10),                 (x*m01 + y*m11),                (x*m02 + y*m12),                (x*m03 + y*m13)
    __m128 z = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 2, 2, 2 ) );
    __m128 x_mr0_y_mr1_z_mr2 = _mm_add_ps( x_mr0_y_mr1, _mm_mul_ps( z, m.m_r[2] ) ); // (x*m00 + y*m10 + z*m20),         (x*m01 + y*m11 + z*m21),        (x*m02 + y*m12 + z*m22),        (x*m03 + y*m13 + z*m23)
    __m128 w = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 3 ) );
    m_value = _mm_add_ps( x_mr0_y_mr1_z_mr2, _mm_mul_ps( w, m.m_r[3] ) );            // (x*m00 + y*m10 + z*m20 + w*m30), (x*m01 + y*m11 + z*m21 +w*m31), (x*m02 + y*m12 + z*m22 +w*m32), (x*m03 + y*m13 + z*m23 +w*m33)
    return *this;
}

ForceInline Vec4& Vec4::operator*=( Quat const &q ) {
    // a = 2*( q.x*v.x + q.y*v.y + q.z*v.z );
    // b = 2*q.w;
    // c = b*q.w - 1;

    // return Vec4( c*v.x + a*q.x + b*( y*v.z - q.z*vector.y ),
    //              c*v.y + a*q.y + b*( z*v.x - q.x*vector.z ),
    //              c*v.z + a*q.z + b*( x*v.y - q.y*vector.x ) );

    // this is performing Inverse( q ) * *this * q

    // Dot3( *this, q )
    __m128 product = _mm_mul_ps( m_value, q.m_value );
    __m128 y___ = _mm_shuffle_ps( product, product, SHUFFLE( 1, 0, 0, 0 ) );
    __m128 z___ = _mm_shuffle_ps( product, product, SHUFFLE( 2, 0, 0, 0 ) );
    __m128 dot = _mm_add_ps( product, _mm_add_ps( y___, z___ ) ); // (xx+yy+zz), (_+_+_), (_+_+_), (_+_+_)
    dot = _mm_shuffle_ps( dot, dot, SHUFFLE( 0, 0, 0, 0 ) );

    // Cross( q, *this )
    __m128 yzx_ = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 zxy_ = _mm_shuffle_ps(   m_value,   m_value, SHUFFLE( 2, 0, 1, 0 ) );
    __m128 product1 = _mm_mul_ps( yzx_, zxy_ ); // (y1*z2), (z1*x2), (x1*y2), (x1*x2)
    zxy_ = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 2, 0, 1, 0 ) );
    yzx_ = _mm_shuffle_ps(   m_value,   m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 product2 = _mm_mul_ps( zxy_, yzx_ ); // (z1*y2), (x1*z2), (y1*x2), (x1*x2)
    __m128 cross = _mm_sub_ps( product1, product2 ); // w = 0  

    __m128 w = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 3, 3, 3, 3 ) );
    __m128 a = _mm_add_ps( dot, dot );                                // 2 * dot
    __m128 b = _mm_add_ps( w, w );                                    // 2 * w
    __m128 c = _mm_sub_ps( _mm_mul_ps( b, w ), _mm_set_ps1( 1.0f ) ); // 2*w^2 - 1

    __m128 temp0 = _mm_mul_ps( c, m_value );
    __m128 temp1 = _mm_mul_ps( a, q.m_value );
    __m128 temp2 = _mm_mul_ps( b, cross );

    __m128 result = _mm_add_ps( temp0, _mm_add_ps( temp1, temp2 ) );
    m_value = _mm_insert_ps( result, result, INSERT_ZERO( 3 ) );
    return *this;
}

ForceInline Vec4& Vec4::operator*=( Transform const &t ) {
    *this = t.m_translation + ( *this * t.m_scale ) * t.m_rotation;
    return *this;
}

ForceInline Vec4& Vec4::operator*=( Scalar const &s ) {
    m_value = _mm_mul_ps( m_value, s.m_value );
    return *this;
}

ForceInline Vec4& Vec4::operator/=( Scalar const &s ) {
    m_value = _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
    return *this;
}

// unary operators
ForceInline Vec4 Vec4::operator+() const {
    return Vec4( m_value );
}

ForceInline Vec4 Vec4::operator-() const {
    return _mm_xor_ps( _mm_set_ps1( union_cast<float>( 0x80000000 ) ), m_value );
}

// binary operators
ForceInline Vec4 Vec4::operator+( Vec4 const &v ) const {
    return _mm_add_ps( m_value, v.m_value );
}

ForceInline Vec4 Vec4::operator-( Vec4 const &v ) const {
    return _mm_sub_ps( m_value, v.m_value );
}

ForceInline Vec4 Vec4::operator*( Vec4 const &v ) const {
    return _mm_mul_ps( m_value, v.m_value );
}

ForceInline Vec4 Vec4::operator*( Mat44 const &m ) const {
    __m128 x = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 0, 0, 0, 0 ) );
    __m128 x_mr0 = _mm_mul_ps( x, m.m_r[0] );                                        // (x*m00),                         (x*m01),                        (x*m02),                        (x*m03)
    __m128 y = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 1, 1, 1 ) ); 
    __m128 x_mr0_y_mr1 = _mm_add_ps( x_mr0, _mm_mul_ps( y, m.m_r[1] ) );             // (x*m00 + y*m10),                 (x*m01 + y*m11),                (x*m02 + y*m12),                (x*m03 + y*m13)
    __m128 z = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 2, 2, 2 ) );
    __m128 x_mr0_y_mr1_z_mr2 = _mm_add_ps( x_mr0_y_mr1, _mm_mul_ps( z, m.m_r[2] ) ); // (x*m00 + y*m10 + z*m20),         (x*m01 + y*m11 + z*m21),        (x*m02 + y*m12 + z*m22),        (x*m03 + y*m13 + z*m23)
    __m128 w = _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 3 ) );
    return _mm_add_ps( x_mr0_y_mr1_z_mr2, _mm_mul_ps( w, m.m_r[3] ) );               // (x*m00 + y*m10 + z*m20 + w*m30), (x*m01 + y*m11 + z*m21 +w*m31), (x*m02 + y*m12 + z*m22 +w*m32), (x*m03 + y*m13 + z*m23 +w*m33)
}

ForceInline Vec4 Vec4::operator*( Quat const &q ) const {
    // a = 2*( q.x*v.x + q.y*v.y + q.z*v.z );
    // b = 2*q.w;
    // c = b*q.w - 1;

    // return Vec4( c*v.x + a*q.x + b*( y*v.z - q.z*vector.y ),
    //              c*v.y + a*q.y + b*( z*v.x - q.x*vector.z ),
    //              c*v.z + a*q.z + b*( x*v.y - q.y*vector.x ) );

    // this is performing Inverse( q ) * *this * q

    // Dot3( *this, q )
    __m128 product = _mm_mul_ps( m_value, q.m_value );
    __m128 y___ = _mm_shuffle_ps( product, product, SHUFFLE( 1, 0, 0, 0 ) );
    __m128 z___ = _mm_shuffle_ps( product, product, SHUFFLE( 2, 0, 0, 0 ) );
    __m128 dot = _mm_add_ps( product, _mm_add_ps( y___, z___ ) ); // (xx+yy+zz), (_+_+_), (_+_+_), (_+_+_)
    dot = _mm_shuffle_ps( dot, dot, SHUFFLE( 0, 0, 0, 0 ) );

    // Cross( q, *this )
    __m128 yzx_ = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 zxy_ = _mm_shuffle_ps(   m_value,   m_value, SHUFFLE( 2, 0, 1, 0 ) );
    __m128 product1 = _mm_mul_ps( yzx_, zxy_ ); // (y1*z2), (z1*x2), (x1*y2), (x1*x2)
    zxy_ = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 2, 0, 1, 0 ) );
    yzx_ = _mm_shuffle_ps(   m_value,   m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 product2 = _mm_mul_ps( zxy_, yzx_ ); // (z1*y2), (x1*z2), (y1*x2), (x1*x2)
    __m128 cross = _mm_sub_ps( product1, product2 ); // w = 0  

    __m128 w = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 3, 3, 3, 3 ) );
    __m128 a = _mm_add_ps( dot, dot );                                // 2 * dot
    __m128 b = _mm_add_ps( w, w );                                    // 2 * w
    __m128 c = _mm_sub_ps( _mm_mul_ps( b, w ), _mm_set_ps1( 1.0f ) ); // 2*w^2 - 1

    __m128 temp0 = _mm_mul_ps( c, m_value );
    __m128 temp1 = _mm_mul_ps( a, q.m_value );
    __m128 temp2 = _mm_mul_ps( b, cross );

    __m128 result = _mm_add_ps( temp0, _mm_add_ps( temp1, temp2 ) );
    return _mm_insert_ps( result, result, INSERT_ZERO( 3 ) );
}

ForceInline Vec4 Vec4::operator*( Transform const &t ) const {
    return t.m_translation + ( *this * t.m_scale ) * t.m_rotation;
}

ForceInline Vec4 Vec4::operator*( Scalar const &s ) const {
    return _mm_mul_ps( m_value, s.m_value );
}

ForceInline Vec4 Vec4::operator/( Scalar const &s ) const {
    return _mm_mul_ps( m_value, _mm_rcp_ps( s.m_value ) );
}

ForceInline Vec4 operator*( Scalar const &s, Vec4 const &v ) {
    return _mm_mul_ps( v.m_value, s.m_value );
}

// comparison operators
ForceInline Bool Vec4::operator==( Vec4 const &v ) const {
    return _mm_cmpeq_ps( m_value, v.m_value );
}

ForceInline Bool Vec4::operator!=( Vec4 const &v ) const {
    return _mm_cmpneq_ps( m_value, v.m_value );
}

// accessors
ForceInline Scalar Vec4::X() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 0, 0, 0, 0 ) );
}

ForceInline Scalar Vec4::Y() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 1, 1, 1, 1 ) );
}

ForceInline Scalar Vec4::Z() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 2, 2, 2, 2 ) );
}

ForceInline Scalar Vec4::W() const {
    return _mm_shuffle_ps( m_value, m_value, SHUFFLE( 3, 3, 3, 3 ) );
}

ForceInline void Vec4::XYZ( float xyz[3] ) const {
    Align( 16 ) float f[4];
    _mm_store_ps( f, m_value );
    xyz[0] = f[0];
    xyz[1] = f[1];
    xyz[2] = f[2];
}

ForceInline void Vec4::XYZW( float xyzw[4] ) const {
    Align( 16 ) float f[4];
    _mm_store_ps( f, m_value );
    xyzw[0] = f[0];
    xyzw[1] = f[1];
    xyzw[2] = f[2];
    xyzw[3] = f[3];
}

ForceInline Scalar Vec4::Elem( int32_t i ) const {
    return SelectElem( m_value, i );
}

ForceInline void Vec4::SetX( Scalar const &x ) {
    m_value = _mm_insert_ps( m_value, x.m_value, INSERT( 0, 0 ) );
}

ForceInline void Vec4::SetY( Scalar const &y ) {
    m_value = _mm_insert_ps( m_value, y.m_value, INSERT( 1, 1 ) );
}

ForceInline void Vec4::SetZ( Scalar const &z ) {
    m_value = _mm_insert_ps( m_value, z.m_value, INSERT( 2, 2 ) );
}

ForceInline void Vec4::SetW( Scalar const &w ) {
    m_value = _mm_insert_ps( m_value, w.m_value, INSERT( 3, 3 ) );
}

ForceInline void Vec4::SetXYZ( Scalar const &x, Scalar const &y, Scalar const &z ) {
    __m128 xxyy = _mm_shuffle_ps( x.m_value, y.m_value, SHUFFLE( 0, 0, 0, 0 ) );
    __m128 zzww = _mm_shuffle_ps( z.m_value, m_value, SHUFFLE( 0, 0, 3, 3 ) );
    m_value = _mm_shuffle_ps( xxyy, zzww, SHUFFLE( 0, 2, 0, 2 ) );
}

ForceInline void Vec4::SetXYZ( Vec4 const &xyz ) {
    m_value = _mm_blend_ps( m_value, xyz.m_value, BLEND( 1, 1, 1, 0 ) );
}

ForceInline void Vec4::SetElem( int32_t i, Scalar const &s ) {
    m_value = Select( Bool( i ), s.m_value, m_value );
}

// misc
ForceInline Vec4 Normalize( Vec4 const &v ) {
    return v * RcpLength( v );
}

ForceInline Vec4 Normalize3w0( Vec4 const &v ) {
    __m128 vw0 = _mm_insert_ps( v.m_value, v.m_value, INSERT_ZERO( 3 ) );
    return Normalize( Vec4( vw0 ) );
}

ForceInline Scalar Length( Vec4 const &v ) {
    return _mm_sqrt_ps( LengthSquared( v ).m_value );
}

ForceInline Scalar RcpLength( Vec4 const &v ) {
    return _mm_rsqrt_ps( LengthSquared( v ).m_value );
}

ForceInline Scalar LengthSquared( Vec4 const &v ) {
    return Dot( v, v );
}

ForceInline Scalar Dot( Vec4 const &a, Vec4 const &b ) {
    // use _mm_dp_ps instead?

    // 8 instructions
    __m128 product = _mm_mul_ps( a.m_value, b.m_value );
    __m128 wzyx = _mm_shuffle_ps( product, product, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 xw_yz_zy_wx = _mm_add_ps( product, wzyx ); // (xx+ww), (yy+zz), (zz+yy), (ww+xx)
    __m128 zy_wx_xw_yz = _mm_shuffle_ps( xw_yz_zy_wx, xw_yz_zy_wx, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_add_ps( xw_yz_zy_wx, zy_wx_xw_yz );    // (xx+ww+yy+zz), (yy+zz+ww+xx), (zz+yy+xx+ww), (ww+xx+yy+zz)
}

ForceInline Scalar Dot3( Vec4 const &a, Vec4 const &b ) {
    // use _mm_dp_ps instead?

    // 9 instructions, ignores w
    __m128 product = _mm_mul_ps( a.m_value, b.m_value );
    __m128 y___ = _mm_shuffle_ps( product, product, SHUFFLE( 1, 0, 0, 0 ) );
    __m128 z___ = _mm_shuffle_ps( product, product, SHUFFLE( 2, 0, 0, 0 ) );
    __m128 sum = _mm_add_ps( product, _mm_add_ps( y___, z___ ) ); // (xx+yy+zz), (_+_+_), (_+_+_), (_+_+_)
    return _mm_shuffle_ps( sum, sum, SHUFFLE( 0, 0, 0, 0 ) );
}

ForceInline Vec4 Cross( Vec4 const &a, Vec4 const &b ) {
    __m128 yzx_ = _mm_shuffle_ps( a.m_value, a.m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 zxy_ = _mm_shuffle_ps( b.m_value, b.m_value, SHUFFLE( 2, 0, 1, 0 ) );
    __m128 product1 = _mm_mul_ps( yzx_, zxy_ ); // (y1*z2), (z1*x2), (x1*y2), (x1*x2)
    zxy_ = _mm_shuffle_ps( a.m_value, a.m_value, SHUFFLE( 2, 0, 1, 0 ) );
    yzx_ = _mm_shuffle_ps( b.m_value, b.m_value, SHUFFLE( 1, 2, 0, 0 ) );
    __m128 product2 = _mm_mul_ps( zxy_, yzx_ ); // (z1*y2), (x1*z2), (y1*x2), (x1*x2)
    return _mm_sub_ps( product1, product2 ); // w = 0
}