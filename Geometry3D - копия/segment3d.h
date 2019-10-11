#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Segment {

public:
    Vector < T > get_startPoint() const;
    void set_startPoint(const Vector < T > &);
    Vector < T > get_endPoint() const;
    void set_endPoint(const Vector < T > &);

    Segment(const Vector < T > &startPoint, const Vector < T > &endPoint) {
        _startPoint = startPoint;
        _endPoint = endPoint;
    }

    Vector < T > Shift();

protected:
        Vector < T > _startPoint;
        Vector < T > _endPoint;
//        Segment(double x1,double y1,double z1, double x2,double y2,double z2) {
//            Vector < T > _startPoint( x1, y1, z1); // создаю с нуля вектора. Можно и откомментить верхние 2 строчки и через геттеры записать туда
//            Vector < T > _endPoint( x2, y2, z2);
//            cout<<"Segment constructor"<<endl;
//        }

    template < class V >
    friend ostream& operator<< (ostream&, const Segment < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

};

template < class T >
Vector < T > Segment<T>::get_startPoint() const {
    return this->_startPoint;
}

template < class T >
void Segment<T>::set_startPoint(const Vector < T > &p) {
    this->_startPoint = p;
}

template < class T >
Vector < T > Segment<T>::get_endPoint() const {
    return this->_endPoint;
}

template < class T >
void Segment<T>::set_endPoint(const Vector < T > &p) {
    this->_endPoint = p;
}

template < class T >
ostream& operator<< (ostream& os, const Segment<T>& sgm){
    os << "Segment {" << sgm._startPoint << "---" << sgm._endPoint << "}" ;
    return os;
}

template < class T >
Vector < T > Segment < T >::Shift() {
    return Vector < T >(_endPoint.get_x()-_startPoint.get_x(), _endPoint.get_y()-_startPoint.get_y(), _endPoint.get_z()-_startPoint.get_z()) ; // need to displace vector in 0, 0, 0
}

#endif

