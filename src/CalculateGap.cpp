#include "CalculateGap.hpp"
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <list>

using namespace std;

double getGap(const Tile& tile)
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

void getGap(double* x, double* fitness)
{
    /**
     * This is an overloaded variant of getGap that takes in the args
     * as a vector and append the the gap to the fitness vector which
     * is the the second argument.
     */
    bool alarm = false;  // This flag is used to represent the validity of the current tile
    double min_gap;
    Tile tile = {x[0], x[1], x[2], x[3], x[4], x[5], x[6]};  // Create a tile
    // Set the number of decimal to be shown
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);
    cout << "Sides:  " << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << "\n";
    cout << "Angles: " << x[4] << " " << x[5] << " " << x[6] << "\n";
    fillDimensions(tile); // Fill all the dimensions in
    if (!validateTile(tile)) {
	printf("\nThe tile inputted was invalid");
	alarm   = true;
	min_gap = 100;
	// exit(1);
    }

    if (!alarm) {
        int gap_index = 0;
        double gap_list[25];
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                gap_list[gap_index] = calculateGap(tile, i, j);
                gap_index++;
            }
        }

        // Returning the minimumgap in the gap list
        min_gap           = gap_list[0];
        int gap_list_size = (sizeof gap_list) / (sizeof gap_list[0]);
        for (int i = 0; i < gap_list_size; ++i) {
            if (gap_list[i] >= 0 && gap_list[i] < min_gap) min_gap = gap_list[i];
        }
    }
    // Set the number of decimal to be shown
    cout << "\nMin gap is " << min_gap << "\n";

    this_thread::sleep_for(std::chrono::seconds(1));  // TODO : Remove this during release
    fitness[0] = min_gap;
}

double calculateGap(const Tile& tile, const int& i, const int& j)
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
        newSample.doTiling(0, 0, 0, 0);  // TODO pass the appropiate
                                         // arguments when transition
                                         // is programmable, meaning
                                         // when you increase the
                                         // primitive tile size.
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
