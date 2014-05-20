
// constructors
ForceInline Mat44::Mat44() {}

ForceInline Mat44::Mat44( __m128 const &r0, __m128 const &r1, __m128 const &r2, __m128 const &r3 ) {
    m_r[0] = r0;
    m_r[1] = r1;
    m_r[2] = r2;
    m_r[3] = r3;
}

ForceInline Mat44::Mat44( float const f[16] ) {
    m_r[0] = _mm_setr_ps( f[0],  f[1],  f[2],  f[3] );
    m_r[1] = _mm_setr_ps( f[4],  f[5],  f[6],  f[7] );
    m_r[2] = _mm_setr_ps( f[8],  f[9],  f[10], f[11] );
    m_r[3] = _mm_setr_ps( f[12], f[13], f[14], f[15] );
}

ForceInline Mat44::Mat44( float _00, float _01, float _02, float _03,
                          float _10, float _11, float _12, float _13,
                          float _20, float _21, float _22, float _23,
                          float _30, float _31, float _32, float _33 ) {
    m_r[0] = _mm_setr_ps( _00, _01, _02, _03 );
    m_r[1] = _mm_setr_ps( _10, _11, _12, _13 );
    m_r[2] = _mm_setr_ps( _20, _21, _22, _23 );
    m_r[3] = _mm_setr_ps( _30, _31, _32, _33 );
}

ForceInline Mat44::Mat44( Vec4 const &r0, Vec4 const &r1, Vec4 const &r2, Vec4 const &r3 ) {
    m_r[0] = r0.m_value;
    m_r[1] = r1.m_value;
    m_r[2] = r2.m_value;
    m_r[3] = r3.m_value;
}

ForceInline Mat44::Mat44( Quat const &q ) {
    /* Mat44( 1 - 2yy - 2zz, 2zw + 2xy      2zx - 2yw,     0,
              2xy - 2zw,     1 - 2zz - 2xx, 2xw + 2yz,     0,
              2yw + 2zx,     2yz - 2xw,     1 - 2xx - 2yy, 0,
              0,                     0,                 0, 1 ); */

    __m128 selectY = _mm_setr_ps( 0.0f, union_cast<float>( 0xffffffff ), 0.0f, 0.0f );
    __m128 selectZ = _mm_setr_ps( 0.0f, union_cast<float>( 0xffffffff ), 0.0f, 0.0f );

    __m128 xyzw_2 = _mm_add_ps( q.m_value, q.m_value );
    __m128 yzxw_2 = _mm_shuffle_ps( xyzw_2, xyzw_2, SHUFFLE( 1, 2, 0, 3 ) );
    __m128 zxyw_2 = _mm_shuffle_ps( xyzw_2, xyzw_2, SHUFFLE( 2, 0, 1, 3 ) );

    __m128 wwww = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 3, 3, 3, 3 ) );
    __m128 yzxw = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 1, 2, 0, 3 ) );
    __m128 zxyw = _mm_shuffle_ps( q.m_value, q.m_value, SHUFFLE( 2, 0, 1, 3 ) );

    __m128 temp0 = _mm_mul_ps( yzxw_2, wwww );                                    // (2yw), (2zw), (2xw), (2ww)
    __m128 temp1 = _mm_sub_ps( _mm_set_ps1( 1.0f ), _mm_mul_ps( yzxw_2, yzxw ) ); // (1 - 2yy), (1 - 2zz), (1 - 2xx), (1 - 2ww)
    __m128 temp2 = _mm_mul_ps( xyzw_2, yzxw );                                    // (2xy), (2yz), (2zx), (2ww)

    temp0 = _mm_add_ps( temp0, _mm_mul_ps( zxyw, xyzw_2 ) );                      // (2yw + 2zx), (2zw + 2xy), (2xw + 2yz), (2ww + 2ww)
    temp1 = _mm_sub_ps( temp1, _mm_mul_ps( zxyw_2, zxyw ) );                      // (1 - 2yy - 2zz), (1 - 2zz - 2xx), (1 - 2xx - 2yy), (1 - 2ww - 2ww)
    temp2 = _mm_sub_ps( temp2, _mm_mul_ps( zxyw_2, wwww ) );                      // (2xy - 2zw), (2yz - 2xw), (2zx - 2yw), (2ww - 2ww)

    // Mat44( temp1.x, temp0.y, temp2.z, 0,
    //        temp2.x, temp1.y, temp0.z, 0,
    //        temp0.x, temp2.y, temp1.z, 0,
    //              0,       0,       0, 1);

    m_r[0] = Select( selectZ, temp2, Select( selectY, temp0, temp1 ) );
    m_r[1] = Select( selectZ, temp0, Select( selectY, temp1, temp2 ) );
    m_r[2] = Select( selectZ, temp1, Select( selectY, temp2, temp0 ) );
    m_r[0] = _mm_insert_ps( m_r[0], temp2, _MM_MK_INSERTPS_NDX( 0, 3, 0 ) );
    m_r[1] = _mm_insert_ps( m_r[1], temp2, _MM_MK_INSERTPS_NDX( 0, 3, 0 ) );
    m_r[2] = _mm_insert_ps( m_r[2], temp2, _MM_MK_INSERTPS_NDX( 0, 3, 0 ) );
    m_r[3] = _mm_setr_ps( 0.0f, 0.0f, 0.0f, 1.0f );
}

