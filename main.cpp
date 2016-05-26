#include "mainwindow.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;



    w.setWindowTitle("Enter your age");


    w.show();

    return a.exec();
}
