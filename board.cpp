#include "board.h"
#include <iostream>
#include <string.h>
#include <QObject>
#include <QPainter>


Board::Board(QWidget *parent) :
    QWidget(parent)
{
    BGrid = new QGridLayout(this);
    BList.resize(3);

    for (int i = 0; i < 3; ++i){                        //nastavi rozmery mrizky
        BGrid->setColumnMinimumWidth(i, 80);
        BGrid->setRowMinimumHeight(i, 80);
        BGrid->setHorizontalSpacing(5);
        BGrid->setVerticalSpacing(5);
        }

    for( int i = 0; i < 3; i++){             //naplni list tlacitkami, nastavi je
        BList[i].resize(3);
        for(int j = 0; j < 3; j++){
            Hope *ttb = new Hope(this);
            connect( ttb, SIGNAL(clicked()), SLOT(buttonClicked()) );
            ttb->setStyleSheet("background-color:#f2f2f2; border:0px;text-align:center");
            BGrid->addWidget( ttb, i, j );
            BList[i][j] = ttb;
            array[i][j] = 0;



        }
    }
}




void Board::buttonClicked(){
Hope *b = (Hope *)sender();                            //najde ktere tlacitko bylo kliknute

for(int i = 0; i< 3; i++){
    for(int j = 0; j < 3; j++){                        //najde toto tlacitko v listu
        if(b == BList[i][j]){
           if(BList[i][j]->type() == 0) {              //zkontroluje jestli je prazdne
                    BList[i][j]->makeClicked();        //nastavi, ze je kliknute
                    if(computer){                      //pro hru s pocitacem
                        BList[i][j]->updateButton(player);
                        array[i][j] = 1;
                        clicks++;
                        setPlayer();
                        checkState();

                        if(!tie){
                        computerTurn();
                        clicks++;
                        setPlayer();
                        checkState();

                        } else {
                        tie = false; }

                    } else{                              //pro hru bez pocitace
                        BList[i][j]->updateButton(player);
                        if(player){
                            array[i][j] = 1;
                            clicks++;
                        }else{
                            array[i][j] = 2;
                            clicks++;
                        }
                        setPlayer();
                    }
                    checkState();

}}}}}




void Board::checkState()                       //zkontroluje jestli v radku, sloupci a diagonalach nejsou tri stejne
{
    if(clicks > 4){
    for(int i = 0; i< 3; i++){
        if(array[0][i] == array[1][i] && array[1][i] == array[2][i] && array[0][i] != 0){
            win = true;
        }
        if(array[i][0] == array[i][1] && array[i][1] == array[i][2] && array[i][0] != 0){
            win = true;

        }
    }
        if(array[0][0] == array[1][1] && array[1][1] == array[2][2] && array[0][0] != 0){
            win = true;
        }
        if(array[0][2] == array[1][1] && array[1][1]  == array[2][0] && array[0][2] != 0){
            win = true;
        }
    }
        if(win || clicks == 9){              //kdyz nekdo vyhral nebo je 9 kliknuti skonci hru
            tie = true;
            emit finished();
        }
}



void Board::setPlayer(){                     //zmeni hrace a zmeni nadpis na labelu
    if(player)
        player = 0;
    else
        player = 1;
    emit turnChange();
}


void Board::computerTurn()                   //tah pocitace
{                                            //zkontroluje jestli v nejakem radku, sloupci nebo diagonale nejsou dva stejne prvky
    for(int i=0; i < 3; i++){
        if((array[0][i] == array[1][i] && array[0][i] != 0) || (array[1][i] == array[2][i] && array[1][i] != 0) || (array[0][i] == array[2][i] && array[0][i] != 0)){
            for(int j = 0; j < 3; j++){
                if(array[j][i] == 0){
                    BList[j][i]->makeClicked();
                    BList[j][i]->updateButton(player);
                    array[j][i] = 2;
                    return;
                }
            }
        }
        if((array[i][0] == array[i][1] && array[i][0] != 0) || (array[i][1] == array[i][2] && array[i][1] != 0) || (array[i][0] == array[i][2] && array[i][0] != 0)){
            for(int j = 0; j < 3; j++){
                if(array[i][j] == 0){
                    BList[i][j]->makeClicked();
                    BList[i][j]->updateButton(player);
                    array[i][j] = 2;
                    return;
                }
            }
        }
        }
    if((array[0][0] == array[1][1] && array[0][0] != 0) || (array[1][1] == array[2][2] && array[1][1] != 0) || (array[0][0] == array[2][2] && array[0][0] != 0)){
        for(int i = 0; i < 3; i++)
            if(array[i][i] == 0){
            BList[i][i]->makeClicked();
            BList[i][i]->updateButton(player);
            array[i][i] = 2;
            return;

            }
        }
    int k = 0;
    int s = 0;
    if((array[0][2] == array[1][1] && array[0][2] != 0) || (array[1][1] == array[2][0] && array[1][1] != 0) || (array[0][2] == array[2][0] && array[0][2] != 0)){
            if(array[0][2] == 0){
                s = 2;
            } else if(array[1][1] == 0){
                k = 1;
                s = 1;
            } else if(array[2][0] == 0){
                k = 2;
            }
            if( k != 0 || s != 0){

            BList[k][s]->makeClicked();
            BList[k][s]->updateButton(player);
            array[k][s] = 2;
            return;
            } else{
                checkState();
            }
}
    for(int i = 0; i< 3; i++)                           //kdyz nikde neni dva stejne najde kde je jen jeden
        for(int j = 0; j < 3; j++){
            if(array[i][j] != 0){
                for(int r = 0; r < 3; r++){
                    if(array[i][r] == 0){
                        BList[i][r]->makeClicked();
                        BList[i][r]->updateButton(player);
                        array[i][r] = 2;
                        return;
                    }
                    if(array[r][j] == 0){
                        BList[r][j]->makeClicked();
                        BList[r][j]->updateButton(player);
                        array[r][j] = 2;
                        return;
                    }

                }
        }
    }
k = (rand() % 8);                                       //kdyz board je prazdny vygeneruje nahodne
s = rand() % 8;
BList[k][s]->makeClicked();
BList[k][s]->updateButton(player);
array[k][s] = 2;
return;


}


void Board::clearBoard(){                              //pripravi board k dalsi hre
    for(int i = 0; i < 3; i++)
        for(int j = 0; j< 3; j++){
            BList[i][j]->clicked = 0;
            BList[i][j]->updateButton(player);
            array[i][j] = 0;

        }
    win = false;
    clicks = 0;
    player = true;

}





