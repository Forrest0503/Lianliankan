#ifndef GAME_H
#define GAME_H

#include <QString>

//处理游戏逻辑

class Game {
public:
    QString map[12][18];
    QString pic1;
    QString pic2;
    int totalPic = 0;

    bool linkWithNoCorner(QString pic1, QString pic2);
    bool linkWithOneCorner(QString pic1, QString pic2);
    bool linkWithTwoCorner(QString pic1, QString pic2);
    bool isWin();

protected:
//    bool linkWithNoCorner(int &x1, int &y1, int &x2, int & y2);

private:
    void getPosition(int &x1, int &y1, int &x2, int & y2, QString pic1, QString pic2);
    bool link(int x1, int y1, int x2, int y2);
};
#endif // GAME_H
