
#include "Math/Math.h"
#include "Container/String.h"
#include "Container/List.h"
#include "Container/Vector.h"
#include "Core/Print.h"
#include "Core/MemoryManager.h"

#include "Component/ComponentManager.h"
#include "Component/ComponentIncludes.h"
#include "Component/ComponentTypes.h"
#include "Component/Handle.h"


#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <memory>

class A {
public:
    A() {
        int asdf = 0;
    }

    A( int i ) : m_i( i ) {
        int asdf = 0;
    }

    ~A() {
        int asdf = 0;
    }

    A( A const &a ) : m_i( a.m_i ) {
        int asdf = 0;
    }

    A& operator=( A const &a ) {
        m_i = a.m_i;
        int asdf = 0;
        return *this;
    }

    A( A const &&a ) {
        int asdf = 0;
    }



    operator int() const { return m_i; }

    virtual char const* Value() const { return "A"; }

private:
    int m_i;
};

class B : public A {
public:
    virtual char const* Value() const { return "B"; }
};

class C : public A {
    virtual char const* Value() const { return "C"; }
};

template class List<A>;
template class Vector<A>;

int main() {
#if 0
    Vec4 a( 1.0f, 2.0f, 3.0f, 4.0f );

    // vec4 constructors
    {
        Vec4 a;
        Vec4 b( 1.0f, 2.0f, 3.0f, 4.0f );
        Vec4 c( Scalar( 5.0f ), Scalar( 6.0f ), Scalar( 7.0f ), Scalar( 8.0f ) );
        Vec4 zero = Vec4::ZeroVector();
        Vec4 point = Vec4::ZeroPoint();
        Vec4 xAxis = Vec4::XAxis();
        Vec4 yAxis = Vec4::YAxis();
        Vec4 zAxis = Vec4::ZAxis();
        Vec4 d = b;
        Vec4 e = Vec4( 10.0f, 9.0f, 8.0f, 7.0f );

        int asdf = 0;
    }

    // vec4 assignment operators
    {
        Vec4 a( -2.0f, -1.0f, 0.0f, 4.0f );
        Vec4 b( 10.5f, 4.0f, 2.0f, -19.8f );

        a += b;
        a -= b;

        a *= b;
        b *= 2.0f;
        a /= -4.0f;

        int asdf = 0;
    }

    // vec4 unary operators
    {
        Vec4 a( -2.0f, -1.0f, 0.0f, 4.0f );
        Vec4 b( 10.5f, 4.0f, 2.0f, -19.8f );

        Vec4 c = +a;
        Vec4 d = -b;

        int asdf = 0;
    }

    // vec4 binary operators
    {
        Vec4 a( -2.0f, -1.0f, 0.0f, 4.0f );
        Vec4 b( 10.5f, 4.0f, 2.0f, -19.8f );

        Vec4 c = a + b;
        Vec4 d = a - b;
        Vec4 e = b - a;
        Vec4 f = a * b;
        Vec4 g = b * a;
        Vec4 h = a * 5.0f;
        Vec4 i = a / 2.5f;
        Vec4 j = 2.0f * b;

        int asdf = 0;
    }

    // vec4 comparison operators
    {
        Vec4 a( 1.0f, -2.0f, 3.0f, 6.0f );
        Vec4 b( 1.0f, 0.0f, 0.0f, 0.0f );
        Vec4 c( 0.0f, -2.0f, 0.0f, 0.0f );
        Vec4 d( 1.0f, 0.0f, 3.0f, 0.0f );
        Vec4 e( 0.0f, 0.0f, 3.0f, 6.0f );

        Bool f = a == b;
        Bool g = a == c;
        Bool h = a == d;
        Bool i = a == e;


        bool j = f;
        bool k = g;
        bool l = h;
        bool m = i;

        e = a;
        Bool n = e == a;
        bool o = n;

        float nan = Math::NaN();
        float inf = Math::Inf();

        bool isNan = Math::IsNaN( nan );
        bool isNan2 = Math::IsNaN( inf );

        bool isInf = Math::IsInf( nan );
        bool isInf2 = Math::IsInf( inf );

        bool isNumber = Math::IsNonNumber( nan );
        bool isNumber2 = Math::IsNonNumber( inf );

        double dnan = union_cast<double>( 0x7fff000000000000 );
        double dinf = union_cast<double>( 0x7fff000000000001 );

        bool aaa = Math::IsNaN( dnan );
        bool bbb = Math::IsInf( dnan );
        bool ccc = Math::IsNaN( inf );
        bool ddd = Math::IsInf( inf );

        int asdf = 0;
    }

    // vec4 accessors
    {
        Vec4 a( 1.0f, 2.0f, 3.0f, 4.0f );
        Scalar x = a.X();
        Scalar y = a.Y();
        Scalar z = a.Z();
        Scalar w = a.W();

        float b[3];
        a.XYZ( b );

        float c[4];
        a.XYZW( c );

        Scalar d = a.GetElem( 0 );
        Scalar e = a.GetElem( 1 );
        Scalar f = a.GetElem( 2 );
        Scalar g = a.GetElem( 3 );

        a.SetX( -1.0f );
        a.SetY( -2.0f );
        a.SetZ( -3.0f );
        a.SetW( -4.0f );
        a.SetXYZ( 10.0f, 20.0f, 30.0f );
        a.SetElem( 0, -10.0f );
        a.SetElem( 1, -20.0f );
        a.SetElem( 2, -30.0f );
        a.SetElem( 3, 1.0f );

        int asdf = 0;
    }

    // vec4 misc
    {
        Vec4 a( 1.0f, 2.0f, 3.0f, 4.0f );
        Vec4 b( 5.0f, 6.0f, 7.0f, 8.0f );

        Vec4 c = Normalize( a );
        Scalar length = Length( a );
        Scalar rcpLength = RcpLength( a );
        Scalar lengthSquared = LengthSquared( a );
        Scalar dot = Dot( a, b );
        Scalar dot2 = Dot( b, a );
        Scalar dot3 = Dot3( a, b );
        Scalar dot32 = Dot3( b, a );

        Vec4 x = Vec4::XAxis();
        Vec4 y = Vec4::YAxis();
        Vec4 z = Vec4::ZAxis();

        Vec4 xCrossY = Cross( x, y );
        Vec4 yCrossX = Cross( y, x );
        Vec4 yCrossZ = Cross( y, z );
        Vec4 zCrossY = Cross( z, y );
        Vec4 zCrossX = Cross( z, x );
        Vec4 xCrossZ = Cross( x, z );



        int asdf = 0;
    }
#endif

#if 0
    static float const f[16] = {  1.0f,  2.0f,  3.0f,  4.0f, 
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f };

    // mat44 constructors
    {
       Mat44 a;
       Mat44 b( f );
       Mat44 c( f[0],  f[1],  f[2],  f[3],
                f[4],  f[5],  f[6],  f[7],
                f[8],  f[9],  f[10], f[11],
                f[12], f[13], f[14], f[15] );
       Mat44 e( Vec4( f[0],  f[1],  f[2],  f[3] ),
                Vec4( f[4],  f[5],  f[6],  f[7] ),
                Vec4( f[8],  f[9],  f[10], f[11] ),
                Vec4( f[12], f[13], f[14], f[15] ) );

       Mat44 i = Mat44::Identity();
       Mat44 zero = Mat44::Zero();

       int asdf = 0;
    }

    // mat44 assignment operators
    {
        Mat44 a( f );
        Mat44 b( f );
        a *= b;
        Mat44 c = a += b;
        a -= b;
        a *= 2.0f;;
        a /= 2.0f;

        int asdf = 0;
    }

    // mat44 unary operators
    {
        Mat44 a( f );
        Mat44 b = +a;
        Mat44 c = -a;

        int asdf = 0;
    }

    // mat44 binary operators
    {
        Mat44 a( f );
        Mat44 b( f );

        Mat44 c = a + b;
        Mat44 d = a - b;
        Mat44 e = a * b;
        Mat44 g = a * 2.0f;
        Mat44 h = b / 2.0f;
        Mat44 i = 2.0f * a;

        int asdf = 0;
    }

    // mat44 comparison operators
    {
        Mat44 a( f );
        Mat44 b( f );
        Mat44 c = b * 1.1f;
        Mat44 asdf3( a );
        asdf3.SetElem( 0, 0, 3.0f );

        Bool d = a == b;
        Bool e = a == c;
        bool asdf2 = asdf3 == a;
            
        bool g = d;
        bool asdfasdf = asdf2;

        int asdf = 0;
    }

    // mat44 accessors
    {
        Mat44 a( f );
        Vec4 r0 = a.Row0();
        Vec4 r1 = a.Row1();
        Vec4 r2 = a.Row2();
        Vec4 r3 = a.Row3();
        r0 = a.Row( 3 );
        r1 = a.Row( 2 );
        r2 = a.Row( 1 );
        r3 = a.Row( 0 );

        float f2[16];
        for( int i = 0; i < 16; ++i ) {
            f2[i] = a.Elem( i / 4, i % 4 );
        }

        Vec4 x = Vec4::XAxis();
        Vec4 y = Vec4::YAxis();
        Vec4 z = Vec4::ZAxis();
        Vec4 w = Vec4::WAxis();

        a.SetRow0( x );
        a.SetRow1( y );
        a.SetRow2( z );
        a.SetRow3( w );

        a.SetRow( 2, Vec4::Zero() );

        for( int i = 0; i < 16; ++i ) {
            a.SetElem( i / 4, i % 4, i );
        }

        int asdf = 0;
    }

    // mat44 misc
    {
        Mat44 a( f );
        Mat44 b = Transpose( a );
        Mat44 c = Abs( -a );

        Scalar det;
        Mat44 inva = Inverse( a, &det );

        Mat44 inv = Inverse( Mat44::Identity(), &det );

        Mat44 t = Translation( 1.0f, 2.0f, 3.0f );
        Mat44 rx = RotationX( 0.6f );
        Mat44 ry = RotationY( 0.6f );
        Mat44 rz = RotationZ( 0.6f );
        Mat44 rypr = RotationYawPitchRoll( 0.6f, 1.0f, 1.4f );
        Mat44 rax = RotationAxisAngle( Vec4( 1.0f, 2.0f, 3.0f, 0.0f ), 0.6f );
        Mat44 s = Scaling( 1.0f, 2.0f, 3.0f );
        Mat44 la = LookAtRH( Vec4( 1.0f, 2.0f, 3.0f, 0.0f ), Vec4( -1.0f, -5.0f, 8.0f, 0.0f ), Vec4( 0, 1, 0, 0.0f ) );
        Mat44 o = OrthographicRH( 4.0f, 10.0f, 2.0f, 150.0f );
        Mat44 p = PerspectiveFovRH( 3.14159265358979323846f / 4.0f, 16.0f / 9.0f, 2.0f, 150.0f );

        Vec4 asdf3( 4.0f, 2.0f, -45.0f, 1.0f );
        Vec4 asdf2 = asdf3 * s * rax * la * p;

        int asdf = 0;
    }

    // quat constructors
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
        Quat b( Scalar( 1.0f ), Scalar( 2.0f ), Scalar( 3.0f ), Scalar( 4.0f ) );
        Quat c( RotationAxisAngle( Vec4( 1.0f, 2.0f, 3.0f, 0.0f ), 2.0f ) );
        Quat d( RotationX( kPiBy2 ) );
        Quat e = QuatRotationAxisAngle( Vec4::XAxis(), kPiBy2 ); 
        Quat f = QuatRotationAxisAngle( -Vec4::XAxis(), kPiBy2 );

        int asdf = 0;
    }

    // quat assignment operators
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
        Quat b( Scalar( 1.0f ), Scalar( 2.0f ), Scalar( 3.0f ), Scalar( 4.0f ) );

        Quat c = a += b;
        Quat d = c -= b;
        Quat e = a *= b;
        Quat f = c *= d;

        Scalar s = Scalar( 1.0f ) * 2.0f;
        Scalar s2 = 2.0f * Scalar( 2.0f );

        int asdf = 0;
    }

    // quat unary operators
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
        Quat b( Scalar( 1.0f ), Scalar( 2.0f ), Scalar( 3.0f ), Scalar( 4.0f ) );
        Quat c = +a;
        Quat d = -b;

        int asdf = 0;
    }

    // quat binary operators
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
        Quat b( Scalar( 1.0f ), Scalar( 2.0f ), Scalar( 3.0f ), Scalar( 4.0f ) );

        Quat c = a + b;
        Quat d = c - b;
        Quat e = a * b;
        Quat f = c * d;

        Quat g = a * 2.0f;
        Quat h = b / 2.0f;

        int asdf = 0;
    }

    // quat comparison operators
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );
        Quat b( Scalar( 3.0f ), Scalar( 2.0f ), Scalar( 3.0f ), Scalar( 4.0f ) );
        Bool c = a == a;
        Bool d = a != b;
        Bool e = a != a;
    }

    // quat accessors
    {
        Quat a( 1.0f, 2.0f, 3.0f, 4.0f );

        float x = a.X();
        float y = a.Y();
        float z = a.Z();
        float w = a.W();
        float f[4];
        a.XYZW( f );
        x = a.GetElem( 0 );
        y = a.GetElem( 1 );
        z = a.GetElem( 2 );
        w = a.GetElem( 3 );

        a.SetX( -3.0f );
        a.SetY( -5.0f );
        a.SetZ( -10.0f );
        a.SetW( -20.0f );
        a.SetElem( 0, 50.0f );
        a.SetElem( 1, 60.0f );
        a.SetElem( 2, 70.0f );
        a.SetElem( 3, 90.0f );

        int asdf = 0;
    }

    // quat misc
    {
        Quat a = QuatRotationAxisAngle( Vec4( 1, 0, 0, 4 ), kPiBy2 );
        Quat b = QuatRotationYawPitchRoll( 1, 2, 3 );

        Quat r = QuatRotationAxisAngle( Vec4::XAxis(), -kPiBy2 );
        Quat r2 = QuatRotationAxisAngle( Vec4::YAxis(), kPiBy2 );
        Vec4 v = Vec4( 0, 2, 0, 0.0f );
        v *= r;
        Vec4 v2 = v * (r * r2);

        int asdf = 0;
    }

