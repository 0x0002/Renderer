#include "Geometry/DifferentialGeometry.h"

DifferentialGeometry::DifferentialGeometry() {

}

DifferentialGeometry::DifferentialGeometry( Handle<Shape> const &shape,
                                            Vec4 const &p,
                                            Vec4 const &dpdu, Vec4 const &dpdv,
                                            Normal const &dndu, Normal const &dndv,
                                            float u, float v ) :
    m_shape( shape ),
    m_p( p ),
    m_dpdu( dpdu ), m_dpdv( dpdv ),
    m_dndu( dndu ), m_dndv( dndv ),
    m_u( u ), m_v( v ) {
    m_n = Normal( Normalize( Cross( dpdu, dpdv ) ) );
}