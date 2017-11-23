#ifndef TILINGGEN_HPP
#define TILINGGEN_HPP

#include <QWidget>

class tilingGen : public QWidget
{
    Q_OBJECT

   public:
    explicit tilingGen(QWidget* parent = 0);

   protected:
    void paintEvent(QPaintEvent* e) override;
};

#endif /* TILINGGEN_HPP */
