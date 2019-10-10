#ifndef LINE_H
#define LINE_H

#include "vector3d.h"
#include <iostream>

template < class T >
class Line {
public:
    Line(const Vector < T > &Point, const Vector < T > &Direction) {
        _Point = Point;
        _Direction = Direction;
    }

//protected:
    Vector < T > _Point;
    Vector < T > _Direction;

    template < class V >
    friend ostream& operator<< (ostream&, const Line < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

};

template < class T >
ostream& operator<< (ostream& os, const Line<T>& l){
    os << "Line: Point0" << l._Point << " --- Direction:" << l._Direction ;
    return os;
}

#endif // LINE_H
