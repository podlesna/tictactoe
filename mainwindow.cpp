#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include <QGridLayout>
#include <QColor>
#include <QLabel>
#include <string.h>


#include <thread>
#include <chrono>


Widget::Widget(QWidget *parent) :
   QWidget(parent)
{

    this->resize(300,500);
    grid = new QGridLayout(this);
    this->setWindowTitle("Tic Tac Toe");

    this->setLayout(grid);
    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, QColor(22, 22, 22));
    setAutoFillBackground(true);
    this->setPalette(Pal);


    QPixmap pixmap(":/images/newlogo.png");

    label = new QLabel();
    label->setPixmap(pixmap.scaled(200, 150));

    grid->addWidget(label, 0, 1);


    start = new QPushButton("&New game", this);

    start->setStyleSheet("background-color:#FF8C00; color:white; font-size: 20px;");
    start->setAutoFillBackground(true);

    start->update();
    connect(start, SIGNAL(clicked()), this, SLOT(choosePlayer()));
    end = new QPushButton("&Quit", this);
    connect(end , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    end->setStyleSheet("background-color:#FF8C00; color:white; font-size: 20px;");


    start->setMinimumSize(200,50);
    end->setMinimumSize(200, 50);

    grid->addWidget(start, 1, 1);
    grid->addWidget(end, 2, 1);
    grid->setColumnMinimumWidth(0, 50);
    grid->setColumnMinimumWidth(1, 200);
    grid->setColumnMinimumWidth(2, 50);
    grid->setRowMinimumHeight(1, 75);
    grid->setRowMinimumHeight(0, 300);
    grid->setRowMinimumHeight(2, 75);
    grid->setRowMinimumHeight(3, 50);
  //  grid->addWidget(board, 1, 1);


}

Widget::~Widget()
{

}

void Widget::startGame(){                       //pripravi hru ke startu
    start->deleteLater();
    turn = new QLabel();
    score = new QLabel();
    connect(board, SIGNAL(turnChange()), SLOT(showChanged()));

    cross = new QLabel();
    QPixmap pixmap(":/images/cross.png");
    cross->setPixmap(pixmap.scaled(40,40));
    cross->setFixedSize(50, 50);
    grid->addWidget(cross, 1, 0, Qt::AlignRight);

    circle = new QLabel();
    QPixmap pixmap2(":/images/circleicon.png");
    circle->setPixmap(pixmap2.scaled(45,45));
    circle->setFixedSize(50,50);
    grid->addWidget(circle, 1, 2);

    score = new QLabel();
    score->setText("SCORE");
    grid->addWidget(score, 0, 1);
    score->setStyleSheet("color:white; font-size: 20px;");

    turn = new QLabel();
    turn->setText("It's X turn!");
    turn->setStyleSheet("color:white; font-size: 20px;");
    turn->setAlignment(Qt::AlignCenter);
    grid->addWidget(turn, 3, 0, 1, 3);
    wins[0] = 0;
    wins[1] = 0;
    sc1 = new QLabel();
    sc1->setText(QString::number(wins[0])+ " : "+ QString::number(wins[1]));

    grid->addWidget(sc1, 1, 1 );
    sc1->setFixedSize(80, 50);
    sc1->setStyleSheet("color:white; font-size: 30px;");
    sc1->setAlignment(Qt::AlignCenter);

    pause = new QPushButton("&Pause", this);
    pause->setStyleSheet("background-color:#FF8C00; color:white; font-size: 20px;");
    pause->setAutoFillBackground(true);
    pause->setMinimumSize(100, 25);

    connect(pause, SIGNAL(clicked()), SLOT(onPause()));

    end->setMinimumSize(100, 25);
    grid->addWidget(pause, 4, 0);
    grid->addWidget(end, 4, 2);
    grid->addWidget(board, 2, 0, 1, 3);


    grid->setColumnMinimumWidth(0, 75);
    grid->setColumnMinimumWidth(1, 75);
    grid->setColumnMinimumWidth(2, 75);
    grid->setRowMinimumHeight(0, 50);
    grid->setRowMinimumHeight(1, 50);
    grid->setRowMinimumHeight(2, 300);
    grid->setRowMinimumHeight(3, 50);
    this->setFixedSize(300, 500);

    connect( board, SIGNAL(finished()), SLOT(gameOver()) );


}

