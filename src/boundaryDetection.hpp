#ifndef CONCAVEHULL_HPP
#define CONCAVEHULL_HPP

#include <CGAL/Alpha_shape_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/algorithm.h>
#include <CGAL/Simple_cartesian.h>
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

typedef CGAL::Alpha_shape_vertex_base_2<K> Vb;
typedef CGAL::Alpha_shape_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation_2;

typedef CGAL::Alpha_shape_2<Triangulation_2> Alpha_shape_2;
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator;


template <class OutputIterator>
void alpha_edges(const Alpha_shape_2&, OutputIterator);
template <class OutputIterator>
bool file_input(OutputIterator);
std::list<Segment> getConcaveHull(std::list<Point_2>);

Rect getBoundingBox(std::list<Point_2>);
std::list<Segment> removeInnerLines(std::list<Line>);
std::list<Segment> getSegments(std::list<Line>); // TODO: Remove this
bool doIntersect(Segment, std::list<Segment>, Segment);

#endif /* CONCAVEHULL_HPP */