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

    T get_R() const;
    void set_R(const T &R);

    Vector < T > get_Center() const;
    void set_Center(const Vector < T > &);

protected:
    Vector < T > _Center;
    T _R;
    template < class V >
    friend ostream& operator<< (ostream&, const Sphere < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector



//    T get_x() const;
//    T get_y() const;
//    T get_z() const;

//    void set_x(const T &x);
//    void set_y(const T &y);
//    void set_z(const T &z);
};

template < class T >
ostream& operator<< (ostream& os, const Sphere<T>& sp){
    os << "Sphere Center: (" << sp._Center._x << ";" << sp._Center._y << ";" << sp._Center._z << ")" << " Radius: "<< sp._R ;
    return os;
}

template < class T >
T Sphere<T>::get_R() const {
    return _R;
}

template < class T >
void Sphere<T>::set_R(const T& R) {
    _R = R;
}

template < class T >
Vector < T > Sphere<T>::get_Center() const {
    return this->_Center;
}

template < class T >
void Sphere<T>::set_Center(const Vector < T > &c) {
    this->_Center = c;
}

//template < class T >
//T Vector<T>::get_x() const {
//    return _x;
//}

//template < class T >
//T Vector<T>::get_y() const {
//    return _y;
//}

//template < class T >
//T Vector<T>::get_z() const {
//    return _z;
//}

//template < class T >
//void Vector<T>::set_x(const T& x) {
//    _x = x;
//}

//template < class T >
//void Vector<T>::set_y(const T& y) {
//    _y = y;
//}

//template < class T >
//void Vector<T>::set_z(const T& z) {
//    _z = z;
//}

#endif // SPHERE3D_H
