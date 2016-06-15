#ifndef GAME_H
#define GAME_H

#include <QString>

//处理游戏逻辑

class Game {
public:
    int map[12][18];
    QString selectedPic;
//    QString pic2;
    int totalPic = 0;
    bool flagA = false, flagB = false, flagC = false; //转折点数量
    int rawMap[10][16];//未经打乱的游戏棋盘

    bool linkWithNoCorner(QString pic1, QString pic2);
    bool linkWithOneCorner(QString pic1, QString pic2, QString& pos2);
    bool linkWithTwoCorner(QString pic1, QString pic2, QString& pos2, QString& pos3);
    void useTool(QString pic1, QString pic2);
    bool isWin();
    void clearRawMap();
    void init();


protected:
//    bool linkWithNoCorner(int &x1, int &y1, int &x2, int & y2);

private:
    void getPosition(int &x1, int &y1, int &x2, int & y2, QString pic1, QString pic2);
    bool link(int x1, int y1, int x2, int y2);

};
#endif // GAME_H
