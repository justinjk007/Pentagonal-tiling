#include "mainwindow.h"
#include <QTextBrowser>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <chrono>
#include <thread>
#include "CalculateGap.hpp"
#include "de.h"
#include "ui_mainwindow.h"

/**
 * Note: "de.h" file mentions the prototypes of two classes
 * searchAlgorithm and LSHADE. LSHADE is the actual Optimization
 * algorithm and searchAlgorithm class are further improvements on the
 * optimization algorithm like region constraints and more constraints
 * after mutation
 */

using namespace QtCharts;
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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePentagonInfo(const QString& content)
{
    /**
     * This method updates information about the pentagon in the text
     * browser on the top right of the main program window. Appending
     * whatever is given as the argument
     */
    ui->pentagon_info->append(content);
}

void MainWindow::updateFitnessGraph()
{
    /**
     * This method updates the content of Fitnessgraph
     */
    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3)
            << QPointF(20, 2);

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->setTitle("Fitness of generated samples");

    QChartView* fitness_graph = new QChartView(chart);
    fitness_graph->setRenderHint(QPainter::Antialiasing);
    fitness_graph->setMinimumSize(300, 100);
    ui->left_side->addWidget(fitness_graph);
}

void MainWindow::on_start_btn_clicked()
{
    /**
     * Implements the start button, here we initialize variables for
     * Differential evolution and start the algorithm
     */
    g_problem_size        = 7;                       // dimension size.
    g_max_num_evaluations = g_problem_size * 10000;  // available number of fitness evaluations
    // random seed is selected based on time according to competition rules
    srand((unsigned)time(NULL));
    g_pop_size    = (int)round(sqrt(g_problem_size) * log(g_problem_size) * 25);
    g_memory_size = 5;
    g_arc_rate    = 1;
    g_p_best_rate = 0.25;
    // Set domain for each dimension
    domain_min = 90;
    domain_max = 120;
    // Display information
    QString problem_size = QString::number(g_problem_size);
    QString pop_size = QString::number(g_pop_size);
    QString content =
        QString("<span style=\" font-size:10pt; color:blue; font-weight:200; font-family:Hack,Arial;\"\\>") +
        "Dimension size = " + problem_size + ", g_pop_size[_INIT] = " + pop_size+ "</span>";
    updatePentagonInfo(content);  // Update data
    // Finally start DE
    // searchAlgorithm* algorithm = new LSHADE();
    // algorithm->run();
    // delete algorithm;
    // outFile << endl;
}

void MainWindow::on_stop_btn_clicked()
{
}

void MainWindow::on_pause_btn_clicked()
{
}

void MainWindow::on_resume_btn_clicked()
{
}

void MainWindow::lineCreated(Segment line)
{

}