ForceInline Mat44 Mat44::Identity() {
    return Mat44( 1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f );
}

ForceInline Mat44 Mat44::Zero() {
    __m128 zero = _mm_setzero_ps();
    return Mat44( zero, zero, zero, zero );
}

// assignment operators
ForceInline Mat44& Mat44::operator+=( Mat44 const &m ) {
    m_r[0] = _mm_add_ps( m_r[0], m.m_r[0] );
    m_r[1] = _mm_add_ps( m_r[1], m.m_r[1] );
    m_r[2] = _mm_add_ps( m_r[2], m.m_r[2] );
    m_r[3] = _mm_add_ps( m_r[3], m.m_r[3] );
    return *this;
}

ForceInline Mat44& Mat44::operator-=( Mat44 const &m ) {
    m_r[0] = _mm_sub_ps( m_r[0], m.m_r[0] );
    m_r[1] = _mm_sub_ps( m_r[1], m.m_r[1] );
    m_r[2] = _mm_sub_ps( m_r[2], m.m_r[2] );
    m_r[3] = _mm_sub_ps( m_r[3], m.m_r[3] );
    return *this;
}

ForceInline Mat44& Mat44::operator*=( Mat44 const &m ) {
    // row0
    __m128 a00 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a00br0 = _mm_mul_ps( m.m_r[0], a00 );                                            // (a00*b00),                               (a00*b01),                              (a00*b02),                              (a00*b03)
    __m128 a01 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a00br0_a01br1 = _mm_add_ps( a00br0, _mm_mul_ps( a01, m.m_r[1] ) );               // (a00*b00 + a01*b10),                     (a00*b01 + a01*b11),                    (a00*b02 + a01*b12),                    (a00*b03 + a01*b13)
    __m128 a02 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a00br0_a01br1_a02br2 = _mm_add_ps( a00br0_a01br1, _mm_mul_ps( a02, m.m_r[2] ) ); // (a00*b00 + a01*b10 + a02*b20),           (a00*b01 + a01*b11 + a02*b21),          (a00*b02 + a01*b12 + a02*b22),          (a00*b03 + a01*b13 + a02*b23)
    __m128 a03 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row0 = _mm_add_ps( a00br0_a01br1_a02br2, _mm_mul_ps( a03, m.m_r[3] ) );          // (a00*b00 + a01*b10 + a02*b20 + a03*b30), (a00*b01 + a01*b11 + a02*b21 +a03*b31), (a00*b02 + a01*b12 + a02*b22 +a03*b32), (a00*b03 + a01*b13 + a02*b23 +a03*b33)

    // row1
    __m128 a10 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a10br0 = _mm_mul_ps( m.m_r[0], a10 );                                            // (a10*b00),                               (a10*b01),                              (a10*b02),                              (a10*b03)
    __m128 a11 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a10br0_a11br1 = _mm_add_ps( a10br0, _mm_mul_ps( a11, m.m_r[1] ) );               // (a10*b00 + a11*b10),                     (a10*b01 + a11*b11),                    (a10*b02 + a11*b12),                    (a10*b03 + a11*b13)
    __m128 a12 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 2, 2, 2, 2 ) ); 
    __m128 a10br0_a11br1_a12br2 = _mm_add_ps( a10br0_a11br1, _mm_mul_ps( a12, m.m_r[2] ) ); // (a10*b00 + a11*b10 + a12*b20),           (a10*b01 + a11*b11 + a12*b21),          (a10*b02 + a11*b12 + a12*b22),          (a10*b03 + a11*b13 + a12*b23)
    __m128 a13 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row1 = _mm_add_ps( a10br0_a11br1_a12br2, _mm_mul_ps( a13, m.m_r[3] ) );          // (a10*b00 + a11*b10 + a12*b20 + a13*b30), (a10*b01 + a11*b11 + a12*b21 +a13*b31), (a10*b02 + a11*b12 + a12*b22 +a13*b32), (a10*b03 + a11*b13 + a12*b23 +a13*b33)

    // row2
    __m128 a20 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a20br0 = _mm_mul_ps( m.m_r[0], a20 );                                            // (a20*b00),                               (a20*b01),                              (a20*b02),                              (a20*b03)
    __m128 a21 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a20br0_a21br1 = _mm_add_ps( a20br0, _mm_mul_ps( a21, m.m_r[1] ) );               // (a20*b00 + a21*b10),                     (a20*b01 + a21*b11),                    (a20*b02 + a21*b12),                    (a20*b03 + a21*b13)
    __m128 a22 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a20br0_a21br1_a22br2 = _mm_add_ps( a20br0_a21br1, _mm_mul_ps( a22, m.m_r[2] ) ); // (a20*b00 + a21*b10 + a22*b20),           (a20*b01 + a21*b11 + a22*b21),          (a20*b02 + a21*b12 + a22*b22),          (a20*b03 + a21*b13 + a22*b23)
    __m128 a23 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row2 = _mm_add_ps( a20br0_a21br1_a22br2, _mm_mul_ps( a23, m.m_r[3] ) );          // (a20*b00 + a21*b10 + a22*b20 + a23*b30), (a20*b01 + a21*b11 + a22*b21 +a23*b31), (a20*b02 + a21*b12 + a22*b22 +a23*b32), (a20*b03 + a21*b13 + a22*b23 +a23*b33)

    // row3
    __m128 a30 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a30br0 = _mm_mul_ps( m.m_r[0], a30 );                                            // (a30*b00),                               (a30*b01),                              (a30*b02),                              (a30*b03)
    __m128 a31 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a30br0_a31br1 = _mm_add_ps( a30br0, _mm_mul_ps( a31, m.m_r[1] ) );               // (a30*b00 + a31*b10),                     (a30*b01 + a31*b11),                    (a30*b02 + a31*b12),                    (a30*b03 + a31*b13)
    __m128 a32 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a30br0_a31br1_a32br2 = _mm_add_ps( a30br0_a31br1, _mm_mul_ps( a32, m.m_r[2] ) ); // (a30*b00 + a31*b10 + a32*b20),           (a30*b01 + a31*b11 + a32*b21),          (a30*b02 + a31*b12 + a32*b22),          (a30*b03 + a31*b13 + a32*b23)
    __m128 a33 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row3 = _mm_add_ps( a30br0_a31br1_a32br2, _mm_mul_ps( a33, m.m_r[3] ) );          // (a30*b00 + a31*b10 + a32*b20 + a33*b30), (a30*b01 + a31*b11 + a32*b21 +a33*b31), (a30*b02 + a31*b12 + a32*b22 +a33*b32), (a30*b03 + a31*b13 + a32*b23 +a33*b33)

    m_r[0] = row0;
    m_r[1] = row1;
    m_r[2] = row2;
    m_r[3] = row3;
    return *this;
}

