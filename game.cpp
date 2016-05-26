#include "game.h"
#include <iostream>
#include <basicmodewindow.h>

using namespace std;

bool Game::isWin() {
    if (totalPic == 0) {
        return true;
    } else {
        return false;
    }
}

void Game::getPosition(int &x1, int &y1, int &x2, int & y2, QString pic1, QString pic2) {
    x1 = pic1.toInt() / 18;
    y1 = pic1.toInt() % 18;
    x2 = pic2.toInt() / 18;
    y2 = pic2.toInt() % 18;
}

bool Game::link(int x1, int y1, int x2, int y2) {
    int k = 0;
    if (x1 != x2 && y1 != y2) {
        return false;
    }
    if (map[x1][y1] != map[x2][y2]) {
        return false;
    }
    if (x1 == x2) {
        for (k = y1 + 1; k < y2; k++)
            if (map[x1][k] != "")
                return false;
        for (k = y2 + 1; k < y1; k++)
            if (map[x1][k] != "")
                return false;
    }
    if (y1 == y2) {
        for (k = x1 + 1; k < x2; k++)
            if (map[k][y1] != "")
                return false;
        for (k = x2 + 1; k < x1; k++)
            if (map[k][y1] != "")
                return false;
    }
    return true;
}

bool Game::linkWithNoCorner(QString pic1, QString pic2) {
    int x1, x2, y1, y2;
    getPosition(x1, y1, x2, y2, pic1, pic2);

    bool result = link(x1, y1, x2, y2);
    if (result == true) {
        map[x1][y1] = "";
        map[x2][y2] = "";
        totalPic -= 2;
    }

    return result;
}

bool Game::linkWithOneCorner(QString pic1, QString pic2) {
    int x1, x2, y1, y2;
    getPosition(x1, y1, x2, y2, pic1, pic2);

    if (x1 == x2 || y1 == y2) {
        return false;
    }
    if (map[x1][y1] != map[x2][y2]) {
        return false;
    }

    bool planA = false, planB = false;
    if (map[x1][y2] == "") {
        map[x1][y2] = map[x1][y1];
        if (link(x1, y2, x1, y1) && link(x1, y2, x2, y2)) {
            planA = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
        }
        map[x1][y2] = "";
    }

    if (map[x2][y1] == "") {
        map[x2][y1] = map[x1][y1];
        if (link(x2, y1, x1, y1) && link(x2, y1, x2, y2)) {
            planB = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
        }
        map[x2][y1] = "";
    }

    if (planA || planB) {
        totalPic -= 2;
        return true;
    }
    else
        return false;
}

bool Game::linkWithTwoCorner(QString pic1, QString pic2) {
    int x1, x2, y1, y2;
    getPosition(x1, y1, x2, y2, pic1, pic2);


    if (map[x1][y1] != map[x2][y2]) {
        return false;
    }

    bool planA = false, planB = false, planC = false, planD = false;
    //向上
    for (int i = x1 - 1; i >= 0; i--) {
        if (map[i][y1] != "")
            break;
        map[i][y1] = map[x1][y1];
        QString p1 = QString::number(i*18 + y1);
        QString p2 = QString::number(x2*18 + y2);
        if (linkWithOneCorner(p1, p2)) {
            planA = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
            break;
        }
        map[i][y1] = "";
    }

    //向左
    for (int i = y1 - 1; i >= 0; i--) {
        if (map[x1][i] != "")
            break;
        map[x1][i] = map[x1][y1];
        QString p1 = QString::number(x1*18 + i);
        QString p2 = QString::number(x2*18 + y2);
        if (linkWithOneCorner(p1, p2)) {
            planA = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
            break;
        }
        map[x1][i] = "";
    }

    //向右
    for (int i = y1 + 1; i < 18; i++) {
        if (map[x1][i] != "")
            break;
        map[x1][i] = map[x1][y1];
        QString p1 = QString::number(x1*18 + i);
        QString p2 = QString::number(x2*18 + y2);
        if (linkWithOneCorner(p1, p2)) {
            planA = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
            break;
        }
        map[x1][i] = "";
    }

    //向下
    for (int i = x1 + 1; i < 12; i--) {
        if (map[i][y1] != "")
            break;
        map[i][y1] = map[x1][y1];
        QString p1 = QString::number(i*18 + y1);
        QString p2 = QString::number(x2*18 + y2);
        if (linkWithOneCorner(p1, p2)) {
            planA = true;
            map[x1][y1] = "";
            map[x2][y2] = "";
            break;
        }
        map[i][y1] = "";
    }

    if (planA || planB || planC || planD) {
        return true;
    }
    else {
        return false;
    }

}

