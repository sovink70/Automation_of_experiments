#include <iostream>

#include "segment3d.h"
#include "vector3d.h"
#include "plane3d.h"
#include "sphere3d.h"
#include "line3d.h"

#include "Testlib.h"

#include <random>

#include <cmath>
using namespace std;

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
       Segment <int> sgm(sp,ep);
       ASSERT_MSG( (sgm._startPoint == sp) && (sgm._endPoint == ep), "Segment equals to itself");
    }
    {
       int x1 = distribution(generator), y1 = distribution(generator), z1 = distribution(generator), x2 = distribution(generator), y2 = distribution(generator), z2 = distribution(generator);
       Vector <int> sp(x1, y1, z1);
       Vector <int> ep(x2, y2, z2);
       Segment <int> sgm(sp,ep);
       Vector <int> v(x2-x1, y2-y1, z2-z1);
       //ASSERT_MSG( (sgm.Shift() == v), "Shift for Segment works well"); // - это он не кушает, потому что не знает о преропределении ==. ХОТЯ сверху и снизу он всё скушал
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
       ASSERT_MSG(l._Point == p, "Line.Point equals to itself");
       ASSERT_MSG(l._Direction == d, "Line.Direction equals to itself");
    }
}

void Test_Plane() {
    {
       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
       uniform_int_distribution<int> distribution(1,99);
       int a = distribution(generator), b = distribution(generator), c = distribution(generator), d = distribution(generator);
       Plane <int> pl(a, b, c, d);
       ASSERT_MSG( ( (pl._A == a) && (pl._B == b) && (pl._C == c) && (pl._D == d) ), "Plane equals to itself");
    }
}

void Test_Sphere() {
    {
       default_random_engine generator; //https://ru.stackoverflow.com/questions/575156/%D0%9A%D0%B0%D0%BA-%D1%81%D0%BE%D0%B7%D0%B4%D0%B0%D1%82%D1%8C-%D1%80%D0%B0%D0%BD%D0%B4%D0%BE%D0%BC-%D0%BD%D0%B0-c/575162
       uniform_int_distribution<int> distribution(1,99);
       int X = distribution(generator), Y = distribution(generator), Z = distribution(generator), r = distribution(generator);
       Vector < int > C(X, Y, Z);
       Sphere <int> sp( C, r);
       ASSERT_MSG( ( (sp._R == r) && (sp._Center.get_x() == X) && (sp._Center.get_y() == Y) && (sp._Center.get_z() == Z) ), "Sphere equals to itself");
    }
}

void TestAll() {
    Geo::Testlib::Test test;
    RUN_TEST_MSG(test, Test_Vector, "Vector check");
    RUN_TEST_MSG(test, Test_Segment, "Segment check");
    RUN_TEST_MSG(test, Test_Line, "Line check");
    RUN_TEST_MSG(test, Test_Plane, "Line check");
    RUN_TEST_MSG(test, Test_Sphere, "Line check");
}

int main() {
    TestAll();
    Vector < double > v1(1.0, 2.0, 1.0);
    Vector < double > v2(2.0, -2.0, 2.0);
    Line < double > pl(v1, v2);
    cout << pl << endl;

    return 0;
}
