#include "relaxedmodewindow.h"
#include "ui_relaxedmodewindow.h"
#include <QMessageBox>
#include "Model/mapbutton.h"
#include <QTime>

RelaxedModeWindow::RelaxedModeWindow(QWidget *parent) :
    BasicModeWindow(parent),
    ui(new Ui::RelaxedModeWindow)
{
    ui->setupUi(this);

    setWindowTitle("欢乐连连看");
    scoreDao = new ScoreDao();
    scoreDao->init();
    gameModel.init();
    helpDialog = new HelpDialog(ui->picWidget);
    ui->progressBar->setValue(totleTime);//progressBar初始化
    grid = new QGridLayout(ui->picWidget); //为游戏棋盘创建网格布局
    timer = new QTimer(this);
    painter = new QPainter(this);
    drawLineLayer = new DrawLineLayer(this);
    drawLineLayer->hide();
    drawLineLayer->setGeometry(QRect(0, 0, 720, 480));
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    //为开始游戏和暂停游戏按钮设置信号槽

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(startGame()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate())); //将timer和timerUpDate方法关联
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(findHint()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(resetMap()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(useTool()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(changeSpeed()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
}

RelaxedModeWindow::~RelaxedModeWindow()
{
    delete ui;
}

void RelaxedModeWindow::startGame() { //开始游戏
    initMap(); //初始化游戏棋盘
    totleTime = 100;
    ui->progressBar->setValue(totleTime);//progressBar初始化
    timer->start(1000); //开始计时，时间间隔为1000ms
    credit = 0;
    ui->label_2->setText(QString::number(credit)); //积分清零
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton->setText("重新开始");
    //如果pushButton之前绑定了startGame方法, 就先解除绑定，然后绑定reStartGame方法
    if (disconnect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(startGame())))
        connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(reStartGame()));
}

void RelaxedModeWindow::reStartGame() { //重新开始游戏
    //清除游戏棋盘
    auto children = ui->picWidget->children();
    for (int i = 1; i < 217; i++) {
        if (children[i]->objectName() != "") {
            grid->removeWidget((QWidget*)children[i]);
            children[i]->deleteLater();
        }
    }
    startGame();


}

void RelaxedModeWindow::pauseGame() {
    if (timer->isActive()) {
        ui->pushButton_2->setText("继续游戏");
        timer->stop();
        ui->picWidget->setDisabled(true);
        ui->pushButton->setDisabled(true);
        ui->pushButton_3->setDisabled(true);
        ui->pushButton_4->setDisabled(true);
    } else {
        ui->pushButton_2->setText("暂停游戏");
        timer->start();
        ui->picWidget->setDisabled(false);
        ui->pushButton->setDisabled(false);
        ui->pushButton_3->setDisabled(false);
        ui->pushButton_4->setDisabled(false);
    }
}

void RelaxedModeWindow::timerUpDate() {
    totleTime -= speed; //timer每更新一次，总时间减去0.5s
    ui->progressBar->setValue(totleTime); //更新progressBar的值
    if (totleTime == 0) {
        QMessageBox *box = new QMessageBox(this);
        box->setInformativeText("时间到！");
        box->show();
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
    }
}

void RelaxedModeWindow::resetMap() {
    auto children = ui->picWidget->children();
    for (int i = 1; i < 217; i++) {
        if (children[i]->objectName() != "") {
            grid->removeWidget((QWidget*)children[i]);
            children[i]->deleteLater();
        }
    }

    reset(true);

    decreaseCredit(50);
}

void RelaxedModeWindow::findHint() {
    QString pos2, pos3;
    QString pic1, pic2;
    int tmp1, tmp2;
    bool success = false;
    for (int i = 0; i < 216 && !success; i++) {
        for (int j = 0; j < 216 && !success && j!=i; j++) {
            if (i % 18 == 0 || i % 18 == 17 || i<18 || i>=198 || j % 18 == 0 || j % 18 == 17 || j<18 || j>=198)
                continue;
            pic1 = QString::number(i);
            pic2 = QString::number(j);

            tmp1 = gameModel.map[i/18][i%18];
            tmp2 = gameModel.map[j/18][j%18];

            if (gameModel.linkWithNoCorner(pic1, pic2)
                               || gameModel.linkWithOneCorner(pic1, pic2, pos2)
                               || gameModel.linkWithTwoCorner(pic1, pic2, pos2, pos3)) {//可消去
                drawLine(pic1, pic2, pos2, pos3);

                success = true;
                gameModel.map[i/18][i%18] = tmp1;
                gameModel.map[j/18][j%18] = tmp2;

                gameModel.totalPic += 2; //还原被减去的图片数
            }

        }
    }

    decreaseCredit(20);
}


void RelaxedModeWindow::showHelp() {
    helpDialog->showHelpDialog();
}

void RelaxedModeWindow::changeSpeed() {
    QHBoxLayout *layout = new QHBoxLayout();
    changeSpeedDialog = new QDialog();
    box = new QSpinBox();
    box->setMaximum(500);
    box->setMinimum(10);
    box->setValue(100/speed);
    box2 = new QSpinBox();
    box2->setMaximum(10);
    box2->setMinimum(5);
    box2->setValue(PIC_NUM);
    QLabel *label = new QLabel("设置总时间（单位s）,最大500, 最小10");
    QLabel *label2 = new QLabel("设置花色数，最小5,最大10");
    layout->addWidget(label);
    layout->addWidget(box);
    layout->addWidget(label2);
    layout->addWidget(box2);
    QPushButton *button = new QPushButton("确定");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(_changeSpeed()));
    layout->addWidget(button);
    changeSpeedDialog->setLayout(layout);
    changeSpeedDialog->show();

}

