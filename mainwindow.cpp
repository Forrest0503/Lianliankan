#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basicmodewindow.h"
#include "relaxedmodewindow.h"
#include "levelmodewindow.h"
#include <QDialog>
#include <QToolBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setUpWelcomeWindow();

    ui->setupUi(this);
    connect(ui->button3, SIGNAL(clicked(bool)), this, SLOT(showBasicModeWindow()));
    connect(ui->button2, SIGNAL(clicked(bool)), this, SLOT(showRelaxedModeWindow()));
    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(showLevelModeWindow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showBasicModeWindow() {
    BasicModeWindow *bmw = new BasicModeWindow();
    bmw->setWindowTitle("欢乐连连看－基本模式");
    bmw->show();
    this->hide();
}

void MainWindow::showRelaxedModeWindow() {
    RelaxedModeWindow *rmw = new RelaxedModeWindow();
    rmw->setWindowTitle("欢乐连连看－休闲模式");
    rmw->show();
    this->hide();
}

void MainWindow::showLevelModeWindow() {
    LevelModeWindow *lmw = new LevelModeWindow();
    lmw->setWindowTitle("欢乐连连看－关卡模式（简单）");
    lmw->show();
    this->hide();
}

void MainWindow::setUpWelcomeWindow() {

    QMainWindow *window = new QMainWindow();
    window->setFixedSize(800,600);
    QCoreApplication::processEvents();

    QWidget *cenWidget = new QWidget(window);
    window->setCentralWidget(cenWidget);
    QLabel *welcomeLabel = new QLabel(cenWidget);
    welcomeLabel->setText("WELCOME TO LIANLIANKAN");
    QGridLayout *gridLayout = new QGridLayout(cenWidget);
    QFont ft;
    ft.setPointSize(32);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    welcomeLabel->setFont(ft);
    welcomeLabel->setPalette(pa);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(welcomeLabel);

    window->show();
    QTime t;
    t.start();
    while(t.elapsed()<1000) //让欢迎界面延迟1s
        QCoreApplication::processEvents();
    window->close();
}

