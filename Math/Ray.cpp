#include "Math/Ray.h"

Ray::Ray() :
    m_mint( 0.0f ),
    m_maxt( kInfinity ),
    m_time( 0.0f ),
    m_depth( 0 ) {
}

Ray::Ray( Vec4 const &origin, Vec4 const &direction, float start, float end, float t, int d ) :
    m_origin( origin ),
    m_direction( direction ),
    m_mint( start ),
    m_maxt( end ),
    m_time( t ),
    m_depth( d )  {
}

Ray::Ray( Vec4 const &origin, Vec4 const &direction, Ray const &parent, float start, float end ) :
    m_origin( origin ),
    m_direction( direction ),
    m_mint( start ),
    m_maxt( end ),
    m_time( parent.m_time ),
    m_depth( parent.m_depth + 1 )  {
}

Ray& Ray::operator*=( Transform const &t ) {
    m_origin *= t;
    m_direction *= t;
    return *this;
}

Ray Ray::operator*( Transform const &t ) const {
    Ray copy( *this );
    return copy *= t;
}

Vec4 Ray::Point( float t ) const {
    return m_origin + m_direction * t;
}

