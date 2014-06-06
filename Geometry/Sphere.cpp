#include "Geometry/Sphere.h"
#include "Geometry/DifferentialGeometry.h"
#include "Math/Ray.h"

// f( x, y, z ) = 0
// x^2 + y^2 + z^2 - r^2 = 0

// f( theta, phi ), theta : [0, 2pi], phi : [0, pi]

// x = r * sin( phi ) * sin( theta )
// y = r * cos( phi )
// z = r * sin( phi ) * cos( theta )

// theta = atan2( x, z )
// phi = acos( y )

Component::Type const Sphere::kType = Component::kSphere;

bool Sphere::Intersect( Ray const &ray, float *tHit, float *epsilon, DifferentialGeometry *geom ) const {
    Transform tf = Tform();
    Ray r = ray * Inverse( tf );

    float t;
    if( !Intersect( ray, &t ) )
        return false;

    // compute differential geometry
    Vec4 p = ray.Point( t );

    float x = p.X();
    float y = p.Y();
    float z = p.Z();

    if( x == 0.0f && z == 0.0f ) {
        // can't have both atan2 arguments be zero
        z = kEpsilon * m_radius;
    }
    float theta = atan2( p.X(), p.Z() );

    if( theta < 0.0f ) {
        // remap theta to [0, 2pi] to match sphere's definition
        theta += k2Pi;
    }

    float phi = Acos( Clamp( z / m_radius, -1.0f, 1.0f ) );

    // parameterize sphere hit
    float u = theta * kInv2Pi;
    float v = phi * kInvPi;

    float sTheta, cTheta;
    float sPhi, cPhi;
    SinCos( theta, &sTheta, &cTheta );
    SinCos( phi, &sPhi, &cPhi );

    Vec4 dpdu( k2Pi * z, 0.0f, -k2Pi * x, 0.0f );
    Vec4 dpdv( kPi * y * sTheta, -kPi * m_radius * sPhi, kPi * y * cTheta, 0.0f );
    Vec4 d2pdu2( -k2Pi * k2Pi * x, 0.0f, -k2Pi * k2Pi * z, 0.0f );
    Vec4 d2pduv( k2Pi * kPi * y * cTheta, 0.0f, -k2Pi * kPi * y * sTheta, 0.0f );
    Vec4 d2pdv2( -kPi * kPi * x, -kPi * kPi * y, -kPi * kPi * z, 0.0f );

    // change in normal is computed using Weingarten equations
    Scalar E = Dot( dpdu, dpdu );
    Scalar F = Dot( dpdu, dpdv );
    Scalar G = Dot( dpdv, dpdv );
    Vec4 N = Normalize( Cross(  dpdu, dpdv ) );
    Scalar e = Dot( N, d2pdu2 );
    Scalar f = Dot( N, d2pduv );
    Scalar g = Dot( N, d2pdv2 );

    Scalar h = 1.0f / ( E * G - F * F );
    Vec4 dndu = ( f * F - e * G ) * h * dpdu + ( e * F - f * E ) * h * dpdv;
    Vec4 dndv = ( g * F - f * G ) * h * dpdu + ( f * F - g * E ) * h * dpdv;

    *tHit = t;
    *epsilon = 5e-4f * t;

    // return world space differential geometry
    *geom = DifferentialGeometry( Handle(), p * tf, dpdu * tf, dpdv * tf, Normal( dndu ) * tf, Normal( dndv ) * tf, u, v );

    return true;
}

bool Sphere::Intersect( Ray const &objSpaceRay, float *tHit ) const {
    Ray r = objSpaceRay;
    Scalar a = Dot3( r.m_direction, r.m_direction );
    Scalar b = 2.0f * Dot3( r.m_direction, r.m_origin );
    Scalar c = Dot3( r.m_origin, r.m_origin ) - m_radius * m_radius;

    Scalar t0, t1;
    if( !Quadratic( a, b, c, &t0, &t1 ) ) {
        // ray does not intersect sphere
        return false;
    }

    if( t0 > r.m_maxt || t1 < r.m_mint ) {
        // intersection is outside of ray range
        return false;
    }

    Scalar t = t0;
    if( t0 < r.m_mint ) {
        // t0 is out of range, try t1
        t = t1;
        if( t > r.m_maxt ) {
            // t1 is out of range
            return false;
        }
    }

    *tHit = t;
    return true;
}

void Sphere::GetShadingGeom( DifferentialGeometry const &intersectGeom, DifferentialGeometry *shadingGeom ) const {
    *shadingGeom = intersectGeom;
}

float Sphere::GetArea() const {
    float r = m_radius;
    return 4.0f * kPi * r * r;
}