#include "Worker.hpp"
#include <QDebug>
#include <fstream>
#include <QString>
#include <chrono>
#include <thread>

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
    qDebug("run de method is called");
    QString content =
    QString(
    "<span style=\" font-size:12pt; font-weight:300; font-family:Hack,Arial;\"\\>") +
    "Main method has emitted a signal" + "</span>";
    emit updatePentagonInfo(content);
    content = QString("Waiting for 5 seconds");
    emit updatePentagonInfo(content);
    this_thread::sleep_for(std::chrono::seconds(5));
    content = QString("Done Waiting");
    emit updatePentagonInfo(content);
    emit finished();
}
