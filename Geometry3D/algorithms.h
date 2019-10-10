#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "segment3d.h"
#include "vector3d.h"
#include "plane3d.h"
#include "sphere3d.h"
#include "line3d.h"

template < class T >
tuple < bool, Vector<T>, T, Plane<T> > Intersection_of_spheres(Sphere<T> sphere1, Sphere<T> sphere2);

#endif // ALGORITHMS_H
