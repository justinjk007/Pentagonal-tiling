#include "CalculateGap.hpp"

#include "pentagonlib_Export.h" // Include the linker header file for the dll

typedef double dd; // Neat

// EXPORT_MACRO_NAME -> pentagonlib_EXPORT , This is generated in the CMake file

using namespace std;

pentagonlib_EXPORT double getFitness(dd a, dd b, dd c, dd d, dd e, dd f, dd g, dd h, dd i) {
  /**
   * This function was written as the API callable function using the
   * .dll file.
   */
  Tile pentagon = {a, b, c, d, e, f, g, h, i};
  double minimum_gap = getGap(pentagon);
  return minimum_gap;
}
