#include "vector3d.h"
#include "segment3d.h"
#include "line3d.h"
#include "plane3d.h"
#include "sphere3d.h"

#include <cmath>
using namespace std;

template < class T >
bool Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2) {
    if (sphere1._Center + sphere2._Center > sphere1._R + sphere2._R && sphere1._Center + sphere2._Center < fabs(sphere1._R - sphere2._R) )
        return false;
    else return true;
}

template < class T >
bool Intersection_of_planes() {
    //return 0;
}

template < class T >
bool Projection_of_point() {

}

template < class T >
double Distance_point_plane(Plane<T>& plane, Vector<T>& vector) {
    return ( fabs(plane._A*vector._x + plane._B*vector._y + plane._C*vector._z +plane._D) / plane.abs() ); // уточнить на cplusplus.com or cpp reeference, является ли шаблонным - cout << fabs(int(-3)) << endl; работает, так что всё норм //https://ru.onlinemschool.com/math/library/analytic_geometry/p_plane/
}

template < class T >
double Distances_point_line(Line<T>& line, Vector<T>& point) {
    Segment<T> M0M1(point, line._Point);

    return ( fabs(M0M1.Shift()^line._Direction) / fabs(line._Direction) ); //https://ru.onlinemschool.com/math/library/analytic_geometry/p_line/
}
