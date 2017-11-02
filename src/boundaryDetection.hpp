#ifndef BOUNDARYDETECTION_HPP
#define BOUNDARYDETECTION_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include <CGAL/bounding_box.h>
#include <fstream>
#include <iostream>
#include <list>
#include "myGeometry.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::FT FT;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment;
typedef K::Iso_rectangle_2 Rect;
typedef CGAL::Polygon_2<K> Polygon_2;

Rect getBoundingBox(const std::list<Point_2>&);
std::list<Segment> removeInnerLines(const std::list<Line>&);
std::list<Segment> getSegments(const std::list<Line>&);  // TODO: Remove this
bool doIntersect(const Segment&, const std::list<Segment>&, const Segment&);
Polygon_2 getPolygon(const std::list<Point_2>&);
bool onSegment(const Point_2&, const Point_2&, const Point_2&);
int orientation(const Point_2&, const Point_2&, const Point_2&);
bool do_intersect(const Segment&, const Segment&);

template <class Point>
auto getX()(Point p) -> decltype(p.x())
{
    return p.x();
}

template <class Point>
auto getY()(Point p) -> decltype(p.y())
{
    return p.y();
}

#endif /* BOUNDARYDETECTION_HPP */
