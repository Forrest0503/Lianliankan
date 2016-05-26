#ifndef MAPBUTTON_H
#define MAPBUTTON_H

#include <QPushButton>
#include <QTimer>

class MapButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MapButton(QWidget *parent = 0) : QPushButton(parent),
        pauseMsecs(400), intervalMsecs(30)
    {
        tm = new QTimer(this);
//        connect(tm, SIGNAL(timeout()), this, SLOT(on_pressed_last()));
//        connect(this, SIGNAL(pressed()), this, SLOT(on_pressed()));
//        connect(this, SIGNAL(released()), this, SLOT(on_released()));
        connect(this, SIGNAL(clicked()), this, SLOT(on_clicked()));
    }

private:
    QTimer *tm;
    long pauseMsecs;
    long intervalMsecs;

signals:
//    void keyPressed(const QString &msg);
//    void keyReleased(const QString &msg);
    void keyClicked(const QString &msg);

public slots:
//    void on_pressed() { emit this->keyPressed(this->objectName());
//                        tm->start(pauseMsecs); }
//    void on_pressed_last() { emit this->keyPressed(this->objectName());
//                             tm->setInterval(intervalMsecs); }
//    void on_released() { tm->stop(); emit this->keyReleased(this->objectName()); }
    void on_clicked() { emit this->keyClicked(this->objectName()); }
};
#endif // MAPBUTTON_H
