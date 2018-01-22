#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include "PrimitiveTile.hpp"

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
    void updatePentagonInfo(const QString&);
    void updateFitnessGraph();
    void updatePentagonGeneration();
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
