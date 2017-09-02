#ifndef SWEEP_LINE_HPP
#define SWEEP_LINE_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Cartesian.h>
#include <CGAL/algorithm.h>
#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment;

using namespace std;

int doTheSweep();
bool comparePosition(Point_2,Point_2);
std::list<Point_2> sortByPosition(std::list<Point_2>);

#endif /* SWEEP_LINE_HPP */
