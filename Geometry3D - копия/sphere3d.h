#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Sphere {
public:
    Sphere(const Vector < T > &Center, const T &R) {
        _Center = Center;
        _R = R;
    }

//protected:
    Vector < T > _Center;
    T _R;
    template < class V >
    friend ostream& operator<< (ostream&, const Sphere < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

};

template < class T >
ostream& operator<< (ostream& os, const Sphere<T>& sp){
    os << "Sphere Center: (" << sp._Center._x << ";" << sp._Center._y << ";" << sp._Center._z << ")" << " Radius: "<< sp._R ;
    return os;
}

#endif // SPHERE3D_H
