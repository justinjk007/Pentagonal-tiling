#include "boundaryDetection.hpp"

template <class OutputIterator>
void alpha_edges(const Alpha_shape_2& A, OutputIterator out) {
    for (Alpha_shape_edges_iterator it = A.alpha_shape_edges_begin();
         it != A.alpha_shape_edges_end(); ++it) {
        *out++ = A.segment(*it);
    }
}

std::list<Segment> getConcaveHull(std::list<Point_2> points) {
  /**
   * Reads a list of points and returns a list of segments
   * corresponding to the concave hull also known as α-Shape
   */

    Alpha_shape_2 A(points.begin(), points.end(), FT(25), Alpha_shape_2::REGULARIZED);

    std::list<Segment> segments;
    alpha_edges(A, std::back_inserter(segments)); // Inserting the α-shape into the list
    return segments; // Return the segements that are in the hull
}

Rect getBoundingBox(std::list<Point_2> points)
{
  /**
   * Returns axis-aligned bounding box of 2D points
   */
  Rect box = CGAL::bounding_box(points.begin(), points.end());
  // std::cout << box << std::endl;
  return box;
}
