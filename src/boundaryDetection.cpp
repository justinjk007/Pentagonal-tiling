#include "boundaryDetection.hpp"
#include "CalculateGap.hpp"

using namespace std;

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


list<Segment> getSegments(std::list<Line> lines) {
  /**
   * Return CGAL::segments from myGeometry lines, this weill removed later
   * TODO : Remove this method.
   */
  list<Segment> segments;

  for (list<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
    Point_2 start(it->start.x, it->start.y);
    Point_2 end(it->end.x, it->end.y);
    Segment segment(start, end);
    segments.push_back(segment);
  }

  return segments;
}


bool doIntersect(Segment line, std::list<Segment> lines, Segment exception) {
  /**
   * Check if the passed line segments intersects with any of the
   * lines inside the given list of lines without checking for the
   * line that is an exception.
   */

  for (list<Segment>::iterator it = lines.begin(); it != lines.end(); it++)
    if(*it != exception && CGAL::do_intersect(line , *it))
      return true;
  return false;
}

std::list<Segment> removeInnerLines(std::list<Line> temp_lines) {
    /**
     * Returns the lines that lies outside-most in the given list of
     * lines. Special algorithm , slow now thou.
     */
    list<Segment> boundaries;

    list<Point_2> points = getSources(temp_lines);   // Get points from lines
    list<Segment> lines  = getSegments(temp_lines);  // Get CGAL segments from my lines
    Rect box             = getBoundingBox(points);   // Get the bounding box of the points

    for (list<Segment>::iterator it = lines.begin(); it != lines.end(); it++) {
        // Test 01: Check for intersections to the left
        Point_2 midpoint = getMidPoint(*it);  // Get the midpoint
        // // Make line from midpoint to one of the sides of the bounding box
        Point_2 point_left(box.xmin(), midpoint.y());
        Segment test_line(midpoint, point_left);
        // If the test line does not touch any other lines in the list, this is a boundry.
        if (!doIntersect(test_line, lines, *it)) {
            boundaries.push_back(*it);
        }

        // If the lines does touch , draw lines to other sides of the bounding box and make sure.

        // Add boundry lines to new list
    } // End of Test 01

    return boundaries;
}