void Widget::choosePlayer()                     //okno pro vyber poctu hrace
{
    QDialog *dialog = new QDialog();
    dialog->resize(250, 200);
    dialog->setStyleSheet("background-color:#161616");
    dialog->setWindowTitle("Choose number of players");

    QPushButton *onePlayer = new QPushButton(dialog);
    QPushButton *twoPlayers = new QPushButton(dialog);
    onePlayer->setGeometry(50, 25, 150, 50);
    onePlayer->setStyleSheet("background-color:#FF8C00; color:white; font-size: 15px;");

    twoPlayers->setGeometry(50, 100, 150, 50);
    twoPlayers->setStyleSheet("background-color:#FF8C00; color:white; font-size: 15px;");

    connect(onePlayer, SIGNAL(clicked()), this, SLOT(startTwoPl()));
    connect(onePlayer, SIGNAL(clicked()), dialog, SLOT(close()));
    connect(twoPlayers, SIGNAL(clicked()), this, SLOT(startComp()));
    connect(twoPlayers, SIGNAL(clicked()), dialog, SLOT(close()));

    onePlayer->setText("Two players");
    twoPlayers->setText("Player vs Computer");
    dialog->exec();
}

void Widget::startTwoPl(){      //zacne hru s dvema hraci

    label->clear();
    board = new Board(this);
    board->computer = false;
    startGame();
}

void Widget::startComp(){         //zacnu hru s pocitacem

    label->clear();
    board = new Board(this);
    board->computer = true;
    startGame();
}

void Widget::onPause(){            //menu pro talcitko pause
    QDialog *dialog = new QDialog();
    dialog->resize(250, 200
 );
    dialog->setStyleSheet("background-color:#161616");

    dialog->setWindowTitle("Pause");
    QPushButton *changePl = new QPushButton(dialog);
    QPushButton *cont = new QPushButton(dialog);

    cont->setGeometry(50, 25, 150, 50);
    cont->setStyleSheet("background-color:#FF8C00; color:white; font-size: 15px;");
    cont->setText("Continue");


    changePl->setGeometry(50, 100, 150, 50);
    changePl->setStyleSheet("background-color:#FF8C00; color:white; font-size: 15px;");
    changePl->setText("Change players");

    connect(cont, SIGNAL(clicked()),dialog, SLOT(close()));
    connect(changePl, SIGNAL(clicked()),dialog, SLOT(close()));
    connect(changePl, SIGNAL(clicked()), SLOT(changePlayer()));

    dialog->exec();


}

void Widget::showChanged(){
    if(board->player){
        turn->setText("It's X turn!");
    } else{
        turn->setText("It's O turn!");
    }
}

void Widget::changePlayer(){
    clearGame();
    choosePlayer();
}

void Widget::clearGame(){
    delete board;
    delete turn;
    delete score;
    delete sc1;
    delete cross;
    delete circle;

}

void Widget::gameOver()
{
    QMessageBox ms;
    if(board->clicks == 9 && board->win == false){
        turn->setText("It's a draw!");
        ms.setText("It's a draw");

    }else{
    if(board->player == 0){
        turn->setText("X WINS!!!");
        wins[0]++;
        sc1->setText(QString::number(wins[0])+ " : "+ QString::number(wins[1]));
        ms.setText("X WINS!");

    } else{
        turn->setText("O WINS!!!");
        wins[1]++;
        sc1->setText(QString::number(wins[0])+ " : "+ QString::number(wins[1]));
        ms.setText("O WINS!");

        }
    }
    ms.exec();
board->clearBoard();

}

void Widget::onEnd(){
    clearGame();
    QCoreApplication::quit();
}
