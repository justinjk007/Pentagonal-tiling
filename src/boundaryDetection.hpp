#ifndef BOUNDARYDETECTION_HPP
#define BOUNDARYDETECTION_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/algorithm.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/bounding_box.h>
#include <CGAL/Polygon_2.h>
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

Rect getBoundingBox(std::list<Point_2>);
std::list<Segment> removeInnerLines(std::list<Line>);
std::list<Segment> getSegments(std::list<Line>); // TODO: Remove this
bool doIntersect(Segment, std::list<Segment>, Segment);
Polygon_2 getPolygon(std::list<Point_2>);
bool do_intersect(Segment, Segment );

#endif /* BOUNDARYDETECTION_HPP */
