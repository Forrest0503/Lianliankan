#include "scoredao.h"
#include <QFile>
#include <QMessageBox>

void ScoreDao::insertItem(QString name, QString score) {
    std::vector<QString> *item = new std::vector<QString>();
    item->push_back(name);
    item->push_back(score);
    items->push_back(item);
}

void ScoreDao::init() {
    in = new std::ifstream("/Users/Jason/score.txt");
    items = new std::vector<std::vector<QString>*>();
}

void ScoreDao::outputItem(QString name, QString score) {
    QFile file("/Users/Jason/score.txt");
    if (!file.open(QIODevice::Append|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
        return ;
    }
    QTextStream out(&file);
    QString data = "\n" + name + score;
    out << data;
    out.flush();
    file.close();
}
