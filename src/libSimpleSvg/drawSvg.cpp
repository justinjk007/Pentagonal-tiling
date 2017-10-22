#include "drawSvg.hpp"

using namespace svg;

// Demo page shows sample usage of the Simple SVG library.

void drawSvgfile(int h, int w, std::list<Segment> poly_mess)
{
    std::string file_name = "polygons.svg";

    Dimensions dimensions(h, w);
    Document doc(file_name, Layout(dimensions, Layout::BottomLeft));

    // Balck image border.
    SvgPolygon border(Stroke(1, Color::Black));
    border << SvgPoint(0, 0) << SvgPoint(dimensions.width, 0)
           << SvgPoint(dimensions.width, dimensions.height) << SvgPoint(0, dimensions.height);
    doc << border;

    doc << (SvgPolygon(Color(200, 160, 220), Stroke(.5, Color(150, 160, 200)))
            << SvgPoint(20, 70) << SvgPoint(25, 72) << SvgPoint(33, 70) << SvgPoint(35, 60)
            << SvgPoint(25, 55) << SvgPoint(18, 63));

    doc.save();
}
