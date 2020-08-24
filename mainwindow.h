#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "board.h"
#include <QGridLayout>
#include <QLCDNumber>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    QGridLayout *grid;                    //mrizka pro umisteni tlacitek a lablu

    QPushButton *start;                   //tlacitka
    QPushButton *pause;
    QPushButton *end;
    QPushButton *startAgain;

    QLabel *turn;                         //label ukazuje kdo je na tahu a kdo vyhral
    QLabel *score;                        //label ukazuje score
    QLabel *cross;                        //pomocny label pro score
    QLabel *circle;                       //pomocny label pro score
    QLabel *sc1;                          //label ukazuje score
    QLabel *label;                        //obrazek na zacatku

    Board *board;                         //hraci board


    QDialog *dialog;                      //dialog pro vyber poctu hrace
    QDialog *dialog2;                     //dialog pro tlacitko pause
    int wins[2];                          //pole pro ukladani vyher

    void startGame();                     //pripravi vsechno k zacatku hry
    void clearGame();                     //pripravi vsechno k ukonceni hry

public slots:

   void startTwoPl();                    //zacne hru s dvema hraci
   void startComp();                     //zacne hru proti computeru
   void choosePlayer();                  //vyber typu hry
   void gameOver();                      //kdyz hra skonci
   void showChanged();                   //meni nadpis tahu hrace
   void onPause();                       //pause
   void changePlayer();                  //zmeni pocet hracu
   void onEnd();                         //ukonci hru
};

#endif // MAINWINDOW_H
