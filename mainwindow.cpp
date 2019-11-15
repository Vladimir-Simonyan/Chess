#include <QtGui>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int N = 8, M = 8;
int txt[8][8];
int fig[8][8] = { 0 };
int tqb[8][8] = { 0 };
bool selectedfig = false;
int selfig_i, selfig_j;
int xod = 1;
int reseted = 0;

void Dasavorel();
void TQB();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
          elem[i][j] = new QWidget(this);
          elem[i][j]->setGeometry(j*90,i*90,90,90);
          tqbf[i][j] = new QWidget(this);
          tqbf[i][j]->setGeometry(j*90,i*90,90,90);
          figur[i][j] = new QWidget(this);
          figur[i][j]->setGeometry(j*90,i*90,90,90);
        }
    }
    Dasavorel();
    MainWindow::Update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_N) reseted = 1;
    else if(event->key() == Qt::Key_E) {
        if(reseted == 1) reseted = 2;
        else reseted = 0;
    }
    else if(event->key() == Qt::Key_W) {
        if(reseted == 2) {
            reseted = 0;
            Dasavorel();
            MainWindow::Update();
        }
        else reseted = 0;
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    MainWindow::Clicked(event->y()/90, event->x()/90);
}

void MainWindow::Update() {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (((j % 2) + (i % 2)) % 2) elem[i][j]->setStyleSheet("background-color:#2e1000");
            else elem[i][j]->setStyleSheet("background-color:#f8d299;");

            tqbf[i][j]->setStyleSheet("background-color:#00000000");
            if(fig[i][j] == 0) figur[i][j]->setStyleSheet("background-color:#00000000;");
            else if(fig[i][j] == 1) figur[i][j]->setStyleSheet("background-image: url(figures/1.png);");
            else if(fig[i][j] == 2) figur[i][j]->setStyleSheet("background-image: url(figures/2.png);");
            else if(fig[i][j] == 3) figur[i][j]->setStyleSheet("background-image: url(figures/3.png);");
            else if(fig[i][j] == 4) figur[i][j]->setStyleSheet("background-image: url(figures/4.png);");
            else if(fig[i][j] == 5) figur[i][j]->setStyleSheet("background-image: url(figures/5.png);");
            else if(fig[i][j] == 6) figur[i][j]->setStyleSheet("background-image: url(figures/6.png);");
            else if(fig[i][j] == -1) figur[i][j]->setStyleSheet("background-image: url(figures/-1.png);");
            else if(fig[i][j] == -2) figur[i][j]->setStyleSheet("background-image: url(figures/-2.png);");
            else if(fig[i][j] == -3) figur[i][j]->setStyleSheet("background-image: url(figures/-3.png);");
            else if(fig[i][j] == -4) figur[i][j]->setStyleSheet("background-image: url(figures/-4.png);");
            else if(fig[i][j] == -5) figur[i][j]->setStyleSheet("background-image: url(figures/-5.png);");
            else if(fig[i][j] == -6) figur[i][j]->setStyleSheet("background-image: url(figures/-6.png);");

            if(selectedfig == 1) {
                if(tqb[i][j] == 1) tqbf[i][j]->setStyleSheet("background-image: url(figures/1112.png);");
                else if(tqb[i][j] == 2) tqbf[i][j]->setStyleSheet("background-color:#cc0000;");
                else if(tqb[i][j] == 3) tqbf[i][j]->setStyleSheet("background-color:#ffcc00;");
            }
        }
    }
}

void MainWindow::Clicked(int i, int j) {
    if(fig[i][j] != 0 && !selectedfig && xod*fig[i][j] > 0) {        //  @ntrel
        selectedfig = true;
        selfig_i = i;
        selfig_j = j;
        TQB();
    }
    else if(fig[i][j] == 0 && selectedfig) {    // qaylel
        if(tqb[i][j]) {
            fig[i][j] = fig[selfig_i][selfig_j];
            fig[selfig_i][selfig_j] = 0;
            xod = -xod;
        }
        selectedfig = false;
    }
    else if(fig[i][j] != 0 && selectedfig) {    // utel
        if(tqb[i][j] && fig[selfig_i][selfig_j]*fig[i][j] < 0 && fig[i][j] != 1 && fig[i][j] != -1) {
            fig[i][j] = fig[selfig_i][selfig_j];
            fig[selfig_i][selfig_j] = 0;
            xod = -xod;
        }
        selectedfig = false;
    }
    MainWindow::Update();
}

