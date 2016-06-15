#ifndef SCOREDAO_H
#define SCOREDAO_H
#include <vector>
#include <QString>
#include <fstream>
#include <QDataStream>
#include <QTextStream>

class ScoreDao
{

public:
    void init();
    void insertItem(QString name, QString score);
    void outputItem(QString name, QString score);

    std::vector<std::vector<QString>*> *items;
    std::ifstream *in;
};

#endif // SCOREDAO_H
