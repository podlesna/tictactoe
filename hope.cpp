#include "hope.h"

#include <QPainter>
#include <QWidget>
#include <QMessageBox>
#include <QImage>


Hope::Hope(QWidget *parent): QPushButton(parent)
{
    setMouseTracking(true);
    setFixedSize(80, 80);                                //nastavi rozmer tlacitka

    QPalette Pal(palette());                             //nastavi vychozi barvu na bilou
    Pal.setColor(QPalette::Button, QColor(Qt::white));
    setAutoFillBackground(true);
    setPalette(Pal);

    this->show();

}

void Hope::updateButton(bool pl){
    if(clicked){                                          //zkontroluje jestli tlacitko je kliknute
        if(pl){                                           //podle hrace nastavi obrazek
            QPixmap pixmap(":/images/cross.png");
            QIcon icon(pixmap);
            setIcon(icon);
            setIconSize(QSize(70,70));
        } else{
            QPixmap pixmap(":/images/circle.png");
            QIcon icon(pixmap);
            setIcon(icon);
            setIconSize(QSize(80,80));

        }
    } else{
        setIcon(QIcon());                                  //kdyz neni kliknute nastavi prazdno
    }
}








