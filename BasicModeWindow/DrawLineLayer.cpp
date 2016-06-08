#include "DrawLineLayer.h"
DrawLineLayer::DrawLineLayer(QWidget *parent)
    : QWidget(parent)
{
}

DrawLineLayer::~DrawLineLayer()
{

}
//重新实现paintEvent
void DrawLineLayer::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPen pen;
    pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::red);
    paint.setPen(pen);
    if (!pos1.isNull() && !pos2.isNull()) {
        pos1.rx() += 20;
        pos1.ry() += 20;
        pos2.rx() += 20;
        pos2.ry() += 20;
        paint.drawLine(pos1, pos2);
    }
    if (!pos2.isNull() && !pos3.isNull()) {
        pos3.rx() += 20;
        pos3.ry() += 20;
        paint.drawLine(pos2, pos3);
    }
    if (!pos3.isNull() && !pos4.isNull()) {
        pos4.rx() += 20;
        pos4.ry() += 20;
        paint.drawLine(pos3, pos4);
    }
}

void DrawLineLayer::setPos1(QPoint pos) {
    this->pos1 = pos;
}

void DrawLineLayer::setPos2(QPoint pos) {
    this->pos2 = pos;
}

void DrawLineLayer::setPos3(QPoint pos) {
    this->pos3 = pos;
}

void DrawLineLayer::setPos4(QPoint pos) {
    this->pos4 = pos;
}

void DrawLineLayer::clear() {
    pos1.setX(0);
    pos1.setY(0);
    pos2.setX(0);
    pos2.setY(0);
    pos3.setX(0);
    pos3.setY(0);
    pos4.setX(0);
    pos4.setY(0);
    this->hide();
}