ForceInline Mat44& Mat44::operator*=( Scalar const &s ) {
    m_r[0] = _mm_mul_ps( m_r[0], s.m_value );
    m_r[1] = _mm_mul_ps( m_r[1], s.m_value );
    m_r[2] = _mm_mul_ps( m_r[2], s.m_value );
    m_r[3] = _mm_mul_ps( m_r[3], s.m_value );
    return *this;
}

ForceInline Mat44& Mat44::operator/=( Scalar const &s ) {
    __m128 rcp = _mm_rcp_ps( s.m_value );
    m_r[0] = _mm_mul_ps( m_r[0], rcp );
    m_r[1] = _mm_mul_ps( m_r[1], rcp );
    m_r[2] = _mm_mul_ps( m_r[2], rcp );
    m_r[3] = _mm_mul_ps( m_r[3], rcp );
    return *this;
}

// unary operators
ForceInline Mat44 Mat44::operator+() const {
    return Mat44( m_r[0], m_r[1], m_r[2], m_r[3] );
}

ForceInline Mat44 Mat44::operator-() const {
    __m128 mask = _mm_set_ps1( union_cast<float>( 0x80000000 ) );
    return Mat44( _mm_xor_ps( mask, m_r[0] ),
                  _mm_xor_ps( mask, m_r[1] ),
                  _mm_xor_ps( mask, m_r[2] ),
                  _mm_xor_ps( mask, m_r[3] ) );
}

// binary operators
ForceInline Mat44 Mat44::operator+( Mat44 const &m ) const {
    return Mat44( _mm_add_ps( m_r[0], m.m_r[0] ),
                  _mm_add_ps( m_r[1], m.m_r[1] ),
                  _mm_add_ps( m_r[2], m.m_r[2] ),
                  _mm_add_ps( m_r[3], m.m_r[3] ) );
}

ForceInline Mat44 Mat44::operator-( Mat44 const &m ) const {
    return Mat44( _mm_sub_ps( m_r[0], m.m_r[0] ),
                  _mm_sub_ps( m_r[1], m.m_r[1] ),
                  _mm_sub_ps( m_r[2], m.m_r[2] ),
                  _mm_sub_ps( m_r[3], m.m_r[3] ) );
}

