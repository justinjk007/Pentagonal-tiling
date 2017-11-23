#ifndef PENTAGONGEN_HPP
#define PENTAGONGEN_HPP

#include <QWidget>

class pentagonGen : public QWidget
{
    Q_OBJECT

   public:
    explicit pentagonGen(QWidget* parent = 0);

   protected:
    void paintEvent(QPaintEvent* e) override;
};

#endif /* PENTAGONGEN_HPP */
