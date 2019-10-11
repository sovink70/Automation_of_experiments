// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>

#include "segment3d.h"
#include "vector3d.h"
#include "plane3d.h"
#include "sphere3d.h"
#include "line3d.h"

//#include "algorithms.h"
#include "Testlib.h"

#include <random>

#include <tuple>

#include <cmath>
using namespace std;

template < class T >
tuple < bool, Vector<T>, T, Plane<T> > Intersection_of_spheres(Sphere<T>& sphere1, Sphere<T>& sphere2);
template < class T >
bool Intersection_of_planes(Plane<T>& plane1, Plane<T>& plane2);
template < class T >
Vector<T> Projection_of_point(Plane<T>& plane, Vector<T>& point);
template < class T >
T Distance_point_plane(Plane<T>& plane, Vector<T>& vector);
template < class T >
T Distances_point_line(Line<T>& line, Vector<T>& point);

template < class T >
tuple < bool, Vector<T>, T, Plane<T> > Intersection_of_spheres(Sphere<T>& sphere1, Sphere<T>& sphere2) {
    if ( ( (sphere1.get_Center() - sphere2.get_Center()).abs() < sphere1.get_R() + sphere2.get_R() ) && (sphere1.get_Center() - sphere2.get_Center()).abs() > fabs(sphere1.get_R() - sphere2.get_R()) ) {
        bool Index = true;
        T l = sqrt( ( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() )*( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() ) + ( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() )*( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() ) + ( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() )*( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() ) );
        T p = 0.5*(sphere1.get_R() + sphere2.get_R() + l); // для расчёта площади по формула Герона
        T R = 2/l*sqrt( p*(p-sphere1.get_R())*(p-sphere2.get_R())*(p-l) );
        Vector<T> normal = (sphere1.get_Center() - sphere2.get_Center()); // /((sphere1.get_Center() - sphere2.get_Center()).abs()); // вектор нормали НЕ единичный
        Vector<T> circle_Center = sphere1.get_Center() + normal*(sqrt(sphere1.get_R()*sphere1.get_R()-R*R)/( sphere1.get_Center() - sphere2.get_Center()).abs() );
        T D = -normal.get_x()*circle_Center.get_x() -normal.get_y()*circle_Center.get_y() -normal.get_z()*circle_Center.get_z();
        Plane<T> circle_Plane (normal.get_x(), normal.get_y(), normal.get_z(), D);
        return make_tuple(Index, circle_Center, R, circle_Plane);
    }
    else {
        bool Index = false;
        Vector<T> circle_Center;
        Plane<T> circle_Plane;
        return make_tuple(Index, circle_Center, 0, circle_Plane);
    }
}

template < class T >
bool Intersection_of_planes(Plane<T>& plane1, Plane<T>& plane2) {
    Vector<T> n1 (plane1.get_A(), plane1.get_B(), plane1.get_C());
    Vector<T> n2 (plane2.get_A(), plane2.get_B(), plane2.get_C());
    Vector<T> n1_n2=n1^n2;
    Vector<T> Null(0, 0, 0);
    if (n1_n2 == Null)
        return false;
    else return true;
}

