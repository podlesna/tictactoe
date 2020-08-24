#ifndef SLOT_H
#define SLOT_H

#include <QRect>
#include <QWidget>
#include <QGridLayout>

class Slot: public QWidget
{
    Q_OBJECT
public:
    Slot(QWidget *parent = nullptr);
    enum Type { none, X, O };
    Type t = none;
    QGridLayout *SGrid;
protected:
    void paintEvent(QPaintEvent *);

};

#endif // SLOT_H
