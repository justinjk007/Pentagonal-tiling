#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include <QString>

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
    void updateFitnessGraph();
    void updatePentagonGeneration();
    void updatePrimitiveTileGeneration();
    void updatePentagonInfo(const QString&);

   public slots:
    void on_start_btn_clicked();
    void on_stop_btn_clicked();
    void on_pause_btn_clicked();
    void on_resume_btn_clicked();

   private:
    Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
