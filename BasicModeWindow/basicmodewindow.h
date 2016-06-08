#ifndef BASICMODEWINDOW_H
#define BASICMODEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QString>
#include "Model/game.h"
#include <QTimer>
#include <QPainter>
#include "DrawLineLayer.h"

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

public slots:
    void startGame();
    void reStartGame();
    void pauseGame();
    void initMap();
    void select(const QString &msg); //鼠标点击图片时触发的事件
    void timerUpDate(); //计时器更新
    void resetMap(); //图片重排
    void findHint(); //提示

private:
    Game gameModel; //model层，用来进行逻辑处理
    Ui::BasicModeWindow *ui;
    QGridLayout *grid;
    double totleTime = 100; //总时间
    int PIC_NUM = 10; //花色数
    QTimer *timer;
    QPainter* painter;
    DrawLineLayer* drawLineLayer; //用于画线的layer

    void reset(bool flag);
};

#endif // BASICMODEWINDOW_H
