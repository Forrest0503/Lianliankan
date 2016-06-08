#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
namespace Ui {
class MainWindow; //模式选择界面
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //创建欢迎界面
    void setUpWelcomeWindow();

    ~MainWindow();

public slots:
    //弹出各种模式对应的窗口
    void showBasicModeWindow();
    void showRelaxedModeWindow();
    void showLevelModeWindow();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
