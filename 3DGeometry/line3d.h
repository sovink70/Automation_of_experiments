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

protected:
    Vector < T > _Point;
    Vector < T > _Direction;

};

#endif // LINE_H
