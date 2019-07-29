#ifndef COMPUTATION_GEOMETRY_H
#define COMPUTATION_GEOMETRY_H

#include "segment.h"

template <typename T>
typename vector<Point<T> >::iterator FindLeftMostPoint(vector<Point<T> >& pts);

template <typename T>
vector<Point<T> > ComputeConvexHull(vector<Point<T> >& pts);

#include "convexhull.cpp"

#endif // COMPUTATION_GEOMETRY_H