template < class T >
Vector<T> Projection_of_point(Plane<T>& plane, Vector<T>& point) {
    Vector<T> Projection;
    if (plane.get_A() != 0) {
        Projection.set_x( -( plane.get_B()*plane.get_A()*plane.get_A()*point.get_y()+ plane.get_C()*plane.get_B()*plane.get_B()*point.get_z()- plane.get_C()*plane.get_C()*point.get_z()+ plane.get_B()*plane.get_C()*plane.get_D()+ plane.get_A()*plane.get_A()*point.get_z()+ plane.get_B()*plane.get_B()*point.get_z()+ plane.get_C()*plane.get_C()*point.get_z()+ plane.get_D()*plane.get_A()*plane.get_A()+ plane.get_C()*plane.get_D()*plane.get_D())/( plane.get_A() * (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) )   );
        Projection.set_y( ( (plane.get_C()*plane.get_C() + plane.get_A()*plane.get_A())*point.get_y() + point.get_z()*plane.get_B()*plane.get_C()- plane.get_D()*plane.get_B() ) / (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C())   );
        Projection.set_z( - (plane.get_B()*plane.get_C()*point.get_y() + plane.get_C()*point.get_z() - plane.get_D()*plane.get_C()) / (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) + point.get_z()   );
        return Projection;
    }
    else { //A ==0
        if (plane.get_B() != 0){
            Projection.set_x( point.get_x()   );
            Projection.set_z( (plane.get_B()*plane.get_B()*point.get_z() - plane.get_D()*plane.get_C()- point.get_y()*plane.get_B()*plane.get_C())/ (plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C())   );
            Projection.set_y( (-plane.get_C()*(plane.get_B()*plane.get_B()*point.get_z() - plane.get_D()*plane.get_C()- point.get_y()*plane.get_B()*plane.get_C())/(plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) - plane.get_D()  ) / plane.get_B()   );
        }
        else { //B ==0
            if (plane.get_C() == 0){
                cout<<"ERROR: impossible plane"<<endl;
            }
            else {//C !=0
                Projection.set_y(point.get_y());
                Projection.set_x(point.get_x()); //Projection._x = point._x;
                Projection.set_z( -plane.get_D()/plane.get_C() );
            }
        }
    }
    return Projection;
}

template < class T >
T Distance_point_plane(Plane<T>& plane, Vector<T>& vector) { //double
    return ( fabs(plane.get_A()*vector.get_x() + plane.get_B()*vector.get_y() + plane.get_C()*vector.get_z() +plane.get_D()) / plane.abs() ); // уточнить на cplusplus.com or cpp reeference, является ли шаблонным - cout << fabs(int(-3)) << endl; работает, так что всё норм //https://ru.onlinemschool.com/math/library/analytic_geometry/p_plane/
}

template < class T >
T Distances_point_line(Line<T>& line, Vector<T>& point) { //double
    Segment<T> M0M1(point, line.get_Point());

    return ( (M0M1.Shift()^line.get_Direction()).abs() / (line.get_Direction()).abs() ); //https://ru.onlinemschool.com/math/library/analytic_geometry/p_line/
}


void Test_Vector() {
    default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
    uniform_int_distribution<int> distribution(1,99);
    {
       int X = distribution(generator), Y = distribution(generator), Z = distribution(generator); //int x = rand(), y = rand();
       Vector <int> v(X, Y, Z);
       ASSERT_MSG( (v.get_x() == X) && (v.get_y() == Y) && (v.get_z() == Z), "Vector constructor works well");
    }
    {
       int X = distribution(generator), Y = distribution(generator), Z = distribution(generator); //int x = rand(), y = rand();
       Vector <int> v2(X, Y, Z);
       Vector <int> v1(X, Y, Z);
       ASSERT_MSG(v1 == v2, "Operator == works well");
    }
    {
        int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
        Vector <int> v1(x1, y1, z1);
        Vector <int> v2(x2, y2, z2);
        Vector <int> v3 = v1+v2;
       ASSERT_MSG( ( (v3.get_x() == x1+x2) && (v3.get_y() == y1+y2) && (v3.get_z() == z1+z2) ), "Operator + works well");
    }
    {
        int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
        Vector <int> v1(x1, y1, z1);
        Vector <int> v2(x2, y2, z2);
        Vector <int> v3 = v1-v2;
       ASSERT_MSG( ( (v3.get_x() == x1-x2) && (v3.get_y() == y1-y2) && (v3.get_z() == z1-z2) ), "Operator - works well");
    }
    {
        int h = distribution(generator);
        int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator);
        Vector <int> v1(x1, y1, z1);
        Vector <int> v2 = v1*h; //h строго справа
       ASSERT_MSG( ( (v2.get_x() == h*x1) && (v2.get_y() == h*y1) && (v2.get_z() == h*z1) ), "Operator *(const double &h) works well");
    }
    {
        int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
        Vector <int> v1(x1, y1, z1);
        Vector <int> v2(x2, y2, z2);
       ASSERT_MSG(v1*v2 == x1*x2+y1*y2+z1*z2, "Dot=Scalar product works well");
    }
    {
        int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
        Vector <int> v1(x1, y1, z1);
        Vector <int> v2(x2, y2, z2);
        Vector <int> v3 =v1^v2;
       ASSERT_MSG( ( (v3.get_x() == y1*z2-y2*z1) && (v3.get_y() == z1*x2-x1*z2) && (v3.get_z() == x1*y2-y1*x2) ), "Cross=Vector product works well");
    }
}

