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

std::list<Segment> removeInnerLines(std::list<Line> lines) {
  /**
   * Returns the lines that lies outside-most in the given list of
   * lines. Special algorithm , slow now thou.
   */

  // Make the lines into points

  // Get the bounding box of the points

  // In a loop start servicing each line

          // Get the midpoint

          // Make line from midpoint to one of the sides of the bounding box

          // If the line does not touch any other lines in the list, this is a boundry.

          // If the lines does touch , draw lines to other sides of the bounding box and make sure.

         // Add boundry lines to new list

  // Return boundaries
}
