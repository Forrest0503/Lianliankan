#include "relaxedmodewindow.h"
#include "ui_relaxedmodewindow.h"

RelaxedModeWindow::RelaxedModeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RelaxedModeWindow)
{
    ui->setupUi(this);

}

RelaxedModeWindow::~RelaxedModeWindow()
{
    delete ui;
}
