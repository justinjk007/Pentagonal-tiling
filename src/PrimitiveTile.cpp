#include "PrimitiveTile.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "CalculateGap.hpp"
#include "myGeometry.hpp"

using namespace std;

bool PrimitiveTile::isLinkable(Link link)
{
    /**
     * Check if the sides are linkable
     */
    if (!(link.from.value == link.to.value))
        return false;
    else
        return true;
}

void PrimitiveTile::addTile(int from, int to)
{
    /**
     * Add a tile to the primitive tile after saving the combination of
     * the side used to connect it.
     */
    this->connector_sides.push_back(from);
    this->connector_sides.push_back(to);
    this->size += 1;
}

void PrimitiveTile::del()
{
    /**
     * Resets the contents of the primitiveTile.
     */
    this->lines.clear();  // Delete the contents of the list
    this->size = 1;
}

Tile PrimitiveTile::createPentagon()
{
    /**
     * This method tries to create the correct pentagon from the 7 dimensions we
     * have, this way producing less errors than trying to guess all 10
     * dimensions incorrectly.  Here the inputted tile has only seven dimensions
     * we will fill the others.
     */
    PrimitiveTile newSample(this->pentagon);
    newSample.drawPentagon(2, 2);  // Keep this 2,2 always. This way the correct
                                   // sides and angles are referenced.
    // Create CGAL polygon for validation
    vector<Point_2> points = getPointsFromLines(newSample.lines);  // Returns the start points

	///////////////////////////////////////////////////
	// Integrate GUI here, pass the points vector above into setupDrawingParameters function 
	//before calling the main of the GUI for execution.
	// This should place a call to the GUI every time the points change.
	// Draw the polygon to assist visual debugging.
	

	///////////////////////////////////////////////////

    if (!validatePolygon(points)) {
        throw std::logic_error("THE PENTAGON CREATED WAS NOT CONVEX!");
    }

    // Now to find the missing dimensions
    // Firstly, find the missing length
    double side_ea                   = sqrt(CGAL::squared_distance(points[4], points[0]));
    newSample.pentagon.side[4].value = side_ea;

    // Secondly find the missing angles
    double diagonal1 = sqrt(CGAL::squared_distance(points[0], points[3]));
    double diagonal2 = sqrt(CGAL::squared_distance(points[4], points[1]));
    double angle_e   = getMiddleAngle(newSample.pentagon.side[3].value,
                                    newSample.pentagon.side[4].value, diagonal1);
    double angle_a   = getMiddleAngle(newSample.pentagon.side[4].value,
                                    newSample.pentagon.side[0].value, diagonal2);
    newSample.pentagon.angle[4] = angle_e;
    newSample.pentagon.angle[0] = angle_a;
    return newSample.pentagon;
}

