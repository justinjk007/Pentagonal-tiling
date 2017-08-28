#include "concaveHull.hpp"

template <class OutputIterator>
void alpha_edges(const Alpha_shape_2& A, OutputIterator out) {
    for (Alpha_shape_edges_iterator it = A.alpha_shape_edges_begin();
         it != A.alpha_shape_edges_end(); ++it) {
        *out++ = A.segment(*it);
    }
}

int getConcaveHull(std::list<Point_2> points) {
  /**
   * Reads a list of points and returns a list of segments
   * corresponding to the concave hull also known as α-Shape
   */

    Alpha_shape_2 A(points.begin(), points.end(), FT(10000), Alpha_shape_2::GENERAL);

    std::list<Segment> segments;
    alpha_edges(A, std::back_inserter(segments));

    std::cout << "Alpha Shape computed" << std::endl;
    std::cout << segments.size() << " alpha shape edges" << std::endl;
    std::cout << "Optimal alpha: " << *A.find_optimal_alpha(1) << std::endl;

    return 0;
}
