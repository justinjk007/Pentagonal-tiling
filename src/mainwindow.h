#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtWidgets>
#include "Worker.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    QtCharts::QSplineSeries* fitness_line_series;
    QtCharts::QChartView* fitness_chart_view;
    QtCharts::QValueAxis* axisX;
    QtCharts::QValueAxis* axisY;
    long y_axis;  // Store current maximum Y value on the fitness graph
    void updatePentagonInfo(const QString&);
    void updateFitnessGraph(const long&, const double&);
    void updatePentagonGeneration(Line);
    void updatePrimitiveTileGeneration();

   private slots:
    void on_start_btn_clicked();
    void on_stop_btn_clicked();
    void on_pause_btn_clicked();
    void on_resume_btn_clicked();

   private:
    Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
