#include "slot.h"
#include <QPainter>
#include <QGridLayout>

Slot::Slot(QWidget *parent) :
    QWidget(parent)
{
t = none;
SGrid = new QGridLayout(this);
}

void Slot::paintEvent(QPaintEvent *){
     QPainter p(this);
     QPalette Pal(palette());

         Pal.setColor(QPalette::Background, Qt::gray);
         this->setAutoFillBackground(true);
         this->setPalette(Pal);
         this->show();

}
