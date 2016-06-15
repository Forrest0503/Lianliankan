#ifndef RELAXEDMODEWINDOW_H
#define RELAXEDMODEWINDOW_H

#include <QMainWindow>
#include "BasicModeWindow/basicmodewindow.h"
#include "Dao/scoredao.h"

namespace Ui {
class RelaxedModeWindow;
}

class RelaxedModeWindow : public BasicModeWindow
{
    Q_OBJECT

public:
    explicit RelaxedModeWindow(QWidget *parent = 0);
    void reset(bool flag);
    void initMap();
    void select(const QString &msg); //鼠标点击图片时触发的事件
    void drawLine(QString pic1, QString pic2, QString pos2, QString pos3);
    ~RelaxedModeWindow();

private:
    Ui::RelaxedModeWindow *ui;
    int credit = 0;
    int creditIncrement = 0;
    int toolsNum = 0;
    bool isUsingTool = false;
    QSpinBox *box2; // 设置花色数
    ScoreDao *scoreDao; //数据层

    void increaseCredit();
    void decreaseCredit(int num);
    bool creditIsEnoughForReset();
    bool creditIsEnoughForHint();

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
    void useTool(); //使用道具


};

#endif // RELAXEDMODEWINDOW_H
