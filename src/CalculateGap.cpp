#include "CalculateGap.hpp"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "PrimitiveTile.hpp"
#include "myGeometry.hpp"

const double PI = 3.14159265358979323846264338327950288;

using namespace std;

double getGap(Tile tile)
{
    /*
     * This is the main method that returns the gap minimum between the
     * tiles when arranged with any particular order. Current this only
     * calculates gap between primitive tiles of size 2. This returns
     * the minimum gap from the list of combinateions.
     */
    if (!validateTile(tile)) {
        exit(1);
        printf("\nThe tile inputted was invalid");
    }

    int gap_index = 0;
    double gap_list[25];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            gap_list[gap_index] = calculateGap(tile, i, j);
            gap_index++;
        }
    }

    // Returning the minimumgap in the gap list
    double min_gap    = gap_list[0];
    int gap_list_size = (sizeof gap_list) / (sizeof gap_list[0]);
    for (int i = 0; i < gap_list_size; ++i) {
        if (gap_list[i] >= 0 && gap_list[i] < min_gap) min_gap = gap_list[i];
    }
    return min_gap;
}

double getGap(dd a, dd b, dd c, dd d, dd e, dd f, dd g, dd h, dd i)
{
    /**
     * This is an overloaded variant of getGap(Tile) that takes in the raw arguments instead of a
     * tile
     */

    Tile tile = {a, b, c, d, e, f, g, h, i}; // Create a tile structure with the passed arguments

    if (!validateTile(tile)) {
        exit(1);
        printf("\nThe tile inputted was invalid");
    }

    int gap_index = 0;
    double gap_list[25];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            gap_list[gap_index] = calculateGap(tile, i, j);
            gap_index++;
        }
    }

    // Returning the minimumgap in the gap list
    double min_gap    = gap_list[0];
    int gap_list_size = (sizeof gap_list) / (sizeof gap_list[0]);
    for (int i = 0; i < gap_list_size; ++i) {
        if (gap_list[i] >= 0 && gap_list[i] < min_gap) min_gap = gap_list[i];
    }
    return min_gap;
}

void getGap(double* x, double* f)
{
    f[0] = 0.0;
    // sr_func(x, z, nx, Os, Mr, 1.0, s_flag, r_flag); /* Shift and Rotate */

    Tile tile = {x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]};  // Create a tile

    tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};  // Create a tile

    // Tile tile = {32.72,  73.59,  78.67, 49.06, 57.68, 122.03, 115.73, 84.19, 95.81, 122.23};  //
    // Type 1.1

    if (!validateTile(tile)) {
        printf("\nThe tile inputted was invalid\n");
        exit(1);
    }

    // std::cout << "Here2\n";
    int gap_index = 0;
    double gap_list[25];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            gap_list[gap_index] = calculateGap(tile, i, j);
            gap_index++;
        }
    }

    // std::cout << "Here2\n";
    // Finding the minimumgap in the gap list
    double min_gap    = gap_list[0];
    int gap_list_size = (sizeof gap_list) / (sizeof gap_list[0]);
    for (int i = 0; i < gap_list_size; ++i) {
        if (gap_list[i] >= 0 && gap_list[i] < min_gap) min_gap = gap_list[i];
    }

    // std::cout << "Here3\n";

    // for (int i = 0; i < nx; i++) {
    f[0] = min_gap;
    // }

    // std::cout << "Here4\n";
    // std::cout << "Testing count: "<< testing_count <<"\n";
}

double calculateGap(Tile tile, int i, int j)
{
    /**
     * This method integrates all the core methods into finding the gap
     * of the given polygon when tiled in many ways.
     */
    PrimitiveTile newSample(tile);
    newSample.drawPentagon(i, j);  // Draw the first pentagon
    double tile_area = getPolygonArea(newSample.lines) * 8.0;
    Link link(tile.side[i], tile.side[j]);
    if (newSample.isLinkable(link)) {
        newSample.drawPentagon(i, j);
        newSample.doTiling(0, 0, 0, 0);  // TODO pass the
                                         // appropiate arguments
                                         // when transition is
                                         // programmable
        std::list<Segment> boundary        = removeInnerLines(newSample.lines);
        std::list<Point_2> boundary_points = getSources(boundary);
        boundary_points                    = sortClockwise(boundary_points);
        double total_area                  = getPolygonArea(boundary_points);
        double gap                         = total_area - tile_area;
        // newSample.writeToFileRaw();
        return abs(gap);
    } else
        return -101;
}

bool validateTile(Tile tile)
{
    /*
     * This method returns whether the Tile inputted is valid or not.
     * This method is used by getgap()
     */
    double max_side  = getMaxSide(tile);
    double max_angle = getMaxAngle(tile);
    if (max_angle <= 180.00)
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
    else
        return false;
}

double getMaxSide(Tile tile)
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

double getMaxAngle(Tile tile)
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

double getThirdSide(Side a, Side b, double angle)
{
    /*
     * This method returns the third side of the triangle formed inside
     * a polygon used for area calculating purposes. Angle should be
     * passed in degrees
     */
    angle = angle * PI / 180.0;
    double side_c =
        sqrt((a.value * a.value) + (b.value * b.value) - (2.0 * a.value * b.value * cos(angle)));
    return side_c;
}

double getOtherAngle(Side a, Side b, double angle_b, char which_angle)
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

double getTriangleArea(double a, double b, double c)
{
    /*
     * This method returns the Area of the triagle using Heron's
     * Formulae
     */
    double S    = (a + b + c) / 2.0;
    double area = sqrt(S * (S - a) * (S - b) * (S - c));
    return area;
}

double getTileArea(Tile tile)
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