ForceInline Mat44 Mat44::operator*( Mat44 const &m ) const {
    // row0
    __m128 a00 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a00br0 = _mm_mul_ps( a00, m.m_r[0] );                                            // (a00*b00),                               (a00*b01),                              (a00*b02),                              (a00*b03)
    __m128 a01 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a00br0_a01br1 = _mm_add_ps( a00br0, _mm_mul_ps( a01, m.m_r[1] ) );               // (a00*b00 + a01*b10),                     (a00*b01 + a01*b11),                    (a00*b02 + a01*b12),                    (a00*b03 + a01*b13)
    __m128 a02 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a00br0_a01br1_a02br2 = _mm_add_ps( a00br0_a01br1, _mm_mul_ps( a02, m.m_r[2] ) ); // (a00*b00 + a01*b10 + a02*b20),           (a00*b01 + a01*b11 + a02*b21),          (a00*b02 + a01*b12 + a02*b22),          (a00*b03 + a01*b13 + a02*b23)
    __m128 a03 = _mm_shuffle_ps( m_r[0], m_r[0], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row0 = _mm_add_ps( a00br0_a01br1_a02br2, _mm_mul_ps( a03, m.m_r[3] ) );          // (a00*b00 + a01*b10 + a02*b20 + a03*b30), (a00*b01 + a01*b11 + a02*b21 +a03*b31), (a00*b02 + a01*b12 + a02*b22 +a03*b32), (a00*b03 + a01*b13 + a02*b23 +a03*b33)

    // row1
    __m128 a10 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a10br0 = _mm_mul_ps( a10, m.m_r[0] );                                            // (a10*b00),                               (a10*b01),                              (a10*b02),                              (a10*b03)
    __m128 a11 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a10br0_a11br1 = _mm_add_ps( a10br0, _mm_mul_ps( a11, m.m_r[1] ) );               // (a10*b00 + a11*b10),                     (a10*b01 + a11*b11),                    (a10*b02 + a11*b12),                    (a10*b03 + a11*b13)
    __m128 a12 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a10br0_a11br1_a12br2 = _mm_add_ps( a10br0_a11br1, _mm_mul_ps( a12, m.m_r[2] ) ); // (a10*b00 + a11*b10 + a12*b20),           (a10*b01 + a11*b11 + a12*b21),          (a10*b02 + a11*b12 + a12*b22),          (a10*b03 + a11*b13 + a12*b23)
    __m128 a13 = _mm_shuffle_ps( m_r[1], m_r[1], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row1 = _mm_add_ps( a10br0_a11br1_a12br2, _mm_mul_ps( a13, m.m_r[3] ) );          // (a10*b00 + a11*b10 + a12*b20 + a13*b30), (a10*b01 + a11*b11 + a12*b21 +a13*b31), (a10*b02 + a11*b12 + a12*b22 +a13*b32), (a10*b03 + a11*b13 + a12*b23 +a13*b33)

    // row2
    __m128 a20 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a20br0 = _mm_mul_ps( a20, m.m_r[0] );                                            // (a20*b00),                               (a20*b01),                              (a20*b02),                              (a20*b03)
    __m128 a21 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a20br0_a21br1 = _mm_add_ps( a20br0, _mm_mul_ps( a21, m.m_r[1] ) );               // (a20*b00 + a21*b10),                     (a20*b01 + a21*b11),                    (a20*b02 + a21*b12),                    (a20*b03 + a21*b13)
    __m128 a22 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a20br0_a21br1_a22br2 = _mm_add_ps( a20br0_a21br1, _mm_mul_ps( a22, m.m_r[2] ) ); // (a20*b00 + a21*b10 + a22*b20),           (a20*b01 + a21*b11 + a22*b21),          (a20*b02 + a21*b12 + a22*b22),          (a20*b03 + a21*b13 + a22*b23)
    __m128 a23 = _mm_shuffle_ps( m_r[2], m_r[2], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row2 = _mm_add_ps( a20br0_a21br1_a22br2, _mm_mul_ps( a23, m.m_r[3] ) );          // (a20*b00 + a21*b10 + a22*b20 + a23*b30), (a20*b01 + a21*b11 + a22*b21 +a23*b31), (a20*b02 + a21*b12 + a22*b22 +a23*b32), (a20*b03 + a21*b13 + a22*b23 +a23*b33)

    // row3
    __m128 a30 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 0, 0, 0, 0 ) );
    __m128 a30br0 = _mm_mul_ps( a30, m.m_r[0] );                                            // (a30*b00),                               (a30*b01),                              (a30*b02),                              (a30*b03)
    __m128 a31 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 1, 1, 1, 1 ) );
    __m128 a30br0_a31br1 = _mm_add_ps( a30br0, _mm_mul_ps( a31, m.m_r[1] ) );               // (a30*b00 + a31*b10),                     (a30*b01 + a31*b11),                    (a30*b02 + a31*b12),                    (a30*b03 + a31*b13)
    __m128 a32 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 2, 2, 2, 2 ) );
    __m128 a30br0_a31br1_a32br2 = _mm_add_ps( a30br0_a31br1, _mm_mul_ps( a32, m.m_r[2] ) ); // (a30*b00 + a31*b10 + a32*b20),           (a30*b01 + a31*b11 + a32*b21),          (a30*b02 + a31*b12 + a32*b22),          (a30*b03 + a31*b13 + a32*b23)
    __m128 a33 = _mm_shuffle_ps( m_r[3], m_r[3], SHUFFLE( 3, 3, 3, 3 ) );
    __m128 row3 = _mm_add_ps( a30br0_a31br1_a32br2, _mm_mul_ps( a33, m.m_r[3] ) );          // (a30*b00 + a31*b10 + a32*b20 + a33*b30), (a30*b01 + a31*b11 + a32*b21 +a33*b31), (a30*b02 + a31*b12 + a32*b22 +a33*b32), (a30*b03 + a31*b13 + a32*b23 +a33*b33)

    return Mat44( row0, row1, row2, row3 );
}

