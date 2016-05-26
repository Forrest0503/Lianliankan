#ifndef BASICMODEWINDOW_H
#define BASICMODEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QString>
#include <game.h>
#include <QTimer>

namespace Ui {
class BasicModeWindow;
}

class BasicModeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicModeWindow(QWidget *parent = 0);
    ~BasicModeWindow();

public slots:
    void startGame();
    void pauseGame();
    void initMap();
    void select(const QString &msg);
    void timerUpDate();

private:
    Game gameModel;

    Ui::BasicModeWindow *ui;
    QGridLayout *grid;
    double totleTime = 100;
    QTimer *timer;
};

#endif // BASICMODEWINDOW_H
