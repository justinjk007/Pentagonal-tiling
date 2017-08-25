#include "concaveHull.hpp"

template <class OutputIterator>
void alpha_edges(const Alpha_shape_2& A, OutputIterator out) {
    for (Alpha_shape_edges_iterator it = A.alpha_shape_edges_begin();
         it != A.alpha_shape_edges_end(); ++it) {
        *out++ = A.segment(*it);
    }
}

template <class OutputIterator>
bool file_input(OutputIterator out) {
  /**
   * Reads data from file, we won't be needing this tho, this will be
   * deleted in the long run
   */
    std::ifstream is("fin.dat", std::ios::in);

    if (is.fail()) {
        std::cerr << "unable to open file for input" << std::endl;
        return false;
    }

    int n;
    is >> n;
    std::cout << "Reading " << n << " points from file" << std::endl;
    CGAL::cpp11::copy_n(std::istream_iterator<Point>(is), n, out);

    return true;
}

int getConcaveHull() {
  /**
   * Reads a list of points and returns a list of segments
   * corresponding to the concave hull also known as α-Shape
   */
    std::list<Point> points;
    if (!file_input(std::back_inserter(points))) {
        return -1;
    }

    Alpha_shape_2 A(points.begin(), points.end(), FT(10000), Alpha_shape_2::GENERAL);

    std::list<Segment> segments;
    alpha_edges(A, std::back_inserter(segments));

    std::cout << "Alpha Shape computed" << std::endl;
    std::cout << segments.size() << " alpha shape edges" << std::endl;
    std::cout << "Optimal alpha: " << *A.find_optimal_alpha(1) << std::endl;

    return 0;
}
