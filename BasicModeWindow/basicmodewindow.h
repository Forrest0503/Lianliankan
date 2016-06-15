#ifndef BASICMODEWINDOW_H
#define BASICMODEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QString>
#include "Model/game.h"
#include <QTimer>
#include <QPainter>
#include "Model/DrawLineLayer.h"
#include <HelpDialog/helpdialog.h>
#include <QSpinBox>
#include "Dao/scoredao.h"

namespace Ui {
class BasicModeWindow;
}

class BasicModeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicModeWindow(QWidget *parent = 0);
    void drawLine(QString pic1, QString pic2, QString pos2, QString pos3);
    ~BasicModeWindow();

private:
    Ui::BasicModeWindow *ui;

protected:
    Game gameModel; //model层，用来进行逻辑处理
    QGridLayout *grid;
    double totleTime = 100; //总时间
    double speed = 0.5; //速率系数
    int PIC_NUM = 10; //花色数
    QTimer *timer;
    QPainter* painter;
    DrawLineLayer* drawLineLayer; //用于画线的layer
    HelpDialog *helpDialog;
    QSpinBox *box; // 设置时间
    QSpinBox *box2; // 设置花色数
    QDialog *changeSpeedDialog;
    ScoreDao *scoreDao;

    void initMap();
    void reset(bool flag);
    void select(const QString &msg); //鼠标点击图片时触发的事件

public slots:
    void startGame();
    void reStartGame();
    void pauseGame();
    void timerUpDate(); //计时器更新
    void resetMap(); //图片重排
    void findHint(); //提示
    void showHelp(); //显示帮助
    void changeSpeed();
    void _changeSpeed();

};

#endif // BASICMODEWINDOW_H