void PrimitiveTile::drawPentagon(int from, int to)
{
    /**
     * This was hard work okay, this draws the pentagon meaning they give out
     * the co-ordinates from the lengths and angles if a pentagon. Parameters
     * are the side conneted from and to of a new pentagon.
     */
    Line first_line;
    Line current_line;
    Line diagonal;  // The line that connects the 1st and the end of the 2nd line.
    Line next_line;
    double next_angle      = 0.0;
    double diagonal_angle  = 0.0;
    double diagonal_length = 0.0;
    Point origin           = {0.0, 0.0};
    int index              = 0;
    int type1              = 0;
    int type2              = 0;
    int i                  = 1;  // Becuase we are already finding line 1 here
    if (!this->lines.empty()) {
        /**
         * This means we already have a pentagon or more, so we are
         * connecting a new pentagon to it by starting to draw from
         * one of its side. So the first line of the new pentagon will
         * be one of the sides of the last pentagon.
         */
        index                   = to % 5;  // This is done to rotate the first pentagon
        list<Line>::iterator it = this->lines.begin();
        advance(it, 2);
        current_line = *it;
        current_line = current_line.reverse();
        this->lines.push_back(current_line);  // Add the line discovered to the list of line we have
        first_line = current_line;
    } else {
        /**
         * If we are here that means we haven't drawn any lines yet so
         * we are starting from scratch, so for the first line we are
         * just drawing a line of the length we need on the x-axis
         * itslef.
         */
        index        = (from + 3) % 5;  // This is done to rotate the first pentagon
        current_line = current_line.getLineWithRespectTo(origin, this->pentagon.side[index].value);
        this->lines.push_back(current_line);
        first_line = current_line;
    }
    index = (index + 1) % 5;  // Wraparound like a circle array
    while (i < 4) {
        next_angle      = this->pentagon.angle[index];
        diagonal_length = getThirdSide(this->pentagon.side[(index + 4) % 5],
                                       this->pentagon.side[index], next_angle);
        diagonal_angle  = getOtherAngle(this->pentagon.side[(index + 4) % 5],
                                       this->pentagon.side[index], next_angle, 'a');
        diagonal  = current_line.getLineWithRespectTo(diagonal_angle, diagonal_length, type1, 'd');
        next_line = current_line.getLineWithRespectTo(180.0 - next_angle,
                                                      this->pentagon.side[index].value, type2, 's');
        double diff = diagonal.target.x - next_line.target.x;
        if (diff <= 0.1 && diff >= -0.1) {
            type1 = 0;  // Reset types after every line
            type2 = 0;  // Reset types after every line
            this->lines.push_back(next_line);
            current_line = next_line;
            ++i;
            index = (index + 1) % 5;  // Wraparound like a circle array
        } else {
            if (type1 == 0 && type2 == 0) {
                type1 = 1;
                continue;
            } else if (type1 == 1 && type2 == 0) {
                type2 = 1;
                continue;
            } else if (type1 == 1 && type2 == 1) {
                type1 = 0;
                continue;
            } else {
                std::cout << "*****************************************************************\n";
                std::cout << "All options for finding co-ordinates covered, exiting abnormally!\n";
                std::cout << "*****************************************************************\n";
		this_thread::sleep_for(std::chrono::seconds(1));
                exit(1);
            }
        }
    }
    // Now connect the last line drawn to the first line to complete the pentagon
    current_line        = current_line.reverse();
    current_line.target = first_line.source;  // Start and end of a pentagon should be the same
    this->lines.push_back(current_line);      // Add the modified line to the end
}

void PrimitiveTile::drawPentagonRev(int from, int to)
{
    /**
     * This draw the pentagon in Reverse
     */
    // TODO Implement this
}

void PrimitiveTile::writeToFile()
{
    /**
     * Write the lines list to file so it can be plotted for debugging
     * and viewing the creation
     */
    ofstream myfile;
    string file_name = "example.csv";
    myfile.open(file_name, std::ios_base::app);
    list<Line>::iterator it      = this->lines.begin();
    list<Line>::iterator temp_it = it;  // Temporary storage fo the main iterator
    int i                        = 0;
    Point i_need_this            = this->lines.begin()->source;
    while (it != this->lines.end()) {
        myfile << it->source.x << "," << it->source.y << "\n";
        temp_it = it;
        ++it;
        i += 1;
        if (i % 5 == 0) {
            temp_it--;
            myfile << i_need_this.x << "," << i_need_this.y << "\n";
            advance(temp_it, 2);
            if (temp_it != this->lines.end()) i_need_this = temp_it->source;
        }
    }
    myfile.close();
}

void PrimitiveTile::writeToFileRaw()
{
    /**
     * Write the lines list to file in raw, meaning the coordinates of
     * points of each line in the list, this is just for viewing and not
     * for plotting.
     */
    ofstream myfile;
    string file_name = "rawData.csv";
    myfile.open(file_name);
    myfile << "x,y\n";
    list<Line>::iterator it = this->lines.begin();
    while (it != this->lines.end()) {
        myfile << it->source.x << "," << it->source.y << "\n";
        myfile << it->target.x << "," << it->target.y << "\n";
        ++it;
    }
    myfile.close();
}

