#include "Math/RayDifferential.h"

RayDifferential::RayDifferential() :
    Ray(),
    m_hasDifferentials( false ) {
}

RayDifferential::RayDifferential( Vec4 const &origin, Vec4 const &direction, Scalar const &start, Scalar const &end, Scalar const &t, int d ) :
    Ray( origin, direction, start, end, t, d ),
    m_hasDifferentials( false ) {
}

RayDifferential::RayDifferential( Vec4 const &origin, Vec4 const &direction, Ray const &parent, Scalar const &start, Scalar const &end ) :
    Ray( origin, direction, parent, start, end ),
    m_hasDifferentials( false ) {
}

RayDifferential::RayDifferential( Ray const &ray ) :
    Ray( ray ),
    m_hasDifferentials( false ) {
}

void RayDifferential::ScaleDifferentials( Scalar const &s ) {
    m_rxOrigin    = m_origin    + ( m_rxOrigin    - m_origin    ) * s;
    m_rxDirection = m_direction + ( m_rxDirection - m_direction ) * s;
    m_ryOrigin    = m_origin    + ( m_ryOrigin    - m_origin    ) * s;
    m_ryDirection = m_direction + ( m_ryDirection - m_direction ) * s;
}