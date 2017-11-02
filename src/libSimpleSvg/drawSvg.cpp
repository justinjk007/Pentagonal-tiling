#include "drawSvg.hpp"

using namespace svg;

// Demo page shows sample usage of the Simple SVG library.

void drawSvgfile(const int& w, const int& h, const std::list<Segment>& poly_mess)
{
    std::string file_name = "polygons.svg";

    Dimensions dimensions(h, w);
    Document doc(file_name, Layout(dimensions, Layout::BottomLeft));

    // Balck image border.
    Polygon border(Stroke(1, Color::Black));
    border << svg::Point(0, 0) << svg::Point(dimensions.width, 0)
           << svg::Point(dimensions.width, dimensions.height) << svg::Point(0, dimensions.height);
    doc << border;

    for (auto it = poly_mess.begin(); it != poly_mess.end();) {
        Point_2 single_pentagon[5];  // Get the points needed for one pentagon
        for (int i = 0; i < 5; ++i) {
            single_pentagon[i] = it->source();
            it++;
        }

        doc << (Polygon(Color(200, 160, 220), Stroke(.5, Color(150, 160, 200)))
                << svg::Point(20, 70) << svg::Point(25, 72) << svg::Point(33, 70)
                << svg::Point(35, 60) << svg::Point(25, 55) << svg::Point(18, 63));
    }

    doc.save();
}
