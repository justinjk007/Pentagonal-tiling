/**
 * Author: Justin Kaipada (c) This file couples together the DE
 * algorithm and fitness function written by me to perform tests on
 * pentagonal tiling
 */

#include "Worker.hpp"
#include <QString>
#include <chrono>
#include <fstream>
#include <thread>
#include "de.h"

/**
 * Note: "de.h" file mentions the prototypes of two classes
 * searchAlgorithm and LSHADE. LSHADE is the actual Optimization
 * algorithm and searchAlgorithm class are further improvements on the
 * optimization algorithm like region constraints and more constraints
 * after mutation
 */

using namespace std;

// Global Variables for DE library
int g_problem_size;
unsigned int g_max_num_evaluations;
double domain_max;
double domain_min;
int g_pop_size;
double g_arc_rate;
int g_memory_size;
double g_p_best_rate;

ofstream outFile;

void Worker::mainProcess()
{
    /**
     * This method integreates everything together , connecting the DE
     * and GUI together using Qt's signals and slot system. DE is ran
     * in a seperate thread than the GUI for smooth running and performance
     * reasons
     */

    g_problem_size        = 7;                       // dimension size.
    g_max_num_evaluations = g_problem_size * 10000;  // available number of fitness evaluations

    // random seed is selected based on time according to competition rules
    srand((unsigned)time(NULL));

    g_pop_size    = (int)round(sqrt(g_problem_size) * log(g_problem_size) * 25);
    g_memory_size = 5;
    g_arc_rate    = 1;
    g_p_best_rate = 0.25;

    domain_min = 90;
    domain_max = 120;

    // cout << "\n-------------------------------------------------------" << endl;
    // cout << "Dimension size = " << g_problem_size << ", g_pop_size[_INIT] = " << g_pop_size <<
    // "\n"
    //      << endl;

    QString content = QString("Dimension size =" + QString::number(g_problem_size));
    emit updatePentagonInfo(content);
    content = QString("pop_size =" + QString::number(g_pop_size) + "\n");
    emit updatePentagonInfo(content);

    CalculateGap* fitness_algo = new CalculateGap();

    // Connect signals
    connect(fitness_algo, &CalculateGap::tileInfo, this, &Worker::updatePentagonInfo);

    searchAlgorithm* algorithm     = new LSHADE();
    algorithm->fitness_algo_object = fitness_algo;
    algorithm->run();
    delete fitness_algo;
    delete algorithm;

    outFile << endl;
    emit finished();
}