void RelaxedModeWindow::_changeSpeed() {
    speed = 100.0 / box->value();
    PIC_NUM = box2->value();
    changeSpeedDialog->hide();
}

void RelaxedModeWindow::reset(bool flag) {

    if (flag) {
        gameModel.clearRawMap();
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 18; j++) {
                if (i == 0 || i == 11 || j == 0 || j == 17) {
                    continue;
                }
                gameModel.rawMap[i-1][j-1] = gameModel.map[i][j];
            }
        }
    }
    srand((int)time(0));
    int randx1, randx2, randy1, randy2;
    //将地图中的图片进行300次随机对调，从而打乱棋盘
    for (int k = 0; k < 300; k++) {
        randx1 = random() % 10;
        randx2 = random() % 10;
        randy1 = random() % 16;
        randy2 = random() % 16;
        int tmp = gameModel.rawMap[randx1][randy1];
        gameModel.rawMap[randx1][randy1] = gameModel.rawMap[randx2][randy2];
        gameModel.rawMap[randx2][randy2] = tmp;
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 18; j++) {
            if (i == 0 || i == 11 || j == 0 || j == 17) {
                MapButton *w = new MapButton();
                w->setStyleSheet("background:transparent");
                w->setObjectName(QString::number(i * 18 + j));
                w->setMinimumSize(40, 40);
                w->setMaximumSize(40, 40);
                w->setParent(ui->picWidget);
                grid->addWidget(w, i, j);
                continue;
            }

            int randomPicIndex = gameModel.rawMap[i-1][j-1];
            MapButton *pic = new MapButton();
            if (randomPicIndex == 0) {
                pic->setStyleSheet("background:transparent");
                pic->setObjectName(QString::number(i * 18 + j));
                pic->setIconSize(QSize(40, 40));
                pic->setMinimumSize(40, 40);
                pic->setMaximumSize(40, 40);
                gameModel.map[i][j] = 0;
            } else {
                pic->setIcon(QIcon(":/icon/res/" + QString::number(randomPicIndex) + ".png"));
                pic->setObjectName(QString::number(i * 18 + j));
                pic->setIconSize(QSize(40, 40));
                pic->setMinimumSize(40, 40);
                pic->setMaximumSize(40, 40);
                pic->setCheckable(true);
                connect(pic, &MapButton::keyClicked, this, &RelaxedModeWindow::select);
                gameModel.map[i][j] = randomPicIndex;
            }
            grid->addWidget(pic, i, j);

        }
    }
}

void RelaxedModeWindow::initMap() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 16; j++) {
            gameModel.rawMap[i][j] = gameModel.totalPic++ % PIC_NUM + 1; //初始化未经打乱的棋盘
        }
    }

    reset(false); //打乱rawMap
}

