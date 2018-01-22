/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP

#include <algorithm>
#include <list>
#include <vector>
#include "Link.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "boundaryDetection.hpp"
#include "cgal.hpp"
#include "myGeometry.hpp"

class PrimitiveTile
{
   public:
    std::list<Line> lines;           // Stores the lines of the boundaries primitive tile
    std::list<int> connector_sides;  // Stores the indexes of the sides connected.
    Tile pentagon;                   // Stores the measurements of the tile or pentagon used.
    int size;                        // This accounts for the number of tiles in the primitive tile.
    int count;  // Stores the number of primitivetile used in tiling or drawing.

    bool isLinkable(Link);
    Tile createPentagon();
    void drawPentagon(int, int);
    void drawPentagonRev(int, int);
    void addTile(int, int);
    void del();
    void writeToFile();
    void writeToFileRaw();
    void writeToFileRaw(std::list<Line>);
    void writeToFileRaw(std::list<Segment>);
    void draw();
    void doTiling(double, double, double, double);
    std::list<Line> translate(double, double, std::list<Line>);
    std::vector<Point_2> getPointsFromLines(std::list<Line>);  // Returns the start points
    PrimitiveTile() : size(1), count(1)
    {
    }
    PrimitiveTile(Tile tile) : pentagon(tile), size(1), count(1)
    {
    }
    ~PrimitiveTile()
    {
        this->lines.clear();
        this->connector_sides.clear();
        this->size  = 1;  // Obviously we need atleast one tile.
        this->count = 1;  // Obviously we need atleast one primitive tile.
    }
};

#endif /* PRIMITIVETILE_HPP */