#endif
    
#if 0
    // string
    {
        String a;
        String b = "string b";
        String const c = b;
        String d( a );

        String e = b + c;
        e += e;

        std::string::iterator it2;
        
        std::map<int, int> m;
        std::map<int, int>::iterator it3;
        

        String::iterator it = b.begin();
        for( ; it != b.end(); ++it ) {
            char temp = *it;

            int asdf = 0;
        }

        for( char c : b ) {
            PrintLine( "%c", c );
        }

        auto result = std::find( b.begin() + 5, b.end(), 'r' );

        int asdf = 0;
    }

    // list
    {
#if 0
        std::list<int> l;
        l.cbegin();

        List<A> a( 4 );

        a.PushBack( 1 );
        a.PushBack( 2 );
        a.PushBack( 3 );
        a.PushFront( 4 );

        for( int i : a ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        a.PushFront( 5 );

        auto it = a.begin();
        ++it;
        ++it;

        a.Insert( it, 100 );


        List<A>::const_iterator iter = a.begin();
        for( ; iter != a.end(); ++iter ) {
            int i = *iter;
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        a.PopFront();
        a.PopBack();
        it = a.begin();
        ++it;
        a.Erase( it );

        for( int i : a ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        a.PopFront();
        a.PopFront();
        a.PopFront();
        
        //List<A> asdf2222( 0xffff );

        bool empty = a.Empty();

        for( int i = 0; i < 150; ++i ) {
            a.PushFront( i );
        }

        for( int i : a ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        //A asdf;
        int asdf = 0;

#endif

        List<A*> list( 2 );

        list.PushBack( new A() );
        list.PushBack( new B() );
        list.PushBack( new C() );

        PrintLineConsole( "" );
        for( A const *a : list )
            PrintLineConsole( "%s", a->Value() );

        List<A*> list2( list );
        PrintLineConsole( "" );
        for( A const *a : list2 )
            PrintLineConsole( "%s", a->Value() );

        List<A*> list3;
        list3 = list2;
        PrintLineConsole( "" );
        for( A const *a : list3 )
            PrintLineConsole( "%s", a->Value() );

        std::for_each( list.begin(), list.end(), std::default_delete<A>() );
    }
#endif

#if 0
    {
        A *a0 = new A();
        A *a1 = new A[10];

        int asdf = 0;
    }
#endif

    // initialize
    g_memoryManager.Initialize();
    g_componentManager.Initialize();
    g_memoryManager.SetHeapAllocator();

    for( ComponentBase *b : g_componentManager.AllComponents<ComponentBase>() ) {

    }

    ComponentMultiTypeConstIterator<ComponentBase> it = g_componentManager.AllComponents<ComponentBase>().begin();
    while( it != g_componentManager.AllComponents<ComponentBase>().end() ) {
        ComponentBase const *b = *it;


        ++it;
    }

    for( ComponentType1 const *t1 : g_componentManager.AllComponents<ComponentType1>() ) {

    }

    for( ComponentType2 const *t2 : Components<ComponentType2>() ) {

    }

    List<UntypedHandle>::iterator bn = g_componentManager.Create( Component::kComponentBase );
    Handle<ComponentBase> b = *bn;

    List<UntypedHandle>::iterator c1n = g_componentManager.Create( Component::kComponentType1 );
    Handle<ComponentType1> c1 = *c1n;

    List<UntypedHandle>::iterator c2n = g_componentManager.Create( Component::kComponentType2 );
    Handle<ComponentType2> c2 = *c2n;

    ComponentBase *base = *b;
    g_componentManager.Destroy( bn );
    base = *b;

    for( ComponentBase *c : AllComponents<ComponentBase>() ) {
        c->Initialize();
    }

    

    int asdf = 0;






#if 0
    // vector
    {
        Vector<int> v( 4 );
        v.PushBack( 0 );
        v.PushBack( 1 );
        v.PushBack( 2 );
        v.PushBack( 3 );

        for( int i : v ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        v.Reserve( 5 );

        v.PushBack( 4 );

        Vector<int>::const_iterator iter = v.begin();

        iter += 2;
        v.Erase( iter );

        PrintLineConsole( "" );
        for( int i : v ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        v.Erase( v.begin() );

        v.Erase( --v.end() );

        v.PopBack();
        v.PushBack(100);
        v.PopBack();
        v.PopBack();

        PrintLineConsole( "" );
        for( int i : v ) {
            PrintLineConsole( "%i", i );
            int asdf = 0;
        }

        //v.PopBack();

        int asdf = 0;
    }
#endif




    // deinitialize
    g_memoryManager.UnsetHeapAllocator();
    g_componentManager.Deinitialize();
    g_memoryManager.Deinitialize();
    return 0;
}