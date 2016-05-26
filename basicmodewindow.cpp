#include "basicmodewindow.h"
#include "ui_basicmodewindow.h"
#include <game.h>
#include <random>
#include <iostream>
#include <QString>
#include <mapbutton.h>
#include <QMessageBox>

const int PIC_NUM = 10; //花色数

BasicModeWindow::BasicModeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicModeWindow)
{
    ui->setupUi(this);
    grid = new QGridLayout(ui->picWidget);
    ui->progressBar->setValue(totleTime);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(startGame()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));

}

BasicModeWindow::~BasicModeWindow()
{
    delete ui;
}

void BasicModeWindow::startGame() {
    initMap();
    totleTime = 100;
    ui->progressBar->setValue(totleTime);
    timer->start(1000);
}

void BasicModeWindow::pauseGame() {
    if (timer->isActive()) {
        ui->pushButton_2->setText("继续游戏");
        timer->stop();
    } else {
        ui->pushButton_2->setText("暂停游戏");
        timer->start();
    }

}

void BasicModeWindow::initMap() {
    int rawMap[10][16];
    int randx1, randx2, randy1, randy2;
    timer->start(1000);
    ui->pushButton->setDisabled(true);
    srand((int)time(0));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 16; j++) {
            rawMap[i][j] = gameModel.totalPic++ % PIC_NUM + 1;
//            if (gameModel.totalPic < 160)
//                gameModel.totalPic++;
        }
    }

    for (int k = 0; k < 300; k++) {
        randx1 = random() % 10;
        randx2 = random() % 10;
        randy1 = random() % 16;
        randy2 = random() % 16;
        int tmp = rawMap[randx1][randy1];
        rawMap[randx1][randy1] = rawMap[randx2][randy2];
        rawMap[randx2][randy2] = tmp;
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 18; j++) {
            if (i == 0 || i == 11 || j == 0 || j == 17) {
                continue;
            }

            QString randomPicIndex = QString::number(rawMap[i-1][j-1]);
            MapButton *pic = new MapButton();
            pic->setIcon(QIcon(":/icon/res/" + randomPicIndex + ".png"));
            pic->setObjectName(QString::number(i * 18 + j));
            pic->setIconSize(QSize(40, 40));
            pic->setMinimumSize(40, 40);
            pic->setMaximumSize(40, 40);
            pic->setCheckable(true);
            connect(pic, &MapButton::keyClicked, this, &BasicModeWindow::select);

            grid->addWidget(pic, i-1, j-1);
            gameModel.map[i][j] = randomPicIndex;
        }
    }

}

void BasicModeWindow::select(const QString &msg) {

    MapButton *sb = ui->picWidget->findChild<MapButton*>(msg);
    if (sb != NULL) {
        if (gameModel.pic1 == sb->objectName()) { //连续点击同一个图片
            sb->setChecked(false);
            gameModel.pic1 = "";

        } else if (gameModel.pic1 == "") {
            gameModel.pic1 = sb->objectName();
        } else if (gameModel.linkWithNoCorner(gameModel.pic1, sb->objectName())
                   || gameModel.linkWithOneCorner(gameModel.pic1, sb->objectName())
                   || gameModel.linkWithTwoCorner(gameModel.pic1, sb->objectName())) { //可消去
            gameModel.pic2 = sb->objectName();
            //让两个图片弹起来并消除
            MapButton *p1 = ui->picWidget->findChild<MapButton*>(gameModel.pic1);
            MapButton *p2 = ui->picWidget->findChild<MapButton*>(gameModel.pic2);
            p1->setChecked(false);
            p1->setIcon(QIcon());
            p1->setEnabled(false);
            p2->setChecked(false);
            p2->setIcon(QIcon());
            p2->setEnabled(false);
            gameModel.pic1 = "";
            gameModel.pic2 = "";
        } else if (1) { //不可消去
            //让原来的pic1弹起来
            MapButton *p1 = ui->picWidget->findChild<MapButton*>(gameModel.pic1);
            p1->setChecked(false);
            gameModel.pic1 = sb->objectName();
            //新的pic1按下去
            sb->setChecked(true);
        }


    }
    if (gameModel.isWin()){
        QMessageBox *box = new QMessageBox(this);
        box->setInformativeText("Congratulations！");
        box->show();
        timer->stop();
    }

}

void BasicModeWindow::timerUpDate() {
    totleTime -= 0.5;
    ui->progressBar->setValue(totleTime);

    if (totleTime == 0) {
        QMessageBox *box = new QMessageBox(this);
        box->setInformativeText("时间到！");
        box->show();
        ui->pushButton->setEnabled(true);
    }
}
