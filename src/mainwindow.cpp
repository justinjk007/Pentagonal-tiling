#include "mainwindow.h"
#include <QTextBrowser>
#include <QThread>
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "ui_mainwindow.h"
#include "Worker.hpp"

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
    QThread* worker_thread = new QThread;
    Worker* de_algo        = new Worker();
    de_algo->moveToThread(worker_thread);
    connect(de_algo, &Worker::updatePentagonInfo, this, &MainWindow::updatePentagonInfo);
    connect(worker_thread, SIGNAL(started()), de_algo, SLOT(mainProcess()));
    // Delete thread signals
    connect(de_algo, SIGNAL(finished()), worker_thread, SLOT(quit()));
    connect(de_algo, SIGNAL(finished()), de_algo, SLOT(deleteLater()));
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
