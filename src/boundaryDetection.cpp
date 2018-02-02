#include "boundaryDetection.hpp"

using namespace std;

const double PI = 3.14159265358979323846264338327950288;

Rect getBoundingBox(const std::list<Point_2>& points)
{
    /**
     * Returns axis-aligned bounding box of 2D points
     */
    Rect box = CGAL::bounding_box(points.begin(), points.end());
    // std::cout << box << std::endl;
    return box;
}

list<Segment> getSegments(const std::list<Line>& lines)
{
    /**
     * Return CGAL::segments from myGeometry lines, this weill removed later
     * TODO : Remove this method.
     */
    list<Segment> segments;

    for (auto it = lines.begin(); it != lines.end(); it++) {
        Point_2 start(it->source.x, it->source.y);
        Point_2 end(it->target.x, it->target.y);
        Segment segment(start, end);
        segments.push_back(segment);
    }

    return segments;
}

bool onSegment(const Point_2& p, const Point_2& q, const Point_2& r)
{
    /**
     * Check if point r is on the line segment made by point p and q.
     */
    if (q.x() <= max(p.x(), r.x()) && q.x() >= min(p.x(), r.x()) && q.y() <= max(p.y(), r.y()) &&
        q.y() >= min(p.y(), r.y()))
        return true;
    return false;
}

