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
tuple < bool, Vector<T>, T, Plane<T> > Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2);

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
       //ASSERT_MSG( ( (get<0>(TUP) == true) && ( (get<1>(TUP).get_x() - 4.0) <= 1E-9 ) && ( get<1>(TUP).get_y() <= 1E-9 ) && ( get<1>(TUP).get_z() <= 1E-9 ) && (get<2>(TUP) - 3.0 <= 1E-9)     && (get<3>(TUP).get_B() <= 1E-9) && (get<3>(TUP).get_C() <= 1E-9) && (( ((get<3>(TUP).get_A()-1.0 <= 1E-9) && (get<3>(TUP).get_D()+4.0 <= 1E-9)) || ((get<3>(TUP).get_A()+1.0 <= 1E-9) && (get<3>(TUP).get_D()-4.0 <= 1E-9)) )) ), "Sphere equals to itself");
    }
}



void TestAll() {
    Geo::Testlib::Test test;
    RUN_TEST_MSG(test, Test_Vector, "Vector check");
    RUN_TEST_MSG(test, Test_Segment, "Segment check");
    RUN_TEST_MSG(test, Test_Line, "Line check");
    RUN_TEST_MSG(test, Test_Plane, "Plane check");
    RUN_TEST_MSG(test, Test_Sphere, "Sphere check");
    RUN_TEST_MSG(test, Test_Intersection_of_spheres, "Intersection_of_spheres check");
}

int main() {
    TestAll();
    Vector < double > v1(1.0, 2.0, 1.0);
    Vector < double > v2(2.0, -2.0, 2.0);
    Line < double > pl(v1, v2);
    cout << pl << endl;

    return 0;
}
