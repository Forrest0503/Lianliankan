#include "levelmodewindow.h"
#include "ui_levelmodewindow.h"

LevelModeWindow::LevelModeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelModeWindow)
{
    ui->setupUi(this);
}

LevelModeWindow::~LevelModeWindow()
{
    delete ui;
}
