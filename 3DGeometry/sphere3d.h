#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Sphere {
public:
    Sphere(const Vector < T > &Center, const double &R) {
        _Center = Center;
        _R = R;
    }

protected:
    Vector < T > _Center;
    double _R;

};

#endif // SPHERE3D_H