double getPolygonArea(std::list<Line> polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * lines that create the polygon/polygons, sorted clockwise or
     * anti-clockwise
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;

    for (list<Line>::iterator it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->start.x;
        y1 = it->start.y;
        x2 = it->end.x;
        y2 = it->end.y;
        sum += x1 * y2;
        diff += y1 * x2;
    }

    area = (1.0 / 2.0) * abs((sum - diff));
    return area;
}

double getPolygonArea(std::list<Segment> polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * Segment_2d defined in cgal that creates the polygon/polygons
     * sorted clockwise or anti-clockwise
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;

    for (list<Segment>::iterator it = polygon.begin(); it != polygon.end(); it++) {
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

double getPolygonArea(std::list<Point_2> polygon)
{
    /**
     * This method implements calculating the area of a polygon using
     * the shoelace formula. The list the passed should contain the
     * points that create the polygon/polygons.
     */
    double sum = 0.0, diff = 0.0, area = 0.0;
    double x1, y1, x2, y2;
    for (list<Point_2>::iterator it = polygon.begin(); it != polygon.end();) {
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
        for (list<Line>::iterator it = lines.begin(); it != lines.end(); ++it)
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
        for (list<Point_2>::iterator it = points.begin(); it != points.end(); ++it)
            if (comparePoint(point1, *it))  // Compare to see if same Point_2s exists
                new_points = removePoint(new_points, point1);
    }

    return new_points;
}

std::list<Line> removeLine(std::list<Line> lines, Line val)
{
    /**
     * Override function for list::remove rewritten for list<Line>
     */
    for (list<Line>::iterator it = lines.begin(); it != lines.end();) {
        if (compareLine(val, *it))  // If same lines exists
            it = lines.erase(it);
        else
            ++it;
    }
    return lines;
}

std::list<Point_2> removePoint(std::list<Point_2> points, Point_2 val)
{
    /**
     * Override function for list::remove rewritten for list<Point_2>
     */
    for (list<Point_2>::iterator it = points.begin(); it != points.end();) {
        if (comparePoint(val, *it))  // If same lines exists
            it = points.erase(it);
        else
            ++it;
    }
    return points;
}

bool comparePoint(Point_2 a, Point_2 b)
{
    /**
     * Compare points to see if they are equal.
     */
    double diff1 = a.x() - b.x();
    double diff2 = a.y() - b.y();
    if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04) return true;
    return false;
}

void printData(std::list<Line> polygon)
{
    /**
     * Prints out the given list of lines
     */
    cout << "Displaying list of Lines\n";
    double x1, y1, x2, y2;
    for (list<Line>::iterator it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->start.x;
        y1 = it->start.y;
        x2 = it->end.x;
        y2 = it->end.y;
        printf("(%f, %f)  ---   (%f, %f)\n", x1, y1, x2, y2);
    }
}

void printData(std::list<Segment> polygon)
{
    /**
     * Prints out the given list of lines
     */
    cout << "Displaying list of Segments\n";
    double x1, y1, x2, y2;
    for (list<Segment>::iterator it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->source().x();
        y1 = it->source().y();
        x2 = it->target().x();
        y2 = it->target().y();
        printf("(%f, %f)  ---   (%f, %f)\n", x1, y1, x2, y2);
    }
}

void printData(std::list<Point_2> polygon)
{
    /**
     * Prints out the given list of points
     */
    cout << "Displaying list of Point_2s\n";
    double x1, y1;
    for (list<Point_2>::iterator it = polygon.begin(); it != polygon.end(); it++) {
        x1 = it->x();
        y1 = it->y();
        printf("(%f, %f)\n", x1, y1);
    }
}

std::list<Point_2> getSources(std::list<Line> lines)
{
    /**
     * Returns a list of points representing the source of each line given
     * Used to find the Bounding box of the given line segments basically.
     */
    std::list<Point_2> list_of_points;

    for (list<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
        double xx = it->start.x;
        double yy = it->start.y;
        Point_2 point(xx, yy);
        list_of_points.push_back(point);  // Add the point to the list
    }

    return list_of_points;
}

std::list<Point_2> getSources(std::list<Segment> lines)
{
    /**
     * Returns a list of points representing the source of each line given
     * Used to find the Bounding box of the given line segments basically.
     */
    std::list<Point_2> list_of_points;

    for (list<Segment>::iterator it = lines.begin(); it != lines.end(); it++) {
        double xx = it->source().x();
        double yy = it->source().y();
        Point_2 point(xx, yy);
        list_of_points.push_back(point);  // Add the point to the list
    }

    return list_of_points;
}

Point_2 getMidPoint(Segment line)
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

Point_2 getCentroid(std::list<Point_2> points)
{
    /**
     * Returns the centroid of the given list of points
     */
    double sum_x = 0.0, sum_y = 0.0;
    int count = 0;
    for (list<Point_2>::iterator it = points.begin(); it != points.end(); it++) {
        count++;
        sum_x += it->x();
        sum_y += it->y();
    }
    Point_2 center(sum_x / count, sum_y / count);  // Getting the average of the points
    return center;
}

bool comparePoints(Point_2 a, Point_2 b)
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
    det = (a.x() - centroid.x()) * (b.y() - centroid.y()) -
          (b.x() - centroid.x()) * (a.y() - centroid.y());
    if (det < 0) return true;
    if (det > 0) return false;

    // Points a and b are on the same line from the center
    // Check which point is closer to the center
    d1 = (a.x() - centroid.x()) * (a.x() - centroid.x()) +
         (a.y() - centroid.y()) * (a.y() - centroid.y());
    d2 = (b.x() - centroid.x()) * (b.x() - centroid.x()) +
         (b.y() - centroid.y()) * (b.y() - centroid.y());
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
