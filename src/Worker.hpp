#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public slots:
    void mainProcess();
    void generalInfo(const QString&);
signals:
    void updatePentagonInfo(const QString&);
    void finished();
};

#endif /* WORKER_HPP */
