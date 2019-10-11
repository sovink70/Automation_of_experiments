#ifndef LINE_H
#define LINE_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Line {

protected:
        Vector < T > _Point;
        Vector < T > _Direction;

public:
    Line(const Vector < T > &Point, const Vector < T > &Direction) {
        _Point = Point;
        _Direction = Direction;
    }

    Vector < T > get_Point() const;
    void set_Point(const Vector < T > &);
    Vector < T > get_Direction() const;
    void set_Direction(const Vector < T > &);

    template < class V >
    friend ostream& operator<< (ostream&, const Line < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

};

template < class T >
Vector < T > Line<T>::get_Point() const {
    return this->_Point;
}

template < class T >
void Line<T>::set_Point(const Vector < T > &p) {
    this->_Point = p;
}

template < class T >
Vector < T > Line<T>::get_Direction() const {
    return this->_Direction;
}

template < class T >
void Line<T>::set_Direction(const Vector < T > &p) {
    this->_Direction = p;
}

template < class T >
ostream& operator<< (ostream& os, const Line<T>& l){
    os << "Line: Point0" << l._Point << " --- Direction:" << l._Direction ;
    return os;
}

#endif // LINE_H
