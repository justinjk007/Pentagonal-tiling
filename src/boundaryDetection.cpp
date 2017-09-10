#include "boundaryDetection.hpp"
#include "CalculateGap.hpp"

using namespace std;

Rect getBoundingBox(std::list<Point_2> points)
{
    /**
     * Returns axis-aligned bounding box of 2D points
     */
    Rect box = CGAL::bounding_box(points.begin(), points.end());
    // std::cout << box << std::endl;
    return box;
}

list<Segment> getSegments(std::list<Line> lines)
{
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

bool onSegment(Point_2 p, Point_2 q, Point_2 r)
{
    /**
     * Check if point r is on the line segment made by point p and q.
     */
    if (q.x() <= max(p.x(), r.x()) && q.x() >= min(p.x(), r.x()) && q.y() <= max(p.y(), r.y()) &&
        q.y() >= min(p.y(), r.y()))
        return true;
    return false;
}

int orientation(Point_2 p, Point_2 q, Point_2 r)
{
    /**
     * To find orientation of ordered triplet (p, q, r).
     * The function returns following values
     * 0 --> p, q and r are colinear
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     */
    int val = (double)(q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;    // colinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

bool do_intersect(Segment a, Segment b)
{
    /**
      * Find the four orientations needed for general and special
      * cases, and returns true if the line segments intersect.
     */
    Point_2 p1 = a.source();
    Point_2 q1 = a.target();
    Point_2 p2 = b.source();
    Point_2 q2 = b.target();

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return true;
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;  // Doesn't fall in any of the above cases
}

bool doIntersect(Segment line, std::list<Segment> lines, Segment except_line)
{
    /**
     * Check if the passed line segments intersects with any of the
     * lines inside the given list of lines without checking for the
     * line that is an exception.
     */

    for (std::list<Segment>::iterator it = lines.begin(); it != lines.end(); it++)
        if (*it == except_line)
            continue;
        else if (do_intersect(line, *it))
            return true;
    return false;
}

std::list<Segment> removeInnerLines(std::list<Line> temp_lines)
{
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

        // Make line from midpoint to sides of the bounding box
        Point_2 point_left(box.xmin(), midpoint.y());
        Point_2 point_right(box.xmax(), midpoint.y());
        Point_2 point_up(midpoint.x(), box.ymax());
        Point_2 point_down(midpoint.x(), box.ymin());

        Segment test_line1(midpoint, point_left);
        Segment test_line2(midpoint, point_right);
        Segment test_line3(midpoint, point_up);
        Segment test_line4(midpoint, point_down);

        // If the test lines does not intersect in any one of the side
        // then that is a boundary
        if (!doIntersect(test_line1, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line2, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line3, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line4, lines, *it)) {
            boundaries.push_back(*it);
        } else
            continue;
    }

    return boundaries;
}

Polygon_2 getPolygon(std::list<Point_2> points)
{
    /**
     * Returns a cgal polygon from the given list of points. Remember
     * points passed should already be sorted clockwise. Or error will thrown.
     */

    Polygon_2 polygon;
    for (list<Point_2>::iterator it = points.begin(); it != points.end(); it++) {
        polygon.push_back(*it);
    }
    return polygon;
}
