#ifndef CGAL_HPP
#define CGAL_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/algorithm.h>
#include <CGAL/bounding_box.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::FT FT;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment;
typedef K::Iso_rectangle_2 Rect;
typedef CGAL::Polygon_2<K> Polygon_2;

#endif /* CGAL_HPP */