//鼠标点击图片时触发的事件
void RelaxedModeWindow::select(const QString &msg) {
    QString pos2, pos3;
    MapButton *sb = ui->picWidget->findChild<MapButton*>(msg);
    if (sb != NULL) {
        if (gameModel.selectedPic == sb->objectName()) { //连续点击同一个图片
            sb->setChecked(false);
            gameModel.selectedPic = "";

        } else if (gameModel.selectedPic == "") { //当前未选中任何一个图片
            gameModel.selectedPic = sb->objectName();
        } else if (isUsingTool || gameModel.linkWithNoCorner(gameModel.selectedPic, sb->objectName())
                   || gameModel.linkWithOneCorner(gameModel.selectedPic, sb->objectName(), pos2)
                   || gameModel.linkWithTwoCorner(gameModel.selectedPic, sb->objectName(), pos2, pos3)) { //可消去

            if (isUsingTool) {
                gameModel.useTool(gameModel.selectedPic, sb->objectName());
            }
            drawLine(gameModel.selectedPic, sb->objectName(), pos2, pos3); //画线
            //让两个图片弹起来并消除
            MapButton *p1 = ui->picWidget->findChild<MapButton*>(gameModel.selectedPic);
            MapButton *p2 = ui->picWidget->findChild<MapButton*>(sb->objectName());
            p1->setVisible(false);
            p1->setStyleSheet("background:transparent");
            p2->setVisible(false);
            p2->setStyleSheet("background:transparent");

            //消子成功，增加10积分
            increaseCredit();

            //判断是否可以用提示和重排
            if (creditIsEnoughForHint()) {
                ui->pushButton_3->setEnabled(true);

            }
            if (creditIsEnoughForReset()) {
                ui->pushButton_4->setEnabled(true);
            }

            isUsingTool = false;
            gameModel.selectedPic = "";

            //在消子之后判断是否获胜
            if (gameModel.isWin()){
                QMessageBox *box = new QMessageBox(this);
                box->setInformativeText("Congratulations！");
                box->show();
                timer->stop();
                ui->pushButton_2->setEnabled(false);
                ui->pushButton_3->setEnabled(false);
                ui->pushButton_4->setEnabled(false);
            }

        } else { //不可消去
            //让原来的pic1弹起来
            MapButton *p1 = ui->picWidget->findChild<MapButton*>(gameModel.selectedPic);
            p1->setChecked(false);
            gameModel.selectedPic = sb->objectName();
            //新的pic1按下去
            sb->setChecked(true);
        }
    }
}

void RelaxedModeWindow::drawLine(QString pic1, QString pic2, QString pos2, QString pos3) {
    MapButton *p1 = ui->picWidget->findChild<MapButton*>(pic1);
    MapButton *p2 = ui->picWidget->findChild<MapButton*>(pic2);
    //画线
    if (gameModel.flagA) { //没有转折点
        drawLineLayer->setPos1(p1->pos());
        drawLineLayer->setPos2(p2->pos());
        gameModel.flagA = false;
    } else if (gameModel.flagB) {
        drawLineLayer->setPos1(p1->pos());
        drawLineLayer->setPos2(ui->picWidget->findChild<MapButton*>(pos2)->pos());
        drawLineLayer->setPos3(p2->pos());
        gameModel.flagB = false;
    } else if (gameModel.flagC) {
        drawLineLayer->setPos1(p1->pos());
        QWidget *tmpP1;
        QWidget *tmpP2;
        tmpP1 = ui->picWidget->findChild<QWidget*>(pos2);
        tmpP2 = ui->picWidget->findChild<QWidget*>(pos3);
        if (tmpP1 != nullptr) {
            QPoint pp1 = tmpP1->pos();
            drawLineLayer->setPos2(pp1);
        }
        if (tmpP2 != nullptr) {
            QPoint pp2 = tmpP2->pos();
            drawLineLayer->setPos3(pp2);
        }
        QPoint pp4 = p2->pos();
        drawLineLayer->setPos4(pp4);
        gameModel.flagC = false;
    }
    drawLineLayer->show();
    QTime t;
    t.start();
    while(t.elapsed()<200) //连线延迟0.2s
        QCoreApplication::processEvents();
    drawLineLayer->clear();
}

void RelaxedModeWindow::increaseCredit() {
    credit += 10;
    creditIncrement += 10;
    if (creditIncrement % 100 == 0) {
        toolsNum++;
        ui->label_5->setText(QString::number(toolsNum));
        ui->pushButton_5->setEnabled(true);
    }

    ui->label_2->setText(QString::number(credit));
}

void RelaxedModeWindow::decreaseCredit(int num) {
    credit -= num;
    ui->label_2->setText(QString::number(credit));
    if (credit < 20) {
        ui->pushButton_3->setEnabled(false);
    }
    if (credit < 50) {
        ui->pushButton_4->setEnabled(false);
    }
}

bool RelaxedModeWindow::creditIsEnoughForHint() {
    return credit >= 20;
}

bool RelaxedModeWindow::creditIsEnoughForReset() {
    return credit >= 50;
}

void RelaxedModeWindow::useTool() {
    toolsNum--;
    ui->label_5->setText(QString::number(toolsNum));
    isUsingTool = true;
    if (toolsNum == 0) {
        ui->pushButton_5->setEnabled(false);
    }

}
