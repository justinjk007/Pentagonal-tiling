#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>
#include "myGeometry.hpp"

class Worker : public QObject
{
    Q_OBJECT
   public slots:
    void mainProcess();
   signals:
    void updatePentagonInfo(const QString&);
    void updateFitnessGraph(const long&, const double&);
    void updatePentagonGeneration(std::vector<Line>);
    void updatePrimitiveTileGeneration(std::list<Line>);
    void finished();
};

#endif /* WORKER_HPP */
