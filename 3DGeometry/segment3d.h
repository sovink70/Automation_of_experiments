#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Segment {
public:
    Segment(const Vector < T > &startPoint, const Vector < T > &endPoint) {
        _startPoint = startPoint;
        _endPoint = endPoint;
    }

//        Segment(double x1,double y1,double z1, double x2,double y2,double z2) {
//            Vector < T > _startPoint( x1, y1, z1); // создаю с нуля вектора. Можно и откомментить верхние 2 строчки и через геттеры записать туда
//            Vector < T > _endPoint( x2, y2, z2);
//            cout<<"Segment constructor"<<endl;
//        }

protected:
    Vector < T > _startPoint;
    Vector < T > _endPoint;

    Vector < T > Shift();
};

template < class T >
Vector < T > Segment < T >::Shift() {
    return Vector < T >(_endPoint._x-_startPoint._x, _endPoint._y-_startPoint._y, _endPoint._z-_startPoint._z) ; // need to displace vector
}

#endif

