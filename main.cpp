#include <MainWindow/mainwindow.h>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;

    w.setWindowTitle("欢乐连连看");

    w.show();

    return a.exec();
}
