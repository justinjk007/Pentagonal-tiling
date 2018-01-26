#include "mainwindow.h"
#include <QTextBrowser>
#include <QThread>
#include <QWidget>
#include <QtCore>
#include <QtGui>
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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Setup the QChart Widget on the bottom left of the window
    QLineSeries* series = new QLineSeries();
    this->fitness_line_series = series;
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
    this->fitness_chart_view = fitness_graph;
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

void MainWindow::updateFitnessGraph(const long& iteration_version, const double& fitness)
{
    /**
     * This method updates the content of Fitnessgraph
     */
    this->fitness_line_series->append(iteration_version,fitness);
    this->fitness_chart_view->repaint();
}

void MainWindow::on_start_btn_clicked()
{
    QThread* worker_thread = new QThread;
    Worker* new_worker_obj = new Worker();
    new_worker_obj->moveToThread(worker_thread);
    connect(new_worker_obj, &Worker::updatePentagonInfo, this, &MainWindow::updatePentagonInfo);
    connect(new_worker_obj, &Worker::updateFitnessGraph, this, &MainWindow::updateFitnessGraph);
    connect(worker_thread, SIGNAL(started()), new_worker_obj, SLOT(mainProcess()));
    // Delete thread signals
    connect(new_worker_obj, SIGNAL(finished()), worker_thread, SLOT(quit()));
    connect(new_worker_obj, SIGNAL(finished()), new_worker_obj, SLOT(deleteLater()));
    connect(worker_thread, SIGNAL(finished()), worker_thread, SLOT(deleteLater()));
    // Finally start the thread
    worker_thread->start();
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
