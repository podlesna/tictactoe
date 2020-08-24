#ifndef HOPE_H
#define HOPE_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>

class Hope: public QPushButton
{
    Q_OBJECT
public:
    Hope(QWidget *parent );

    bool type() const{return clicked;}          //vrati jestli tlacitko je kliknute
    void makeClicked()    {  clicked = 1; }     //udela tlacitko kliknutym
    void updateButton(bool pl);                 //obnovi tlacitko
    bool clicked = 0;                           //kliknute talcitko nebo ne
private:
    QIcon Cross;                                //obrazek pro krizek
    QIcon Circle;                               //obrazek pro krouzek



};
#endif // HOPE_H