void PrimitiveTile::writeToFileRaw(std::list<Line> this_lines)
{
    /**
     * Write the lines list to file in raw, meaning the coordinates of
     * points of each line in the list, this is just for viewing and not
     * for plotting.
     */
    ofstream myfile;
    string file_name = "rawData.csv";
    myfile.open(file_name);
    myfile << "x,y\n";
    list<Line>::iterator it = this_lines.begin();
    while (it != this_lines.end()) {
        myfile << it->source.x << "," << it->source.y << "\n";
        myfile << it->target.x << "," << it->target.y << "\n";
        ++it;
    }
    myfile.close();
}

void PrimitiveTile::writeToFileRaw(std::list<Segment> this_lines)
{
    /**
     * Write the lines list to file in raw, meaning the coordinates of
     * points of each line in the list, this is just for viewing and not
     * for plotting.
     */
    ofstream myfile;
    string file_name = "rawData.csv";
    myfile.open(file_name);
    myfile << "x,y\n";
    list<Segment>::iterator it = this_lines.begin();
    while (it != this_lines.end()) {
        myfile << it->source().x() << "," << it->source().y() << "\n";
        myfile << it->target().x() << "," << it->target().y() << "\n";
        ++it;
    }
    myfile.close();
}

void PrimitiveTile::draw()
{
    /**
     * This method will call the python script that shows the plot
     */
    system("python plot_lines.py");
}

std::list<Line> PrimitiveTile::translate(double t_x, double t_y, std::list<Line> tile)
{
    list<Line>::iterator it;
    for (it = tile.begin(); it != tile.end(); ++it) {
        // Translation rightwards is applied here
        it->source.x += t_x;
        it->source.y += t_y;
        it->target.x += t_x;
        it->target.y += t_y;
    }
    return tile;
}

void PrimitiveTile::doTiling(double t_x1, double t_y1, double t_x2, double t_y2)
{
    /**
     * This method does simple tiling by translating the primitive tile
     * to the right once, then upwards then upwards and rightwards.
     */
    std::list<Line> original_p_tile =
        this->lines;              // Stores the lines of the original primitivetile.
    std::list<Line> temp_p_tile;  // Stores the original temporarily for translation.
    std::list<Line> last_p_tile;  // Stores the lines last drawn primitivetile
    list<Line>::iterator it = this->lines.begin();

    // Get the translation rightwards
    it          = this->lines.begin();
    double tpx1 = it->target.x;
    double tpy1 = it->target.y;
    advance(it, 3);
    double tpx2 = it->target.x;
    double tpy2 = it->target.y;
    t_x1        = tpx1 - tpx2;
    t_y1        = tpy1 - tpy2;
    // Get the translation rightwards

    // Get the translation upwards
    it   = this->lines.begin();
    tpx1 = it->source.x;
    tpy1 = it->source.y;
    advance(it, 9);
    tpx2 = it->source.x;
    tpy2 = it->source.y;
    t_x2 = tpx2 - tpx1;
    t_y2 = tpy2 - tpy1;
    // Get the translation upwards

    temp_p_tile = original_p_tile;
    temp_p_tile = translate(t_x1, t_y1, temp_p_tile);    // Translate right
    this->lines.splice(this->lines.end(), temp_p_tile);  // Append main list with temp_list
    this->count++;
    temp_p_tile = original_p_tile;
    temp_p_tile = translate(t_x2, t_y2, temp_p_tile);  // Translate up
    last_p_tile = temp_p_tile;
    this->lines.splice(this->lines.end(), temp_p_tile);  // Append main list with temp_list
    this->count++;
    temp_p_tile = translate(t_x1, t_y1, last_p_tile);    // Translate right and up
    this->lines.splice(this->lines.end(), temp_p_tile);  // Append main list with temp_list
    this->count++;
}

std::vector<Point_2> PrimitiveTile::getPointsFromLines(std::list<Line> lines)
{
    /**
     * Returns the source points of everyline on the given list, which can
     * be then used for other functions like getPolygonArea() and even
     * for getting the concave hull of a set of lines or points
     */
    std::vector<Point_2> list_of_points;  // Stores the lines of the original primitivetile.
    for (list<Line>::iterator it = lines.begin(); it != lines.end(); ++it) {
        double x = it->source.x;
        double y = it->source.y;
        Point_2 point(x, y);
        list_of_points.push_back(point);
    }
    return list_of_points;
}