void Test_Segment() {
    default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
    uniform_int_distribution<int> distribution(1,99);
    {
       int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
       Vector <int> sp(x1, y1, z1);
       Vector <int> ep(x2, y2, z2);
       Segment<int> sgm(sp,ep);
       Vector <int> s1 = sgm.get_startPoint(); // потому что вот так ругается:        ASSERT_MSG( ( (sgm.get_startPoint() == sp) && (sgm.get_endPoint() == ep) ), "Segment equals to itself");
       Vector <int> s2 = sgm.get_endPoint();
       ASSERT_MSG( ( (s1 == sp) && (s2 == ep) ), "Segment equals to itself");
    }
    {
       int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
       Vector <int> sp(x1, y1, z1);
       Vector <int> ep(x2, y2, z2);
       Segment <int> sgm(sp,ep);
       Vector <int> v(x2-x1, y2-y1, z2-z1);
       //ASSERT_MSG( (sgm.Shift() == v), "Shift for Segment works well"); // - это он не кушает и ругается, потому что (ПОЧЕМУ_ТО) не знает о переропределении ==. ХОТЯ сверху и снизу он всё скушал
       ASSERT_MSG( ( (sgm.Shift().get_x() == v.get_x()) && (sgm.Shift().get_y() == v.get_y()) && (sgm.Shift().get_z() == v.get_z()) ), "Shift for Segment works well");
    }
}

void Test_Line() {
    {
       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
       uniform_int_distribution<int> distribution(1,99);
       int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
       Vector <int> p(x1, y1, z1);
       Vector <int> d(x2, y2, z2);
       Line <int> l(p, d);
       Vector <int> l1 = l.get_Point(); // аналогично ругается C:\1Work\GitHub\Automation_of_experiments\Geometry3D\main.cpp:97: ошибка: no match for 'operator==' (operand types are 'Vector<int>' and 'Vector<int>') ASSERT_MSG(l.get_Point() == p, "Line.Point equals to itself");
       Vector <int> l2 = l.get_Direction();
       ASSERT_MSG(l1 == p, "Line.Point equals to itself");
       ASSERT_MSG(l2 == d, "Line.Direction equals to itself");
    }
}

void Test_Plane() {
    {
       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
       uniform_int_distribution<int> distribution(1,99);
       int a = distribution(generator), b = distribution(generator), c = distribution(generator), d = distribution(generator);
       Plane <int> pl(a, b, c, d);
       ASSERT_MSG( ( (pl.get_A() == a) && (pl.get_B() == b) && (pl.get_C() == c) && (pl.get_D() == d) ), "Plane equals to itself");
    }
}

void Test_Sphere() {
    {
       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
       uniform_int_distribution<int> distribution(1,99);
       int X = distribution(generator), Y = distribution(generator), Z = distribution(generator), r = distribution(generator);
       Vector < int > C(X, Y, Z);
       Sphere <int> sp( C, r);
       ASSERT_MSG( ( (sp.get_R() == r) && (sp.get_Center().get_x() == X) && (sp.get_Center().get_y() == Y) && (sp.get_Center().get_z() == Z) ), "Sphere equals to itself");
    }
}

