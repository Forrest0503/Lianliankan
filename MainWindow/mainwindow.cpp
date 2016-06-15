#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BasicModeWindow/basicmodewindow.h"
#include "RelaxedModeWindow/relaxedmodewindow.h"
#include "LevelModeWindow/levelmodewindow.h"
#include <QDialog>
#include <QToolBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>
#include <HelpDialog/helpdialog.h>
#include <QStandardItemModel>
#include <vector>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setUpWelcomeWindow();

    ui->setupUi(this);

    scoreDao = new ScoreDao();
    scoreDao->init();

    //为不同模式的按钮添加信号槽
    connect(ui->button3, SIGNAL(clicked(bool)), this, SLOT(showBasicModeWindow()));
    connect(ui->button2, SIGNAL(clicked(bool)), this, SLOT(showRelaxedModeWindow()));
    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(showLevelModeWindow()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(showRankingList()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
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

void MainWindow::setUpWelcomeWindow() { //创建欢迎界面
    QMainWindow *window = new QMainWindow();
    window->setFixedSize(800,600);
    QCoreApplication::processEvents();

    QWidget *cenWidget = new QWidget(window);
    window->setCentralWidget(cenWidget);
    QLabel *emptyLabel = new QLabel(cenWidget);
    QLabel *welcomeLabel = new QLabel(cenWidget);
    welcomeLabel->setText("WELCOME TO LIANLIANKAN");
    QLabel *nameLabel = new QLabel(cenWidget);
    nameLabel->setText("\t\t by 程厚森");
    QGridLayout *gridLayout = new QGridLayout(cenWidget);
    QFont ft;
    ft.setPointSize(32);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    welcomeLabel->setFont(ft);
    welcomeLabel->setPalette(pa);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    ft.setPointSize(24);
    nameLabel->setFont(ft);
    nameLabel->setPalette(pa);
    nameLabel->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(emptyLabel);
    gridLayout->addWidget(welcomeLabel);
    gridLayout->addWidget(nameLabel);

    window->show();
    QTime t;
    t.start();
    while(t.elapsed()<1000) //让欢迎界面延迟1s
        QCoreApplication::processEvents();
    window->close();
}

void MainWindow::showHelp() {
    HelpDialog *helpDialog = new HelpDialog(this);
    helpDialog->showHelpDialog();
}

void MainWindow::showRankingList() {
    QDialog *dialog = new QDialog();
    QGridLayout *layout = new QGridLayout();
    dialog->setLayout(layout);
    QStandardItemModel *rankModel = new QStandardItemModel(); //TableViewModel
    rankTableView = new QTableView();
    rankTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rankTableView->setGeometry(550, 300, 155, 200);
    rankModel->setHorizontalHeaderItem(0, new QStandardItem("玩家姓名"));
    rankModel->setHorizontalHeaderItem(1, new QStandardItem("积分"));

    //从文件中读取排行榜
    char buffer[100];
    while (scoreDao->in->getline(buffer, sizeof(buffer))) {
        QString data(buffer);
        scoreDao->insertItem(data.left(12), data.right(3));
    }

    //给Model添加数据
    int row = 0;
    for (std::vector<QString>* each : *(scoreDao->items)) {
        rankModel->setItem(row, 0, new QStandardItem(each->at(0)));
        rankModel->setItem(row, 1, new QStandardItem(each->at(1)));
        row++;
    }
    rankModel->sort(1, Qt::DescendingOrder);

    rankTableView->setModel(rankModel);
    rankTableView->resizeColumnsToContents();
    layout->addWidget(rankTableView);
//    rankTableView->show();
    dialog->show();
}
