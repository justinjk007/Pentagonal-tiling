#include "mainwindow.h"
#include <QTextBrowser>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <chrono>
#include <thread>
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