int orientation(const Point_2& p, const Point_2& q, const Point_2& r)
{
    /**
     * To find orientation of ordered triplet (p, q, r).
     * The function returns following values
     * 0 --> p, q and r are colinear
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     */
    int val = (int)((q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y()));

    if (val == 0) return 0;    // colinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

bool do_intersect(const Segment& a, const Segment& b)
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

bool doIntersect(const Segment& line, const std::list<Segment>& lines, const Segment& except_line)
{
    /**
     * Check if the passed line segments intersects with any of the
     * lines inside the given list of lines without checking for the
     * line that is an exception.
     */

    for (auto it = lines.begin(); it != lines.end(); it++)
        if (*it == except_line)
            continue;
        else if (do_intersect(line, *it))
            return true;
    return false;
}

std::list<Segment> removeInnerLines(const std::list<Line>& temp_lines)
{
    /**
     * Returns the lines that lies outside-most in the given list of
     * lines. Special algorithm , slow now thou.
     */
    list<Segment> boundaries;

    list<Point_2> points = getSources(temp_lines);   // Get points from lines
    list<Segment> lines  = getSegments(temp_lines);  // Get CGAL segments from my lines
    Rect box             = getBoundingBox(points);   // Get the bounding box of the points

    for (auto it = lines.begin(); it != lines.end(); it++) {
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

Polygon_2 getPolygon(const std::list<Point_2>& points)
{
    /**
     * Returns a cgal polygon from the given list of points. Remember
     * points passed should already be sorted clockwise. Or error will thrown.
     */

    Polygon_2 polygon;
    for (auto it = points.begin(); it != points.end(); it++) {
        polygon.push_back(*it);
    }
    return polygon;
}

void fillDimensions(Tile& tile)
{
    /**
     * This method creates the tile structure with all dimensions
     * filled in. This is done to fill the missing 3 dimension the DE
     * does not give us.
     */
    PrimitiveTile newSample(tile);
    tile = newSample.createPentagon();
}

bool validateTile(const Tile& tile)
{
    /*
     * This method returns whether the Tile inputted is valid or not.
     * This method is used by getgap()
     */
    double max_side = getMaxSide(tile);
    if (tile.angle[4] > 0.0)
        if (tile.side[0].value + tile.side[1].value + tile.side[2].value + tile.side[3].value +
                tile.side[4].value >
            (2 * max_side))
            // 2 x Biggest side becauase we don't know which one is the
            // biggest side now and we should count that twice on the right
            // side because we are taking the sum of all sides instead of
            // the other 4..soo..
            return true;
        else
            return false;
    else
        return false;
}

bool validatePolygon(const std::vector<Point_2>& points)
{
    /**
     * Make sure the polygon created is convex and simple
     */
    Polygon_2 polygon;
    for (auto& point : points) polygon.push_back(point);
    return (polygon.is_convex() && polygon.is_simple());
}

double getMaxSide(const Tile& tile)
{
    /*
     * This method returns the biggest side of the tile.
     */
    double max_side = tile.side[0].value;
    for (int i = 0; i < 5; ++i) {
        if (tile.side[i].value > max_side) max_side = tile.side[i].value;
    }
    return max_side;
}

double getMaxAngle(const Tile& tile)
{
    /*
     * This method returns the biggest angle of the tile.
     */
    double max_angle = tile.angle[0];
    for (int i = 0; i < 5; ++i) {
        if (tile.angle[i] > max_angle) max_angle = tile.angle[i];
    }
    return max_angle;
}

double getThirdSide(const Side& a, const Side& b, const double& angle)
{
    /*
     * This method returns the third side of the triangle formed inside
     * a polygon used for area calculating purposes. Angle should be
     * passed in degrees
     */
    double side_c = sqrt((a.value * a.value) + (b.value * b.value) -
                         (2.0 * a.value * b.value * cos(angle * PI / 180.0)));
    return side_c;
}

double getOtherAngle(const Side& a, const Side& b, const double& angle_b, const char& which_angle)
{
    /**
     * This method uses sine law to find the angle b/w a and c or b and
     * c .Here the angle passed is the angle b/w the sides a and b. The
     * character passed is the angle to be found which can be a or c
     * because the angle we know that's in the middle is b.Angle should
     * be passed in degrees
     */
    double other_angle = 0.0;
    double part_one;
    double side_c_length = getThirdSide(a, b, angle_b);
    if (which_angle == 'a') {
        part_one    = (sin(angle_b * PI / 180.0) * b.value) / side_c_length;
        other_angle = asin(part_one) * 180.0 / PI;
        return other_angle;
    } else if (which_angle == 'c') {
        part_one    = (sin(angle_b * PI / 180.0) * a.value) / side_c_length;
        other_angle = asin(part_one) * 180.0 / PI;
        return other_angle;
    } else
        return other_angle;
}

double getMiddleAngle(const double& a, const double& b, const double& c)
{
    /**
     * This methods returns the angle b/w a and b when a,b and c are
     * sides of a triangle, using Cosine law in reverse.
     * Reference http://www.teacherschoice.com.au/maths_library/trigonometry/solve_trig_sss.htm
     */
    double calc = ((a * a) + (b * b) - (c * c)) / (2 * a * b);
    return acos(calc) * (180.0 / PI);
}

double getTriangleArea(const double& a, const double& b, const double& c)
{
    /*
     * This method returns the Area of the triagle using Heron's
     * Formulae
     */
    double S    = (a + b + c) / 2.0;
    double area = sqrt(S * (S - a) * (S - b) * (S - c));
    return area;
}

double getTileArea(const Tile& tile)
{
    /*
     * This method returns the Area of the pentagon dividing it into
     * three triangles, calculating its area and summing them up.
     */
    double ac           = getThirdSide(tile.side[0], tile.side[1], tile.angle[1]);
    double ce           = getThirdSide(tile.side[2], tile.side[3], tile.angle[3]);
    double triangle1    = getTriangleArea(tile.side[0].value, tile.side[1].value, ac);
    double triangle2    = getTriangleArea(tile.side[2].value, tile.side[3].value, ce);
    double triangle3    = getTriangleArea(ac, ce, tile.side[4].value);
    double pentagonArea = triangle1 + triangle2 + triangle3;
    return pentagonArea;
}

double getPolygonArea(const std::list<Line>& polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * lines that create the polygon/polygons, sorted clockwise or
     * anti-clockwise
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;

    for (auto it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->source.x;
        y1 = it->source.y;
        x2 = it->target.x;
        y2 = it->target.y;
        sum += x1 * y2;
        diff += y1 * x2;
    }

    area = (1.0 / 2.0) * abs((sum - diff));
    return area;
}

double getPolygonArea(const std::list<Segment>& polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * Segment_2d defined in cgal that creates the polygon/polygons
     * sorted clockwise or anti-clockwise
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;

    for (auto it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->source().x();
        y1 = it->source().y();
        x2 = it->target().x();
        y2 = it->target().y();
        sum += x1 * y2;
        diff += y1 * x2;
    }

    area = (1.0 / 2.0) * abs((sum - diff));
    return area;
}

double getPolygonArea(const std::list<Point_2>& polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * points that create the polygon/polygons.
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;
    for (auto it = polygon.begin(); it != polygon.end();) {
        bool flag = false;
        x1        = it->x();
        y1        = it->y();
        it++;
        if (it == polygon.end()) {
            it   = polygon.begin();
            flag = true;
        }
        x2 = it->x();
        y2 = it->y();
        sum += x1 * y2;
        diff += y1 * x2;
        if (flag) break;
    }

    area = (1.0 / 2.0) * abs((sum - diff));
    return area;
}

std::list<Line> removeCommonLines(std::list<Line> lines)
{
    /**
     * This method is used remove duplicate Lines from the given Line
     * list, this will only work for the specific case I have. If a duplicate
     * is found both the original and the duplicate are removed from the
     * list. This is done to eliminate inner Line-segments of the
     * translated structure.
     */
    std::list<Line> new_lines = lines;

    while (!lines.empty()) {
        Line line1 = lines.front();  // Get the 1st line from the list
        lines.pop_front();           // Remove the same line from the list
        for (auto it = lines.begin(); it != lines.end(); ++it)
            if (compareLine(line1, *it))  // Compare to see if same Lines exists
                new_lines = removeLine(new_lines, line1);
    }

    return new_lines;
}

std::list<Point_2> removeCommonPoints(std::list<Point_2> points)
{
    /**
     * This method is used remove duplicate points, both original and
     * dupe are removed.
     */

    std::list<Point_2> new_points = points;

    while (!points.empty()) {
        Point_2 point1 = points.front();  // Get the 1st line from the list
        points.pop_front();               // Remove the same line from the list
        for (auto it = points.begin(); it != points.end(); ++it)
            if (comparePoint(point1, *it))  // Compare to see if same Point_2s exists
                new_points = removePoint(new_points, point1);
    }

    return new_points;
}

std::list<Line> removeLine(std::list<Line> lines, const Line& val)
{
    /**
     * Override function for list::remove rewritten for list<Line>
     */
    for (auto it = lines.begin(); it != lines.end();) {
        if (compareLine(val, *it))  // If same lines exists
            it = lines.erase(it);
        else
            ++it;
    }
    return lines;
}

std::list<Point_2> removePoint(std::list<Point_2> points, const Point_2& val)
{
    /**
     * Override function for list::remove rewritten for list<Point_2>
     */
    for (auto it = points.begin(); it != points.end();) {
        if (comparePoint(val, *it))  // If same lines exists
            it = points.erase(it);
        else
            ++it;
    }
    return points;
}

bool comparePoint(const Point_2& a, const Point_2& b)
{
    /**
     * Compare points to see if they are equal.
     */
    double diff1 = a.x() - b.x();
    double diff2 = a.y() - b.y();
    if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04) return true;
    return false;
}

std::list<Point_2> getSources(const std::list<Line>& lines)
{
    /**
     * Returns a list of points representing the source of each line given
     * Used to find the Bounding box of the given line segments basically.
     */
    std::list<Point_2> list_of_points;

    for (auto it = lines.begin(); it != lines.end(); it++) {
        double xx = it->source.x;
        double yy = it->source.y;
        Point_2 point(xx, yy);
        list_of_points.push_back(point);  // Add the point to the list
    }
    return list_of_points;
}

std::list<Point_2> getSources(const std::list<Segment>& lines)
{
    /**
     * Returns a list of points representing the source of each line given
     * Used to find the Bounding box of the given line segments basically.
     */
    std::list<Point_2> list_of_points;

    for (auto it = lines.begin(); it != lines.end(); it++) {
        double xx = it->source().x();
        double yy = it->source().y();
        Point_2 point(xx, yy);
        list_of_points.push_back(point);  // Add the point to the list
    }

    return list_of_points;
}

Point_2 getMidPoint(const Segment& line)
{
    /**
     * Returns the mid point of the given line
     */
    double x1, y1, x2, y2, mx, my;
    x1 = line.source().x();
    y1 = line.source().y();
    x2 = line.target().x();
    y2 = line.target().y();

    mx = (x1 + x2) / 2.0;  // Calculate the mid-point of the line
    my = (y1 + y2) / 2.0;

    Point_2 point(mx, my);
    return point;
}

Point_2 getCentroid(const std::list<Point_2>& points)
{
    /**
     * Returns the centroid of the given list of points
     */
    double sum_x = 0.0, sum_y = 0.0;
    int count = 0;
    for (auto it = points.begin(); it != points.end(); it++) {
        count++;
        sum_x += it->x();
        sum_y += it->y();
    }
    Point_2 center(sum_x / count, sum_y / count);  // Getting the average of the points
    return center;
}

bool comparePoints(const Point_2& a, const Point_2& b)
{
    /**
     * Compare points based on there angle with centroid
     * https://stackoverflow.com/questions/6989100/sort-points-in-clockwise-order
     */

    if (a.x() - centroid.x() >= 0 && b.x() - centroid.x() < 0) return true;
    if (a.x() - centroid.x() < 0 && b.x() - centroid.x() >= 0) return false;
    if (a.x() - centroid.x() == 0 && b.x() - centroid.x() == 0) {
        if (a.y() - centroid.y() >= 0 || b.y() - centroid.y() >= 0) return (a.y() > b.y());
        return (b.y() > a.y());
    }

    int det, d1, d2;

    // Compute the cross product of vectors (centroid -> a) x (centroid -> b)
    det = (int)((a.x() - centroid.x()) * (b.y() - centroid.y()) -
                (b.x() - centroid.x()) * (a.y() - centroid.y()));
    if (det < 0) return true;
    if (det > 0) return false;

    // Points a and b are on the same line from the center
    // Check which point is closer to the center
    d1 = (int)((a.x() - centroid.x()) * (a.x() - centroid.x()) +
               (a.y() - centroid.y()) * (a.y() - centroid.y()));
    d2 = (int)((b.x() - centroid.x()) * (b.x() - centroid.x()) +
               (b.y() - centroid.y()) * (b.y() - centroid.y()));
    return d1 > d2;
}

std::list<Point_2> sortClockwise(std::list<Point_2> points)
{
    /**
     * Sort the given points in the list in a clockwise order.
     */
    centroid = getCentroid(points);
    points.sort(comparePoints);
    return points;
    // det = (a.x - centroid.x) * (b.y - centroid.y) - (b.x - centroid.x) * (a.y - centroid.y)
}
