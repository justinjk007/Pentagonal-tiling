/**
 * Author: Justin Kaipada (c) This file couples together the DE
 * algorithm and fitness function written by me to perform tests on
 * pentagonal tiling
 */

#include "CalculateGap.hpp"
#include "DE/de.h"

double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

int g_function_number;
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
    int num_runs          = 51;  // number of runs
    g_problem_size        = 10;  // dimension size. please select from 10, 30, 50, 100
    g_max_num_evaluations = g_problem_size * 10000;  // available number of fitness evaluations

    // random seed is selected based on time according to competition rules
    srand((unsigned)time(NULL));

    g_pop_size    = (int)round(sqrt(g_problem_size) * log(g_problem_size) * 25);
    g_memory_size = 5;
    g_arc_rate    = 1;
    g_p_best_rate = 0.25;

    stringstream ss;
    ss << g_problem_size;
    string tmp(ss.str());
    string fileNameStr = "DeOutput" + tmp + ".dat";
    char fileName[500];
    strcpy(fileName, fileNameStr.c_str());
    outFile.open(fileName, ios::out);

    g_function_number = 5;
    cout << "\n-------------------------------------------------------" << endl;
    cout << "Function = " << g_function_number << ", Dimension size = " << g_problem_size
         << ", g_pop_size[_INIT] = " << g_pop_size << "\n"
         << endl;

    Fitness* bsf_fitness_array = (Fitness*)malloc(sizeof(Fitness) * num_runs);
    Fitness mean_bsf_fitness   = 0;
    Fitness std_bsf_fitness    = 0;

    for (int j = 0; j < num_runs; j++) {
        searchAlgorithm* alg = new LSHADE();
        bsf_fitness_array[j] = alg->run();
        cout << j + 1 << "th run, "
             << "error value = " << bsf_fitness_array[j] << endl;
        delete alg;
    }

    for (int j = 0; j < num_runs; j++) mean_bsf_fitness += bsf_fitness_array[j];
    mean_bsf_fitness /= num_runs;

    for (int j = 0; j < num_runs; j++)
        std_bsf_fitness += pow((mean_bsf_fitness - bsf_fitness_array[j]), 2.0);
    std_bsf_fitness /= num_runs;
    std_bsf_fitness = sqrt(std_bsf_fitness);

    cout << "\nFunction = " << g_function_number << ", Dimension size = " << g_problem_size
         << ",  mean = " << mean_bsf_fitness << ", std = " << std_bsf_fitness << endl;
    free(bsf_fitness_array);

    outFile << endl;
    return 0;
}
