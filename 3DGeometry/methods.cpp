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
bool Intersection_of_planes(Plane<T>& plane1, Plane<T>& plane2) {
    Vector<T> n1 (plane1._A, plane1._B, plane1._C);
    Vector<T> n2 (plane2._A, plane2._B, plane2._C);
    Vector<T> n1_n2=n1^n2;
    Vector<T> Null(0, 0, 0);
    if (n1_n2 == Null)
        return false;
    else return true;
}

template < class T >
Vector<T> Projection_of_point(Plane<T>& plane, Vector<T>& point) {
    Vector<T> Projection;
    if (plane._A != 0) {
        Projection._x = -( plane._B*plane._A*plane._A*point._y+ plane._C*plane._B*plane._B*point._z- plane._C*plane._C*point._z+ plane._B*plane._C*plane._D+ plane._A*plane._A*point._z+ plane._B*plane._B*point._z+ plane._C*plane._C*point._z+ plane._D*plane._A*plane._A+ plane._C*plane._D*plane._D)/( plane._A * (plane._A*plane._A + plane._B*plane._B + plane._C*plane._C) );
        Projection._y = ( (plane._C*plane._C + plane._A*plane._A)*point._y + point._z*plane._B*plane._C- plane._D*plane._B ) / (plane._A*plane._A + plane._B*plane._B + plane._C*plane._C) ;
        Projection._z = - (plane._B*plane._C*point._y + plane._C*point._z - plane._D*plane._C) / (plane._A*plane._A + plane._B*plane._B + plane._C*plane._C) + point._z;
        return Projection;
    }
    else { //A ==0
        if (plane._B != 0){
            Projection._x = point._x;
            Projection._z = (plane._B*plane._B*point._z - plane._D*plane._C- point._y*plane._B*plane._C)/ (plane._B*plane._B + plane._C*plane._C);
            Projection._y = (-plane._C*(plane._B*plane._B*point._z - plane._D*plane._C- point._y*plane._B*plane._C)/(plane._B*plane._B + plane._C*plane._C) - plane._D  ) / plane._B;
        }
        else { //B ==0
            if (plane._C == 0){
                cout<<"ERROR: impossible plane"<<endl;
            }
            else {//C !=0
                Projection._y = point._y;
                Projection._x = point._x;
                Projection._z = -plane._D/plane._C;
            }
        }
    }
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
