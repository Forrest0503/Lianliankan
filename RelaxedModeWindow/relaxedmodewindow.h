#ifndef RELAXEDMODEWINDOW_H
#define RELAXEDMODEWINDOW_H

#include <QMainWindow>

namespace Ui {
class RelaxedModeWindow;
}

class RelaxedModeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RelaxedModeWindow(QWidget *parent = 0);
    ~RelaxedModeWindow();

private:
    Ui::RelaxedModeWindow *ui;
};

#endif // RELAXEDMODEWINDOW_H
