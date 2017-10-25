/**
 * Author: Justin Kaipada (c) This file couples together the DE
 * algorithm and fitness function written by me to perform tests on
 * pentagonal tiling
 */

#include <chrono>
#include <thread>
#include "CalculateGap.hpp"
#include "DE/de.h"

/**
 * Note: "de.h" file mentions the prototypes of two classes
 * searchAlgorithm and LSHADE. LSHADE is the actual Optimization
 * algorithm and searchAlgorithm class are further improvements on the
 * optimization algorithm like region constraints and more constraints
 * after mutation
 */

int g_problem_size;
unsigned int g_max_num_evaluations;

int g_pop_size;
double g_arc_rate;
int g_memory_size;
double g_p_best_rate;

ofstream outFile;

using namespace std;

int main()
{
    g_problem_size        = 9;                       // dimension size.
    g_max_num_evaluations = g_problem_size * 10000;  // available number of fitness evaluations

    // random seed is selected based on time according to competition rules
    srand((unsigned)time(NULL));

    g_pop_size    = (int)round(sqrt(g_problem_size) * log(g_problem_size) * 25);
    g_memory_size = 5;
    g_arc_rate    = 1;
    g_p_best_rate = 0.25;

    cout << "\n-------------------------------------------------------" << endl;
    cout << "Dimension size = " << g_problem_size << ", g_pop_size[_INIT] = " << g_pop_size << "\n"
         << endl;

    searchAlgorithm* algorithm = new LSHADE();
    algorithm->run();
    delete algorithm;

    outFile << endl;
    return 0;
}