ForceInline Mat44 Mat44::operator*( Scalar const &s ) const {
    return Mat44( _mm_mul_ps( m_r[0], s.m_value ),
                  _mm_mul_ps( m_r[1], s.m_value ),
                  _mm_mul_ps( m_r[2], s.m_value ),
                  _mm_mul_ps( m_r[3], s.m_value ) );
}

ForceInline Mat44 Mat44::operator/( Scalar const &s ) const {
    __m128 rcp = _mm_rcp_ps( s.m_value );
    return Mat44( _mm_mul_ps( m_r[0], rcp ),
                  _mm_mul_ps( m_r[1], rcp ),
                  _mm_mul_ps( m_r[2], rcp ),
                  _mm_mul_ps( m_r[3], rcp ) );
}

ForceInline Mat44 operator*( Scalar const &s, Mat44 const &m ) {
    return Mat44( _mm_mul_ps( m.m_r[0], s.m_value ),
                  _mm_mul_ps( m.m_r[1], s.m_value ),
                  _mm_mul_ps( m.m_r[2], s.m_value ),
                  _mm_mul_ps( m.m_r[3], s.m_value ) );
}

// comparison operators
ForceInline Bool Mat44::operator==( Mat44 const &m ) const {
    // compare rows
    __m128 r0 = _mm_cmpeq_ps( m_r[0], m.m_r[0] );
    __m128 r1 = _mm_cmpeq_ps( m_r[1], m.m_r[1] );
    __m128 r2 = _mm_cmpeq_ps( m_r[2], m.m_r[2] );
    __m128 r3 = _mm_cmpeq_ps( m_r[3], m.m_r[3] );

    // compare columns
    __m128 temp1 = _mm_and_ps( r0, r1 );
    __m128 temp2 = _mm_and_ps( r2, r3 );
    __m128 temp3 = _mm_and_ps( temp1, temp2 );

    // test if all results are true
    __m128 wzyx = _mm_shuffle_ps( temp3, temp3, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 xw_yz_zy_wx = _mm_and_ps( wzyx, temp3 );
    __m128 zy_wx_xw_yz = _mm_shuffle_ps( xw_yz_zy_wx, xw_yz_zy_wx, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_and_ps( xw_yz_zy_wx, zy_wx_xw_yz );
}

ForceInline Bool Mat44::operator!=( Mat44 const &m ) const {
    // compare rows
    __m128 r0 = _mm_cmpneq_ps( m_r[0], m.m_r[0] );
    __m128 r1 = _mm_cmpneq_ps( m_r[1], m.m_r[1] );
    __m128 r2 = _mm_cmpneq_ps( m_r[2], m.m_r[2] );
    __m128 r3 = _mm_cmpneq_ps( m_r[3], m.m_r[3] );

    // compare columns
    __m128 temp1 = _mm_and_ps( r0, r1 );
    __m128 temp2 = _mm_and_ps( r2, r3 );
    __m128 temp3 = _mm_and_ps( temp1, temp2 );

    // test if all results are true
    __m128 wzyx = _mm_shuffle_ps( temp3, temp3, SHUFFLE( 3, 2, 1, 0 ) );
    __m128 xw_yz_zy_wx = _mm_and_ps( wzyx, temp3 );
    __m128 zy_wx_xw_yz = _mm_shuffle_ps( xw_yz_zy_wx, xw_yz_zy_wx, SHUFFLE( 2, 3, 0, 1 ) );
    return _mm_and_ps( xw_yz_zy_wx, zy_wx_xw_yz );
}

// accessors
ForceInline Vec4 Mat44::Row0() const {
    return m_r[0];
}

ForceInline Vec4 Mat44::Row1() const {
    return m_r[1];
}

ForceInline Vec4 Mat44::Row2() const {
    return m_r[2];
}

ForceInline Vec4 Mat44::Row3() const {
    return m_r[3];
}

ForceInline Vec4 Mat44::Row( int32_t i ) const {
    return m_r[i];
}

ForceInline Scalar Mat44::Elem( int32_t r, int32_t c ) const {
    return Row( r ).GetElem( c );
}

ForceInline void Mat44::SetRow0( Vec4 const &r0 ) {
    m_r[0] = r0.m_value;
}

ForceInline void Mat44::SetRow1( Vec4 const &r1 ) {
    m_r[1] = r1.m_value;
}

ForceInline void Mat44::SetRow2( Vec4 const &r2 ) {
    m_r[2] = r2.m_value;
}

ForceInline void Mat44::SetRow3( Vec4 const &r3 ) {
    m_r[3] = r3.m_value;
}

ForceInline void Mat44::SetRow( int32_t i, Vec4 const &r ) {
    m_r[i] = r.m_value;
}

ForceInline void Mat44::SetElem( int32_t r, int32_t c, Scalar const &s ) {
    Vec4 row = Row( r );
    row.SetElem( c, s );
    SetRow( r, row );
}

// misc
ForceInline Mat44 Transpose( Mat44 const &m ) {
    Mat44 result( m );
    _MM_TRANSPOSE4_PS( result.m_r[0], result.m_r[1], result.m_r[2], result.m_r[3] );
    return result;
}

ForceInline Mat44 Abs( Mat44 const &m ) {
    __m128 mask = _mm_set_ps1( union_cast<float>( 0x7fffffff ) );
    return Mat44( _mm_and_ps( m.m_r[0], mask ),
                  _mm_and_ps( m.m_r[1], mask ),
                  _mm_and_ps( m.m_r[2], mask ),
                  _mm_and_ps( m.m_r[3], mask ) );
}

ForceInline Mat44 Inverse( Mat44 const &m, Scalar *determinant ) {
    // warning: Inverse( Mat44::Identity() ) does NOT return exactly an identity matrix
    // returns determinant of 0 if the matrix is uninvertable. the matrix returned will probably have non-numeric values (INF)

    // based on Cramer's rule and code from an Intel paper called
    // "Streaming SIMD Extensions - Inverse of 4x4 Matrix"

    __m128 minor0, minor1, minor2, minor3;
    __m128 row0, row1, row2, row3;
    __m128 det, tmp1;

    // reorder the original matrix to
    // Mat44( 00, 10, 20, 30,
    //        21, 31, 01, 11, 
    //        02, 12, 22, 32,
    //        23, 33, 03, 13 );
    // which is not transpose like it says in the paper
    tmp1 = _mm_shuffle_ps( m.m_r[0], m.m_r[1], SHUFFLE( 0, 1, 0, 1 ) );
    row1 = _mm_shuffle_ps( m.m_r[2], m.m_r[3], SHUFFLE( 0, 1, 0, 1 ) );
    row0 = _mm_shuffle_ps( tmp1, row1, SHUFFLE( 0, 2, 0, 2 ) );
    row1 = _mm_shuffle_ps( row1, tmp1, SHUFFLE( 1, 3, 1, 3 ) );
    tmp1 = _mm_shuffle_ps( m.m_r[0], m.m_r[1], SHUFFLE( 2, 3, 2, 3 ) );
    row3 = _mm_shuffle_ps( m.m_r[2], m.m_r[3], SHUFFLE( 2, 3, 2, 3 ) );
    row2 = _mm_shuffle_ps( tmp1, row3, SHUFFLE( 0, 2, 0, 2 ) );
    row3 = _mm_shuffle_ps( row3, tmp1, SHUFFLE( 1, 3, 1, 3 ) );

    // calculate cofactors
    tmp1   = _mm_mul_ps( row2, row3 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    minor0 = _mm_mul_ps( row1, tmp1);
    minor1 = _mm_mul_ps( row0, tmp1);                             
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor0 = _mm_sub_ps( _mm_mul_ps( row1, tmp1 ), minor0 );
    minor1 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor1 );
    minor1 = _mm_shuffle_ps( minor1, minor1, SHUFFLE( 2, 3, 0, 1 ) );

    tmp1   = _mm_mul_ps( row1, row2 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    minor0 = _mm_add_ps( _mm_mul_ps(row3, tmp1), minor0 );
    minor3 = _mm_mul_ps( row0, tmp1 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor0 = _mm_sub_ps( minor0, _mm_mul_ps( row3, tmp1 ) );
    minor3 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor3 );
    minor3 = _mm_shuffle_ps( minor3, minor3, SHUFFLE( 2, 3, 0, 1 ) );

    tmp1   = _mm_mul_ps( _mm_shuffle_ps( row1, row1, SHUFFLE( 2, 3, 0, 1 ) ), row3 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    row2   = _mm_shuffle_ps( row2, row2, SHUFFLE( 2, 3, 0, 1 ) );
    minor0 = _mm_add_ps( _mm_mul_ps( row2, tmp1 ), minor0 );
    minor2 = _mm_mul_ps( row0, tmp1 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor0 = _mm_sub_ps( minor0, _mm_mul_ps( row2, tmp1 ) );
    minor2 = _mm_sub_ps( _mm_mul_ps( row0, tmp1 ), minor2 );
    minor2 = _mm_shuffle_ps( minor2, minor2, SHUFFLE( 2, 3, 0, 1 ) );

    tmp1   = _mm_mul_ps( row0, row1 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    minor2 = _mm_add_ps( _mm_mul_ps( row3, tmp1 ), minor2 );
    minor3 = _mm_sub_ps( _mm_mul_ps( row2, tmp1 ), minor3 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor2 = _mm_sub_ps( _mm_mul_ps( row3, tmp1 ), minor2 );
    minor3 = _mm_sub_ps( minor3, _mm_mul_ps( row2, tmp1 ) );

    tmp1   = _mm_mul_ps( row0, row3 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    minor1 = _mm_sub_ps( minor1, _mm_mul_ps( row2, tmp1 ) );
    minor2 = _mm_add_ps( _mm_mul_ps( row1, tmp1 ), minor2 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor1 = _mm_add_ps( _mm_mul_ps( row2, tmp1 ), minor1 );
    minor2 = _mm_sub_ps( minor2, _mm_mul_ps( row1, tmp1 ) );

    tmp1   = _mm_mul_ps( row0, row2 );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 1, 0, 3, 2 ) );
    minor1 = _mm_add_ps( _mm_mul_ps( row3, tmp1 ), minor1 );
    minor3 = _mm_sub_ps( minor3, _mm_mul_ps( row1, tmp1 ) );
    tmp1   = _mm_shuffle_ps( tmp1, tmp1, SHUFFLE( 2, 3, 0, 1 ) );
    minor1 = _mm_sub_ps( minor1, _mm_mul_ps( row3, tmp1 ) );
    minor3 = _mm_add_ps( _mm_mul_ps( row1, tmp1 ), minor3 );

    // calculate the determinate
    det = _mm_mul_ps( row0, minor0 );
    det = _mm_add_ps( _mm_shuffle_ps( det, det, SHUFFLE( 2, 3, 0, 1 ) ), det );
    det = _mm_add_ss( _mm_shuffle_ps( det, det, SHUFFLE( 1, 0, 3, 2 ) ), det );
    tmp1 = _mm_rcp_ss( det );
    det = _mm_sub_ss( _mm_add_ss( tmp1, tmp1 ), _mm_mul_ss( det, _mm_mul_ss( tmp1, tmp1 ) ) );
    det = _mm_shuffle_ps( det, det, SHUFFLE( 0, 0, 0, 0 ) );

    // multiply cofactors by 1/determinate
    minor0 = _mm_mul_ps( det, minor0 );
    minor1 = _mm_mul_ps( det, minor1 );
    minor2 = _mm_mul_ps( det, minor2 );
    minor3 = _mm_mul_ps( det, minor3 );

    if( determinant ) {
        *determinant = det;
        
        float d = union_cast<float>( _mm_extract_ps( det, 0 ) );
        if( IsNonNumber( d ) || AlmostEqual( d, Scalar::Zero() ) ) {
            // uninvertable matrix
            *determinant = _mm_setzero_ps();
        }
    }

    return Mat44( minor0, minor1, minor2, minor3 );
}

// transformation matrices
ForceInline Mat44 Translation( Scalar const &tx, Scalar const &ty, Scalar const &tz ) {
    /* Mat44( 1,  0,  0,  0,
              0,  1,  0,  0,
              0,  0,  1,  0,
              tx, ty, tz, 1 ); */

    Vec4 row3 = Vec4::WAxis();
    row3.SetXYZ( tx, ty, tz );

    return Mat44( Vec4::XAxis(),
                  Vec4::YAxis(),
                  Vec4::ZAxis(),
                  row3 );
}

ForceInline Mat44 Translation( Vec4 const &t ) {
    /* Mat44( 1,  0,  0,  0,
              0,  1,  0,  0,
              0,  0,  1,  0,
              tx, ty, tz, 1 ); */

    Vec4 row3 = t;
    row3.SetW( 1.0f );

    return Mat44( Vec4::XAxis(),
                  Vec4::YAxis(),
                  Vec4::ZAxis(),
                  row3 );
}

ForceInline Mat44 RotationX( Scalar const &angle ) {
    /* Mat44( 1,  0,  0,  0,
              0,  c,  s,  0,
              0, -s,  c,  0,
              0,  0,  0,  1 ); */

    Scalar s, c;
    SinCos( angle, &s, &c );
    
    Vec4 row1 = Vec4::Zero();
    row1.SetY( c );
    row1.SetZ( s );

    Vec4 row2 = Vec4::Zero();
    row2.SetY( -s );
    row2.SetZ( c );

    return Mat44( Vec4::XAxis(),
                  row1,
                  row2,
                  Vec4::WAxis() );
}

ForceInline Mat44 RotationY( Scalar const &angle ) {
    /* Mat44( c,  0, -s,  0,
              0,  1,  0,  0,
              s,  0,  c,  0,
              0,  0,  0,  1 ) }; */

    Scalar s, c;
    SinCos( angle, &s, &c );

    Vec4 row0 = Vec4::Zero();
    row0.SetX( c );
    row0.SetZ( -s );

    Vec4 row2 = Vec4::Zero();
    row2.SetX( s );
    row2.SetZ( c );

    return Mat44( row0,
                  Vec4::YAxis(),
                  row2,
                  Vec4::WAxis() );
}

ForceInline Mat44 RotationZ( Scalar const &angle ) {
    /* Mat44(  c,  s,  0,  0,
              -s,  c,  0,  0,
               0,  0,  1,  0,
               0,  0,  0,  1 ); */

    Scalar s, c;
    SinCos( angle, &s, &c );

    Vec4 row0 = Vec4::Zero();
    row0.SetX( c );
    row0.SetY( s );

    Vec4 row1 = Vec4::Zero();
    row1.SetX( -s );
    row1.SetY( c );

    return Mat44( row0,
                  row1,
                  Vec4::ZAxis(),
                  Vec4::WAxis() );
}

ForceInline Mat44 RotationYawPitchRoll( Scalar const &yaw, Scalar const &pitch, Scalar const &roll ) {
    return RotationZ( roll ) * RotationX( pitch ) * RotationY( yaw );
}

ForceInline Mat44 RotationAxisAngle( Vec4 const &axis, Scalar const &angle ) {
    /* Mat44( t * x * x + c,     t * x * y + s * z, t * x * z - s * y, 0,
              t * x * y - s * z, t * y * y + c,     t * y * z + s * x, 0,
              t * x * z + s * y, t * y * z - s * x, t * z * z + c,     0,
              0,                 0,                 0,                 1 ); */

    Scalar s, c;
    SinCos( angle, &s, &c );
    Scalar t = 1.0f - c;

    Vec4 normalizedAxis = Normalize( axis );

    Vec4 tAxis = t * normalizedAxis;
    Vec4 sAxis = s * normalizedAxis;
    Vec4 negSAxis = -sAxis;

    Vec4 txx_txy_txz_0 = tAxis * normalizedAxis.X();
    Vec4 tyx_tyy_tyz_0 = tAxis * normalizedAxis.Y();
    Vec4 tzx_tzy_tzz_0 = tAxis * normalizedAxis.Z();

    Scalar zero = Scalar::Zero();
    Vec4 temp0( c, sAxis.Z(), negSAxis.Y(), zero );
    Vec4 temp1( negSAxis.Z(), c, sAxis.X(), zero );
    Vec4 temp2( sAxis.Y(), negSAxis.X(), c, zero );

    return Mat44( txx_txy_txz_0 + temp0,
                  tyx_tyy_tyz_0 + temp1,
                  tzx_tzy_tzz_0 + temp2,
                  Vec4::WAxis() );
}

ForceInline Mat44 Scaling( Scalar const &s ) {
    /* Mat44( s, 0, 0, 0,
              0, s, 0, 0,
              0, 0, s, 0,
              0, 0, 0, 1 ) */

    return Scaling( s, s, s );
}

ForceInline Mat44 Scaling( Scalar const &sx, Scalar const &sy, Scalar const &sz ) {
    /* Mat44( sx,  0,  0, 0,
               0, sy,  0, 0,
               0,  0, sz, 0,
               0,  0,  0, 1 ) */

    __m128 zero = _mm_setzero_ps();
    return Mat44( _mm_blend_ps( zero, sx.m_value, BLEND( 1, 0, 0, 0 ) ),
                  _mm_blend_ps( zero, sy.m_value, BLEND( 0, 1, 0, 0 ) ),
                  _mm_blend_ps( zero, sz.m_value, BLEND( 0, 0, 1, 0 ) ),
                  Vec4::WAxis().m_value );
}

ForceInline Mat44 LookAtRH( Vec4 const &eye, Vec4 const &at, Vec4 const &up ) {
    /* Mat44( xAxis.x,            yAxis.x,            zAxis.x,            0,
              xAxis.y,            yAxis.y,            zAxis.y,            0,
              xAxis.z,            yAxis.z,            zAxis.z,            0,
              -Dot( xAxis, eye ), -Dot( yAxis, eye ), -Dot( zAxis, eye ), 1 ); */

    Vec4 zAxis = Normalize( eye - at );
    Vec4 xAxis = Normalize( Cross( up, zAxis ) );
    Vec4 yAxis = Cross( zAxis, xAxis );

    xAxis.SetW( -Dot( xAxis, eye ) );
    yAxis.SetW( -Dot( yAxis, eye ) );
    zAxis.SetW( -Dot( zAxis, eye ) );
    return Transpose( Mat44( xAxis, yAxis, zAxis, Vec4::WAxis() ) );
}
 
// projection matrices
ForceInline Mat44 OrthographicRH( Scalar const &width, Scalar const &height, Scalar const &zNear, Scalar const &zFar ) {
    /*  Mat44( 2 / width, 0,          0,                        0,
               0,         2 / height, 0,                        0,
               0,         0,          1 / ( zNear - zFar ),     0,
               0,         0,          zNear / ( zNear - zFar ), 1 ); */

    return Mat44( 2.0f / width, 0.0f,          0.0f,                     0.0f,
                  0.0f,         2.0f / height, 0.0f,                     0.0f,
                  0.0f,         0.0f,          1.0f / ( zNear - zFar ),  0.0f,
                  0.0f,         0.0f,          zNear / ( zNear - zFar ), 1.0f );
}

ForceInline Mat44 PerspectiveFovRH( Scalar const &fov, Scalar const &aspectRatio, Scalar const &zNear, Scalar const &zFar ) {
    /* Mat44( xScale, 0,      0,                                0,
              0,      yScale, 0,                                0,
              0,      0,      zFar / ( zNear - zFar ),         -1,
              0,      0,      zNear * zFar / ( zNear - zFar ),  0); */
    
    float yScale = 1.0f / Tan( fov * Scalar( 0.5f ) );
    float xScale = yScale / aspectRatio;

    return Mat44( xScale, 0.0f,   0.0f,                             0.0f,
                  0.0f,   yScale, 0.0f,                             0.0f,
                  0.0f,   0.0f,   zFar / ( zNear - zFar ),         -1.0f,
                  0.0f,   0.0f,   zNear * zFar / ( zNear - zFar ),  0.0f );
}
