#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <QString>
#include <QChar>
#include <QVector>

int oper = 0;
int ind = 0;
int stateNow = 0;

QVector<QVector<QString>> matrix;
QString defString;
QString canBe;
int qAll;
std::set<QChar> setCanBe = {'_'};
std::map<QChar, int> mapCanBe;

#endif // COMMON_H

