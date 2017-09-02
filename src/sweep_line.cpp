// Computing intersection points among curves using the sweep line.
#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Sweep_line_2_algorithms.h>
#include <list>
typedef CGAL::Quotient<CGAL::MP_Float>                  NT;
typedef CGAL::Cartesian<NT>                             Kernel;
typedef Kernel::Point_2                                 Point_2;
typedef CGAL::Arr_segment_traits_2<Kernel>              Traits_2;
typedef Traits_2::Curve_2                               Curve_2;
int doTheSweep()
{
  // Construct the input segments.
  Curve_2 segments[] = {Curve_2 (Point_2 (1, 5), Point_2 (8, 5)),
                          Curve_2 (Point_2 (1, 1), Point_2 (8, 8)),
                          Curve_2 (Point_2 (3, 1), Point_2 (3, 8)),
                          Curve_2 (Point_2 (8, 5), Point_2 (8, 8))};

  // Compute all intersection points.
  std::list<Point_2>     pts;
  CGAL::compute_intersection_points (segments, segments + 4,
                                     std::back_inserter (pts));

  // Print the result.
  std::cout << "Found " << pts.size() << " intersection points: " << std::endl;
  std::copy (pts.begin(), pts.end(),
             std::ostream_iterator<Point_2>(std::cout, "\n"));
  // Compute the non-intersecting sub-segments induced by the input segments.
  std::list<Curve_2>   sub_segs;
  CGAL::compute_subcurves(segments, segments + 4, std::back_inserter(sub_segs));
}
