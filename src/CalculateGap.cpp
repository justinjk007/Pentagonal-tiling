#include "CalculateGap.hpp"
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <thread>

using namespace std;

double CalculateGap::getGap(const Tile& tile)
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
            gap_list[gap_index] = this->calculateGap(tile, i, j);
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

void CalculateGap::getGap(double* x, double* fitness, const long& iteration_num)
{
    /**
     * This is an overloaded variant of getGap that takes in the args
     * as a vector and append the the gap to the fitness vector which
     * is the the second argument.
     */
    bool alarm = false;  // This flag is used to represent the validity of the current tile
    double min_gap;
    Tile tile = {x[0], x[1], x[2], x[3], x[4], x[5], x[6]};  // Create a tile

    // Send the information about the tile to the front-end GUI -----------------------------------
    QString tile_info =
        QString("Sides: " + QString::number(x[0], 'g', 5) + " " + QString::number(x[1], 'g', 5) +
                " " + QString::number(x[2], 'g', 5) + " " + QString::number(x[3], 'g', 5) + "\n" +
                "Angles: " + QString::number(x[4], 'g', 5) + " " + QString::number(x[5], 'g', 5) +
                " " + QString::number(x[6], 'g', 5));
    emit tileInfo(tile_info);
    emit tileInfo(QString("Iteration version: " + QString::number(iteration_num)));
    // Send the information about the tile to the front-end GUI -----------------------------------

    fillDimensions(tile);  // Fill all the dimensions in
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
                gap_list[gap_index] = this->calculateGap(tile, i, j);
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
    // Send the information about the tile to the front-end GUI -----------------------------------
    QString min_gap_info = QString("<span style=\" color:green\"\\>") +
                           "Minimum gap is : " + QString::number(min_gap) + "</span>";
    fitness[0] = min_gap;
    emit tileInfo(min_gap_info);
    emit tileInfo(QString("\n"));
    emit minimumGap(iteration_num, min_gap);
    // Send the information about the tile to the front-end GUI -----------------------------------

    // Write information to file-----------------------------------
    output_file << "Sides: " << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << "\n";
    output_file << "Angles: " << x[4] << " " << x[5] << " " << x[6] << "\n";
    output_file << "Minimum gap is: " << min_gap << "\n\n";
    // Write information to file-----------------------------------
}

double CalculateGap::calculateGap(const Tile& tile, const int& i, const int& j)
{
    /**
     * This method integrates all the core methods into finding the gap
     * of the given polygon when tiled in many ways.
     */
    PrimitiveTile newSample(tile);
    newSample.drawPentagon(i, j);  // Draw the first pentagon
    // Send the information about the tile to the front-end GUI -----------------------------------
    std::vector<Line> lines_in_vector{std::begin(newSample.lines), std::end(newSample.lines)};
    emit sideCreated(lines_in_vector);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // Send the information about the tile to the front-end GUI -----------------------------------
    double tile_area = getPolygonArea(newSample.lines) * 8.0;
    Link link(tile.side[i], tile.side[j]);
    if (newSample.isLinkable(link)) {
        newSample.drawPentagon(i, j);
        newSample.doTiling(0, 0, 0, 0);  // TODO pass the appropiate
                                         // arguments when transition
                                         // is programmable, meaning
                                         // when you increase the
                                         // primitive tile size.
        // Send the information about the tile to the front-end GUI
        // -----------------------------------
        emit tilingCreated(newSample.lines);
        // Send the information about the tile to the front-end GUI
        // -----------------------------------
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
