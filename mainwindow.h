#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setUpWelcomeWindow();
    void closeWelcomeWindow();

    ~MainWindow();

public slots:
    void showBasicModeWindow();
    void showRelaxedModeWindow();
    void showLevelModeWindow();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