void Dasavorel() {
    xod = 1;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            fig[i][j] = 0;
            tqb[i][j] = 0;
        }
    }
    fig[0][0] = fig[0][7] = -5;
    fig[0][1] = fig[0][6] = -4;
    fig[0][2] = fig[0][5] = -3;
    fig[0][3] = -2;
    fig[0][4] = -1;
    for (int i = 0; i < 8; i++) fig[1][i] = -6;

    fig[7][0] = fig[7][7] = 5;
    fig[7][1] = fig[7][6] = 4;
    fig[7][2] = fig[7][5] = 3;
    fig[7][3] = 2;
    fig[7][4] = 1;
    for (int i = 0; i < 8; i++) fig[6][i] = 6;
}

void TQB() {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            tqb[i][j] = 0;
        }
    }

    if (fig[selfig_i][selfig_j] > 0) {           // spitak

        if (fig[selfig_i][selfig_j] == 6) {      // zinvor
            tqb[selfig_i][selfig_j] = 3;
            if (fig[selfig_i-1][selfig_j] == 0) tqb[selfig_i-1][selfig_j] = 1;
            if (selfig_i == 6 && fig[selfig_i-2][selfig_j] == 0) tqb[selfig_i-2][selfig_j] = 1;
            if (selfig_i - 1 >= 0 && selfig_j + 1 < M && fig[selfig_i-1][selfig_j+1] < 0) tqb[selfig_i-1][selfig_j+1] = 2;
            if (selfig_i - 1 >= 0 && selfig_j - 1 >= 0 && fig[selfig_i-1][selfig_j-1] < 0) tqb[selfig_i-1][selfig_j-1] = 2;
        }//

        else if (fig[selfig_i][selfig_j] == 5) {      // navak
            tqb[selfig_i][selfig_j] = 3;

            for (int i = selfig_i-1; i >= 0; i--)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] < 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int i = selfig_i+1; i < N; i++)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] < 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int j = selfig_j-1; j >= 0; j--)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] < 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int j = selfig_j+1; j < M; j++)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] < 0) { tqb[selfig_i][j] = 2; break; }
                else break;
        }//

        else if (fig[selfig_i][selfig_j] == 4) {      // dzi
            tqb[selfig_i][selfig_j] = 3;

            if (selfig_i-2 >= 0 && selfig_j-1 >= 0) {
                if (fig[selfig_i-2][selfig_j-1] == 0) tqb[selfig_i-2][selfig_j-1] = 1;
                else if (fig[selfig_i-2][selfig_j-1] < 0) tqb[selfig_i-2][selfig_j-1] = 2;
            }

            if (selfig_i-2 >= 0 && selfig_j+1 < M) {
                if (fig[selfig_i-2][selfig_j+1] == 0) tqb[selfig_i-2][selfig_j+1] = 1;
                else if (fig[selfig_i-2][selfig_j+1] < 0) tqb[selfig_i-2][selfig_j+1] = 2;
            }

            if (selfig_i+2 < N && selfig_j-1 >= 0) {
                if (fig[selfig_i+2][selfig_j-1] == 0) tqb[selfig_i+2][selfig_j-1] = 1;
                else if (fig[selfig_i+2][selfig_j-1] < 0) tqb[selfig_i+2][selfig_j-1] = 2;
            }

            if (selfig_i+2 < N && selfig_j+1 < M) {
                if (fig[selfig_i+2][selfig_j+1] == 0) tqb[selfig_i+2][selfig_j+1] = 1;
                else if (fig[selfig_i+2][selfig_j+1] < 0) tqb[selfig_i+2][selfig_j+1] = 2;
            }

            if (selfig_i-1 >= 0 && selfig_j-2 >= 0) {
                if (fig[selfig_i-1][selfig_j-2] == 0) tqb[selfig_i-1][selfig_j-2] = 1;
                else if (fig[selfig_i-1][selfig_j-2] < 0) tqb[selfig_i-1][selfig_j-2] = 2;
            }
            if (selfig_i-1 >= 0 && selfig_j+2 < M) {
                if (fig[selfig_i-1][selfig_j+2] == 0) tqb[selfig_i-1][selfig_j+2] = 1;
                else if (fig[selfig_i-1][selfig_j+2] < 0) tqb[selfig_i-1][selfig_j+2] = 2;
            }

            if (selfig_i+1 < N && selfig_j-2 >= 0) {
                if (fig[selfig_i+1][selfig_j-2] == 0) tqb[selfig_i+1][selfig_j-2] = 1;
                else if (fig[selfig_i+1][selfig_j-2] < 0) tqb[selfig_i+1][selfig_j-2] = 2;
            }

            if (selfig_i+1 < N && selfig_j+2 < M) {
                if (fig[selfig_i+1][selfig_j+2] == 0) tqb[selfig_i+1][selfig_j+2] = 1;
                else if (fig[selfig_i+1][selfig_j+2] < 0) tqb[selfig_i+1][selfig_j+2] = 2;
            }
        }//

        else if (fig[selfig_i][selfig_j] == 3) {      // pix
            tqb[selfig_i][selfig_j] = 3;

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j - i >= 0) {
                    if (fig[selfig_i-i][selfig_j-i] == 0) tqb[selfig_i-i][selfig_j-i] = 1;
                    else if (fig[selfig_i-i][selfig_j-i] < 0) { tqb[selfig_i-i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j + i < M) {
                    if (fig[selfig_i-i][selfig_j+i] == 0) tqb[selfig_i-i][selfig_j+i] = 1;
                    else if (fig[selfig_i-i][selfig_j+i] < 0) { tqb[selfig_i-i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j - i >= 0) {
                    if (fig[selfig_i+i][selfig_j-i] == 0) tqb[selfig_i+i][selfig_j-i] = 1;
                    else if (fig[selfig_i+i][selfig_j-i] < 0) { tqb[selfig_i+i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j + i < M) {
                    if (fig[selfig_i+i][selfig_j+i] == 0) tqb[selfig_i+i][selfig_j+i] = 1;
                    else if (fig[selfig_i+i][selfig_j+i] < 0) { tqb[selfig_i+i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

        }//

        else if (fig[selfig_i][selfig_j] == 2) {      // taguhi
            tqb[selfig_i][selfig_j] = 3;

            for (int i = selfig_i-1; i >= 0; i--)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] < 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int i = selfig_i+1; i < N; i++)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] < 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int j = selfig_j-1; j >= 0; j--)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] < 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int j = selfig_j+1; j < M; j++)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] < 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j - i >= 0) {
                    if (fig[selfig_i-i][selfig_j-i] == 0) tqb[selfig_i-i][selfig_j-i] = 1;
                    else if (fig[selfig_i-i][selfig_j-i] < 0) { tqb[selfig_i-i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j + i < M) {
                    if (fig[selfig_i-i][selfig_j+i] == 0) tqb[selfig_i-i][selfig_j+i] = 1;
                    else if (fig[selfig_i-i][selfig_j+i] < 0) { tqb[selfig_i-i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j - i >= 0) {
                    if (fig[selfig_i+i][selfig_j-i] == 0) tqb[selfig_i+i][selfig_j-i] = 1;
                    else if (fig[selfig_i+i][selfig_j-i] < 0) { tqb[selfig_i+i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j + i < M) {
                    if (fig[selfig_i+i][selfig_j+i] == 0) tqb[selfig_i+i][selfig_j+i] = 1;
                    else if (fig[selfig_i+i][selfig_j+i] < 0) { tqb[selfig_i+i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }
        }//

        else if (fig[selfig_i][selfig_j] == 1) {      // tagavor
            tqb[selfig_i][selfig_j] = 3;

            if(selfig_i-1 >= 0 && selfig_j-1 >= 0) {
                if (fig[selfig_i-1][selfig_j-1] == 0) tqb[selfig_i-1][selfig_j-1] = 1;
                else if (fig[selfig_i-1][selfig_j-1] < 0) tqb[selfig_i-1][selfig_j-1] = 2;
            }

            if(selfig_i-1 >= 0 && selfig_j+1 < M) {
                if (fig[selfig_i-1][selfig_j+1] == 0) tqb[selfig_i-1][selfig_j+1] = 1;
                else if (fig[selfig_i-1][selfig_j+1] < 0) tqb[selfig_i-1][selfig_j+1] = 2;
            }

            if(selfig_i+1 < N && selfig_j-1 >= 0) {
                if (fig[selfig_i+1][selfig_j-1] == 0) tqb[selfig_i+1][selfig_j-1] = 1;
                else if (fig[selfig_i+1][selfig_j-1] < 0) tqb[selfig_i+1][selfig_j-1] = 2;
            }

            if(selfig_i+1 < N && selfig_j+1 < M) {
                if (fig[selfig_i+1][selfig_j+1] == 0) tqb[selfig_i+1][selfig_j+1] = 1;
                else if (fig[selfig_i+1][selfig_j+1] < 0) tqb[selfig_i+1][selfig_j+1] = 2;
            }

            if(selfig_i-1 >= 0) {
                if (fig[selfig_i-1][selfig_j] == 0) tqb[selfig_i-1][selfig_j] = 1;
                else if (fig[selfig_i-1][selfig_j] < 0) tqb[selfig_i-1][selfig_j] = 2;
            }

            if(selfig_i+1 < N) {
                if (fig[selfig_i+1][selfig_j] == 0) tqb[selfig_i+1][selfig_j] = 1;
                else if (fig[selfig_i+1][selfig_j] < 0) tqb[selfig_i+1][selfig_j] = 2;
            }

            if(selfig_j-1 >= 0) {
                if (fig[selfig_i][selfig_j-1] == 0) tqb[selfig_i][selfig_j-1] = 1;
                else if (fig[selfig_i][selfig_j-1] < 0) tqb[selfig_i][selfig_j-1] = 2;
            }

            if(selfig_j+1 < M) {
                if (fig[selfig_i][selfig_j+1] == 0) tqb[selfig_i][selfig_j+1] = 1;
                else if (fig[selfig_i][selfig_j+1] < 0) tqb[selfig_i][selfig_j+1] = 2;
            }
        }//
    }

    else if (fig[selfig_i][selfig_j] < 0) {           // sev

        if (fig[selfig_i][selfig_j] == -6) {      // zinvor
            tqb[selfig_i][selfig_j] = 3;
            if (fig[selfig_i+1][selfig_j] == 0) tqb[selfig_i+1][selfig_j] = 1;
            if (selfig_i == 1 && fig[selfig_i+2][selfig_j] == 0) tqb[selfig_i+2][selfig_j] = 1;
            if (selfig_i + 1 < N && selfig_j + 1 < M && fig[selfig_i+1][selfig_j+1] > 0) tqb[selfig_i+1][selfig_j+1] = 2;
            if (selfig_i + 1 < N && selfig_j - 1 >= 0 && fig[selfig_i+1][selfig_j-1] > 0) tqb[selfig_i+1][selfig_j-1] = 2;
        }//

        else if (fig[selfig_i][selfig_j] == -5) {      // navak
            tqb[selfig_i][selfig_j] = 3;

            for (int i = selfig_i-1; i >= 0; i--)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] > 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int i = selfig_i+1; i < N; i++)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] > 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int j = selfig_j-1; j >= 0; j--)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] > 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int j = selfig_j+1; j < M; j++)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] > 0) { tqb[selfig_i][j] = 2; break; }
                else break;
        }//

        else if (fig[selfig_i][selfig_j] == -4) {      // dzi
            tqb[selfig_i][selfig_j] = 3;

            if (selfig_i-2 >= 0 && selfig_j-1 >= 0) {
                if (fig[selfig_i-2][selfig_j-1] == 0) tqb[selfig_i-2][selfig_j-1] = 1;
                else if (fig[selfig_i-2][selfig_j-1] > 0) tqb[selfig_i-2][selfig_j-1] = 2;
            }

            if (selfig_i-2 >= 0 && selfig_j+1 < M) {
                if (fig[selfig_i-2][selfig_j+1] == 0) tqb[selfig_i-2][selfig_j+1] = 1;
                else if (fig[selfig_i-2][selfig_j+1] > 0) tqb[selfig_i-2][selfig_j+1] = 2;
            }

            if (selfig_i+2 < N && selfig_j-1 >= 0) {
                if (fig[selfig_i+2][selfig_j-1] == 0) tqb[selfig_i+2][selfig_j-1] = 1;
                else if (fig[selfig_i+2][selfig_j-1] > 0) tqb[selfig_i+2][selfig_j-1] = 2;
            }

            if (selfig_i+2 < N && selfig_j+1 < M) {
                if (fig[selfig_i+2][selfig_j+1] == 0) tqb[selfig_i+2][selfig_j+1] = 1;
                else if (fig[selfig_i+2][selfig_j+1] > 0) tqb[selfig_i+2][selfig_j+1] = 2;
            }

            if (selfig_i-1 >= 0 && selfig_j-2 >= 0) {
                if (fig[selfig_i-1][selfig_j-2] == 0) tqb[selfig_i-1][selfig_j-2] = 1;
                else if (fig[selfig_i-1][selfig_j-2] > 0) tqb[selfig_i-1][selfig_j-2] = 2;
            }
            if (selfig_i-1 >= 0 && selfig_j+2 < M) {
                if (fig[selfig_i-1][selfig_j+2] == 0) tqb[selfig_i-1][selfig_j+2] = 1;
                else if (fig[selfig_i-1][selfig_j+2] > 0) tqb[selfig_i-1][selfig_j+2] = 2;
            }

            if (selfig_i+1 < N && selfig_j-2 >= 0) {
                if (fig[selfig_i+1][selfig_j-2] == 0) tqb[selfig_i+1][selfig_j-2] = 1;
                else if (fig[selfig_i+1][selfig_j-2] > 0) tqb[selfig_i+1][selfig_j-2] = 2;
            }

            if (selfig_i+1 < N && selfig_j+2 < M) {
                if (fig[selfig_i+1][selfig_j+2] == 0) tqb[selfig_i+1][selfig_j+2] = 1;
                else if (fig[selfig_i+1][selfig_j+2] > 0) tqb[selfig_i+1][selfig_j+2] = 2;
            }
        }//

        else if (fig[selfig_i][selfig_j] == -3) {      // pix
            tqb[selfig_i][selfig_j] = 3;

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j - i >= 0) {
                    if (fig[selfig_i-i][selfig_j-i] == 0) tqb[selfig_i-i][selfig_j-i] = 1;
                    else if (fig[selfig_i-i][selfig_j-i] > 0) { tqb[selfig_i-i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j + i < M) {
                    if (fig[selfig_i-i][selfig_j+i] == 0) tqb[selfig_i-i][selfig_j+i] = 1;
                    else if (fig[selfig_i-i][selfig_j+i] > 0) { tqb[selfig_i-i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j - i >= 0) {
                    if (fig[selfig_i+i][selfig_j-i] == 0) tqb[selfig_i+i][selfig_j-i] = 1;
                    else if (fig[selfig_i+i][selfig_j-i] > 0) { tqb[selfig_i+i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j + i < M) {
                    if (fig[selfig_i+i][selfig_j+i] == 0) tqb[selfig_i+i][selfig_j+i] = 1;
                    else if (fig[selfig_i+i][selfig_j+i] > 0) { tqb[selfig_i+i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

        }//

        else if (fig[selfig_i][selfig_j] == -2) {      // taguhi
            tqb[selfig_i][selfig_j] = 3;

            for (int i = selfig_i-1; i >= 0; i--)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] > 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int i = selfig_i+1; i < N; i++)
                if (fig[i][selfig_j] == 0) tqb[i][selfig_j] = 1;
                else if (fig[i][selfig_j] > 0) { tqb[i][selfig_j] = 2; break; }
                else break;

            for (int j = selfig_j-1; j >= 0; j--)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] > 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int j = selfig_j+1; j < M; j++)
                if (fig[selfig_i][j] == 0) tqb[selfig_i][j] = 1;
                else if (fig[selfig_i][j] > 0) { tqb[selfig_i][j] = 2; break; }
                else break;

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j - i >= 0) {
                    if (fig[selfig_i-i][selfig_j-i] == 0) tqb[selfig_i-i][selfig_j-i] = 1;
                    else if (fig[selfig_i-i][selfig_j-i] > 0) { tqb[selfig_i-i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i - i >= 0 && selfig_j + i < M) {
                    if (fig[selfig_i-i][selfig_j+i] == 0) tqb[selfig_i-i][selfig_j+i] = 1;
                    else if (fig[selfig_i-i][selfig_j+i] > 0) { tqb[selfig_i-i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j - i >= 0) {
                    if (fig[selfig_i+i][selfig_j-i] == 0) tqb[selfig_i+i][selfig_j-i] = 1;
                    else if (fig[selfig_i+i][selfig_j-i] > 0) { tqb[selfig_i+i][selfig_j-i] = 2; break; }
                    else break;
                }
                else break;
            }

            for (int i = 1; i; i++) {
                if (selfig_i + i < N && selfig_j + i < M) {
                    if (fig[selfig_i+i][selfig_j+i] == 0) tqb[selfig_i+i][selfig_j+i] = 1;
                    else if (fig[selfig_i+i][selfig_j+i] > 0) { tqb[selfig_i+i][selfig_j+i] = 2; break; }
                    else break;
                }
                else break;
            }
        }//

        else if (fig[selfig_i][selfig_j] == -1) {      // tagavor
            tqb[selfig_i][selfig_j] = 3;

            if(selfig_i-1 >= 0 && selfig_j-1 >= 0) {
                if (fig[selfig_i-1][selfig_j-1] == 0) tqb[selfig_i-1][selfig_j-1] = 1;
                else if (fig[selfig_i-1][selfig_j-1] > 0) tqb[selfig_i-1][selfig_j-1] = 2;
            }

            if(selfig_i-1 >= 0 && selfig_j+1 < M) {
                if (fig[selfig_i-1][selfig_j+1] == 0) tqb[selfig_i-1][selfig_j+1] = 1;
                else if (fig[selfig_i-1][selfig_j+1] > 0) tqb[selfig_i-1][selfig_j+1] = 2;
            }

            if(selfig_i+1 < N && selfig_j-1 >= 0) {
                if (fig[selfig_i+1][selfig_j-1] == 0) tqb[selfig_i+1][selfig_j-1] = 1;
                else if (fig[selfig_i+1][selfig_j-1] > 0) tqb[selfig_i+1][selfig_j-1] = 2;
            }

            if(selfig_i+1 < N && selfig_j+1 < M) {
                if (fig[selfig_i+1][selfig_j+1] == 0) tqb[selfig_i+1][selfig_j+1] = 1;
                else if (fig[selfig_i+1][selfig_j+1] > 0) tqb[selfig_i+1][selfig_j+1] = 2;
            }

            if(selfig_i-1 >= 0) {
                if (fig[selfig_i-1][selfig_j] == 0) tqb[selfig_i-1][selfig_j] = 1;
                else if (fig[selfig_i-1][selfig_j] > 0) tqb[selfig_i-1][selfig_j] = 2;
            }

            if(selfig_i+1 < N) {
                if (fig[selfig_i+1][selfig_j] == 0) tqb[selfig_i+1][selfig_j] = 1;
                else if (fig[selfig_i+1][selfig_j] > 0) tqb[selfig_i+1][selfig_j] = 2;
            }

            if(selfig_j-1 >= 0) {
                if (fig[selfig_i][selfig_j-1] == 0) tqb[selfig_i][selfig_j-1] = 1;
                else if (fig[selfig_i][selfig_j-1] > 0) tqb[selfig_i][selfig_j-1] = 2;
            }

            if(selfig_j+1 < M) {
                if (fig[selfig_i][selfig_j+1] == 0) tqb[selfig_i][selfig_j+1] = 1;
                else if (fig[selfig_i][selfig_j+1] > 0) tqb[selfig_i][selfig_j+1] = 2;
            }
        }//
    }
}
/*
    0 - datark
    1 - tagavor
    2 - taguhi
    3 - pix
    4 - dzi
    5 - navak
    6 - zinvor
    + spitak
    - sev
*/
