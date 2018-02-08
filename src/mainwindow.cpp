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
    QSplineSeries* series = new QSplineSeries(this);
    QChart* chart         = new QChart();
    QFont arial("Arial", 9, QFont::Bold);
    chart->setTitleFont(arial);
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->setTitle("Fitness of generated samples");
    chart->setAnimationOptions(QChart::NoAnimation);
    QChartView* fitness_graph = new QChartView(chart);
    fitness_graph->setRenderHint(QPainter::Antialiasing);
    fitness_graph->setMinimumSize(300, 100);
    ui->left_side->addWidget(fitness_graph);
    // Set minimum and maximum range for the graph
    QValueAxis* axisX = new QValueAxis(this);
    QValueAxis* axisY = new QValueAxis(this);
    axisX->setRange(0, 10);
    axisY->setRange(0, 10);
    axisY->setTickCount(10);
    axisX->setTickCount(5);
    fitness_graph->chart()->setAxisX(axisX, series);
    fitness_graph->chart()->setAxisY(axisY, series);

    // Add these pointers to the window object so they can be accessed and updated later
    this->fitness_spline_series = series;
    this->fitness_chart_view    = fitness_graph;
    this->axisX                 = axisX;
    this->axisY                 = axisY;
    this->y_axis                = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fitness_spline_series;
    delete fitness_chart_view;
    delete axisX;
    delete axisY;
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

void MainWindow::updateFitnessGraph(const long& iteration, const double& fitness)
{
    /**
     * This method updates the content of Fitnessgraph
     */
    if (iteration > 70)
        // This will make sure that when the iteration gets bigger and
        // bigger we only get to the current and few old relevant
        // points in the fitness graph. This is what makes the
        // current point stay somewhat in the middle
        this->axisX->setRange(iteration - 70, iteration + 50);  // Add more space in the x-axis
    else
        this->axisX->setRange(0, iteration + 50);  // Add more space in the x-axis

    if (fitness > this->y_axis) {
        this->y_axis = fitness + 200;  // Add more space in y-axis if necessary
        this->axisY->setRange(0, this->y_axis);
    }

    // Remove some old points as they are out of the chart and can't be seen anymore
    if (iteration > 70) this->fitness_spline_series->remove(0);
    this->fitness_spline_series->append(iteration, fitness);  // Finally update the chart
}

void MainWindow::updatePentagonGeneration(std::vector<Line> pentagon)
{
    /**
     * This method updates the content of the Widget that draws the
     * pentagons line by line as they are created.
     */
    ui->pentagon_gen->updateLine(pentagon);
}

void MainWindow::updatePrimitiveTileGeneration(std::list<Line> tiling)
{
    /**
     * This method updates the content of the Widget that draws the
     * pentagons after tiling polygon by polygon as they are created.
     */
    ui->tiling_gen->updateTiling(tiling);
}

void MainWindow::on_start_btn_clicked()
{
    QThread* worker_thread = new QThread;
    Worker* new_worker_obj = new Worker();
    new_worker_obj->moveToThread(worker_thread);
    connect(new_worker_obj, &Worker::updatePentagonInfo, this, &MainWindow::updatePentagonInfo);
    connect(new_worker_obj, &Worker::updateFitnessGraph, this, &MainWindow::updateFitnessGraph);
    connect(new_worker_obj, &Worker::updatePentagonGeneration, this,
            &MainWindow::updatePentagonGeneration);
    connect(new_worker_obj, &Worker::updatePrimitiveTileGeneration, this,
            &MainWindow::updatePrimitiveTileGeneration);
    connect(worker_thread, SIGNAL(started()), new_worker_obj, SLOT(mainProcess()));
    // Delete thread signals when they are finished
    connect(new_worker_obj, SIGNAL(finished()), worker_thread, SLOT(quit()));
    connect(new_worker_obj, SIGNAL(finished()), new_worker_obj, SLOT(deleteLater()));
    connect(worker_thread, SIGNAL(finished()), worker_thread, SLOT(deleteLater()));
    // Finally start the thread
    worker_thread->start();
}

void MainWindow::on_stop_btn_clicked() {}

void MainWindow::on_pause_btn_clicked() {}

void MainWindow::on_resume_btn_clicked() {}
