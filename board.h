#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "slot.h"
#include "hope.h"
#include <QGridLayout>
#include "string.h"




class Board : public QWidget
{
    Q_OBJECT
public:
    Board(QWidget *parent = nullptr);

    bool player = true;                     //kdo prave hraje
    int clicks = 0;                         //pocet kliknuti
    bool win = false;                       //dokoncena hra nebo ne
    bool computer = true;                   // je computer nebo ne
    bool getPlayer(){return player;}        //vraci player
    void clearBoard();                      //ocisti board
private:
    bool tie = false;                       //uklada jestli je remiza

    int array[3][3];                        //pole pro ukladani typu tlacitek
    QVector<QVector<Hope *>> BList;         //pole pro ukladani tlacitek
    QGridLayout *BGrid;                     //mrizka pro umisteni tlacitek

    void checkState();                      //zkontroluje jestli nenastala vyhra nebo remiza
    void setPlayer();                       //zmeni hrace
    void computerTurn();                    //tah pocitace
private slots:
    void        buttonClicked();            //kdyz kliknes na tlacitko

signals:
    void finished();                        //ukonci jednu hru
    void turnChange();                      //pro label, ktery ukazuje kdo je na tahu


};

#endif // BOARD_H
