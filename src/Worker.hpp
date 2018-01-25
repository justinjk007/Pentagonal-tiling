#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
   public slots:
    void mainProcess();
   signals:
    void updatePentagonInfo(const QString&);
    void updateFitnessGraph(const long&, const double&);
    void finished();
};

#endif /* WORKER_HPP */