void Test_Intersection_of_spheres() {
    {
//       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
//       uniform_int_distribution<float> distribution(1,99);
//       int X1 = distribution(generator), Y1 = distribution(generator), Z1 = distribution(generator), r1 = distribution(generator);
//       int X2 = distribution(generator), Y2 = distribution(generator), Z2 = distribution(generator), r2 = distribution(generator);
       Vector < float > C1(0, 0, 0);
       Sphere <float> sp1( C1, 5.0);
       Vector < float > C2(8.0, 0, 0);
       Sphere <float> sp2( C2, 5.0);
       tuple < bool, Vector<float>, float, Plane<float> > TUP = Intersection_of_spheres (sp1, sp2);
       ASSERT_MSG( ( (get<0>(TUP) == true) && ( (get<1>(TUP).get_x() - 4.0) <= 1E-9 ) && ( get<1>(TUP).get_y() <= 1E-9 ) && ( get<1>(TUP).get_z() <= 1E-9 ) && (get<2>(TUP) - 3.0 <= 1E-9)     && (get<3>(TUP).get_B() <= 1E-9) && (get<3>(TUP).get_C() <= 1E-9) && (( ((get<3>(TUP).get_A()-1.0 <= 1E-9) && (get<3>(TUP).get_D()+4.0 <= 1E-9)) || ((get<3>(TUP).get_A()+1.0 <= 1E-9) && (get<3>(TUP).get_D()-4.0 <= 1E-9)) )) ), "Intersections of Spheres works");
    }
}

void Test_Intersection_of_planes() {
    {
        Plane<int> pl1 (0, 0, 1, 0);
        Plane<int> pl2 (0, 0, 9, 0);
        Plane<int> pl3 (1, 0, 0, 0);
        ASSERT_MSG( ( Intersection_of_planes(pl1,pl2) == false ) && ( Intersection_of_planes(pl1,pl2) == true ) , "Intersection_of_planes works");
    }
}

void Test_Projection_of_point() {
    {
    Plane<int> pl (0, 0, 1, 0);
    Vector<int> p (1, 2, 3);
    //Vector<int> pr (0, 0, 3);
    Vector<int> pr = Projection_of_point(pl,p);
    ASSERT_MSG( ( (pr.get_x() == 0) && (pr.get_y() == 0) && (pr.get_y() == 3) ), "Projection_of_point works");
    }
}

void Test_Distance_point_plane() {
    Plane<int> pl (0, 0, 1, 0);
    Vector<int> p (0, 0, 3);
    ASSERT_MSG( ( Distance_point_plane(pl,p) == 3 ), "Distance_point_plane works");
}

void Test_Distances_point_line() {
    Vector<int> p0 (0, 0, 0);
    Vector<int> v (1, 1, 0);
    Line<int> l (p0, v);
    Vector<int> p (0, 0, 3);
    ASSERT_MSG( ( Distances_point_line(l,p) == 3 ), "Distance_point_plane works");
}

void TestAll() {
    Geo::Testlib::Test test;
    RUN_TEST_MSG(test, Test_Vector, "Vector check");
    RUN_TEST_MSG(test, Test_Segment, "Segment check");
    RUN_TEST_MSG(test, Test_Line, "Line check");
    RUN_TEST_MSG(test, Test_Plane, "Plane check");
    RUN_TEST_MSG(test, Test_Sphere, "Sphere check");
    RUN_TEST_MSG(test, Test_Intersection_of_spheres, "Intersection_of_spheres check");
    RUN_TEST_MSG(test, Test_Intersection_of_planes, "Intersection_of_planes check");
    RUN_TEST_MSG(test, Test_Projection_of_point, "Projection_of_point check");
    RUN_TEST_MSG(test, Test_Distance_point_plane, "Distance_point_plane check");
    RUN_TEST_MSG(test, Test_Distances_point_line, "Distances_point_line check");
}

int main() {
    TestAll();
    Vector < double > v1(1.0, 2.0, 1.0);
    Vector < double > v2(2.0, -2.0, 2.0);
    Line < double > pl(v1, v2);
    cout << pl << endl;

    return 0;
}
