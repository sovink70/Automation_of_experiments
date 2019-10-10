#ifndef PLANE3D_H
#define PLANE3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Plane {
protected:
        T _A, _B, _C, _D;

public:
    Plane(const T& A, const T& B, const T& C, const T& D) {
        _A = A;
        _B = B;
        _C = C;
        _D = D;
    }

    T get_A() const;
    T get_B() const;
    T get_C() const;
    T get_D() const;

    void set_A(const T &A);
    void set_B(const T &B);
    void set_C(const T &C);
    void set_D(const T &D);

    double abs();
    template < class V >
    friend ostream& operator<< (ostream&, const Plane < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

};

template < class T >
T Plane<T>::get_A() const {
    return _A;
}

template < class T >
T Plane<T>::get_B() const {
    return _B;
}

template < class T >
T Plane<T>::get_C() const {
    return _C;
}

template < class T >
T Plane<T>::get_D() const {
    return _D;
}
template < class T >
void Plane<T>::set_A(const T& A) {
    _A = A;
}

template < class T >
void Plane<T>::set_B(const T& B) {
    _B = B;
}

template < class T >
void Plane<T>::set_C(const T& C) {
    _C = C;
}

template < class T >
void Plane<T>::set_D(const T& D) {
    _D = D;
}

template < class T >
ostream& operator<< (ostream& os, const Plane<T>& pl){
    os << " Plane: {" << pl._A << ";" << pl._B << ";" << pl._C << ";" << pl._D << "} ";
    return os;
}

template < class T >
double Plane < T >::abs() {
    return sqrt( _A*_A + _B*_B + _C*_C);
}
#endif // PLANE3D_H
