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

