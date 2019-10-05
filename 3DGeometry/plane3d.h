#ifndef PLANE3D_H
#define PLANE3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Plane {
public:
    Plane(const T& A, const T& B, const T& C, const T& D) {
        _A = A;
        _B = B;
        _C = C;
        _D = D;
    }

//protected:
    T _A, _B, _C, _D;

    double abs();
};

template < class T >
double Plane < T >::abs() {
    return sqrt( _A*_A + _B*_B + _C*_C);
}
#endif // PLANE3D_H
