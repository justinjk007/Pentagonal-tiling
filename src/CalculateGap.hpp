/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include <QObject>
#include <QString>
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "boundaryDetection.hpp"
#include "myGeometry.hpp"

class CalculateGap : public QObject
{
    Q_OBJECT
public:
    double getGap(const Tile&);
    void getGap(double*, double*, const long&);
    double calculateGap(const Tile&, const int&, const int&);
signals:
    void tileInfo(const QString&);
    void minimumGap(const long&,const double&);
    void sideCreated(const Line&);
    void tilingCreated();
};
#endif /* CALCULATEGAP_HPP */
