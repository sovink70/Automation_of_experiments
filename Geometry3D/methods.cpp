// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "vector3d.h"
#include "segment3d.h"
#include "line3d.h"
#include "plane3d.h"
#include "sphere3d.h"

#include <tuple>
#include <cmath>
using namespace std;

//template < class T >
//bool Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2) {
//    if (sphere1.get_Center() + sphere2.get_Center() > sphere1.get_R() + sphere2.get_R() && sphere1.get_Center() + sphere2.get_Center() < fabs(sphere1.get_R() - sphere2.get_R()) )
//        return false;
//    else return true;
//}

// и тут Георгий сказал сделать всё шаблонным и тестировать в ассертах с помощью флотов
//template < class T >
//tuple <bool, Vector<T>, double, Plane<T> > Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2) {
//    if ( ( (sphere1.get_Center() - sphere2.get_Center()).abs() < sphere1.get_R() + sphere2.get_R() ) && (sphere1.get_Center() - sphere2.get_Center()).abs() > fabs(sphere1.get_R() - sphere2.get_R()) ) {
//        bool Index = true;
//        double l = sqrt( ( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() )*( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() ) + ( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() )*( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() ) + ( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() )*( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() ) );
//        double p = 0.5*(sphere1.get_R() + sphere2.get_R() + l); // для расчёта площади по формула Герона
//        double R = 2/l*sqrt( p*(p-sphere1.get_R())*(p-sphere2.get_R())*(p-l) );
//        Vector<double> normal = (sphere1.get_Center() - sphere2.get_Center())/(sphere1.get_Center() - sphere2.get_Center()).abs();
//        Vector<double> circleget_Center() = sphere1.get_Center() + normal*sqrt(sphere1.get_R()*sphere1.get_R()-R*R);
//        double D = -normal.get_x()*circleget_Center().get_x() -normal.get_y()*circleget_Center().get_y() -normal.get_z()*circleget_Center().get_z();
//        Plane<double> circle_Plane (normal.get_x(), normal.get_y(), normal.get_z(), D);
//        return make_tuple(Index, circleget_Center(), R, circle_Plane);
//    }
//    else {
//        bool Index = false;
//        return make_tuple(Index);
//    }
//}

template < class T >
tuple < bool, Vector<T>, T, Plane<T> > Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2) {
    if ( ( (sphere1.get_Center() - sphere2.get_Center()).abs() < sphere1.get_R() + sphere2.get_R() ) && (sphere1.get_Center() - sphere2.get_Center()).abs() > fabs(sphere1.get_R() - sphere2.get_R()) ) {
        bool Index = true;
        T l = sqrt( ( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() )*( sphere1.get_Center().get_x()-sphere2.get_Center().get_x() ) + ( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() )*( sphere1.get_Center().get_y()-sphere2.get_Center().get_y() ) + ( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() )*( sphere1.get_Center().get_z()-sphere2.get_Center().get_z() ) );
        T p = 0.5*(sphere1.get_R() + sphere2.get_R() + l); // для расчёта площади по формула Герона
        T R = 2/l*sqrt( p*(p-sphere1.get_R())*(p-sphere2.get_R())*(p-l) );
        Vector<T> normal = (sphere1.get_Center() - sphere2.get_Center())/(sphere1.get_Center() - sphere2.get_Center()).abs(); // вектор нормали единичный
        Vector<T> circle_Center = sphere1.get_Center() + normal*sqrt(sphere1.get_R()*sphere1.get_R()-R*R);
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
        Projection._x = -( plane.get_B()*plane.get_A()*plane.get_A()*point._y+ plane.get_C()*plane.get_B()*plane.get_B()*point._z- plane.get_C()*plane.get_C()*point._z+ plane.get_B()*plane.get_C()*plane.get_D()+ plane.get_A()*plane.get_A()*point._z+ plane.get_B()*plane.get_B()*point._z+ plane.get_C()*plane.get_C()*point._z+ plane.get_D()*plane.get_A()*plane.get_A()+ plane.get_C()*plane.get_D()*plane.get_D())/( plane.get_A() * (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) );
        Projection._y = ( (plane.get_C()*plane.get_C() + plane.get_A()*plane.get_A())*point._y + point._z*plane.get_B()*plane.get_C()- plane.get_D()*plane.get_B() ) / (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) ;
        Projection._z = - (plane.get_B()*plane.get_C()*point._y + plane.get_C()*point._z - plane.get_D()*plane.get_C()) / (plane.get_A()*plane.get_A() + plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) + point._z;
        return Projection;
    }
    else { //A ==0
        if (plane.get_B() != 0){
            Projection._x = point._x;
            Projection._z = (plane.get_B()*plane.get_B()*point._z - plane.get_D()*plane.get_C()- point._y*plane.get_B()*plane.get_C())/ (plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C());
            Projection._y = (-plane.get_C()*(plane.get_B()*plane.get_B()*point._z - plane.get_D()*plane.get_C()- point._y*plane.get_B()*plane.get_C())/(plane.get_B()*plane.get_B() + plane.get_C()*plane.get_C()) - plane.get_D()  ) / plane.get_B();
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
double Distance_point_plane(Plane<T>& plane, Vector<T>& vector) {
    return ( fabs(plane.get_A()*vector.get_x() + plane.get_B()*vector.get_y() + plane.get_C()*vector.get_z() +plane.get_D()) / plane.abs() ); // уточнить на cplusplus.com or cpp reeference, является ли шаблонным - cout << fabs(int(-3)) << endl; работает, так что всё норм //https://ru.onlinemschool.com/math/library/analytic_geometry/p_plane/
}

template < class T >
double Distances_point_line(Line<T>& line, Vector<T>& point) {
    Segment<T> M0M1(point, line.get_Point());

    return ( fabs(M0M1.Shift()^line.get_Direction()) / fabs(line.get_Direction()) ); //https://ru.onlinemschool.com/math/library/analytic_geometry/p_line/
}
