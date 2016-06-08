#ifndef LEVELMODEWINDOW_H
#define LEVELMODEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LevelModeWindow;
}

class LevelModeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LevelModeWindow(QWidget *parent = 0);
    ~LevelModeWindow();

private:
    Ui::LevelModeWindow *ui;
};

#endif // LEVELMODEWINDOW_H
