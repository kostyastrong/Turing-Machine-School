#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <QString>
#include <QChar>
#include <QVector>
#include <QColor>

int oper = 0;
int ind = 0;
const int indAdd = 400;
int lookAtMe = indAdd + 6;
const int showMeSize = 1000;
int startOfWord = 400;
int stateNow = 0;
bool finish = false;
QColor bg;


QVector<QVector<QString>> matrix;
QString defString;
QString canBe;
int qAll;
std::set<QChar> setCanBe = {'_'};
std::map<QChar, int> mapCanBe;

#endif // COMMON_H

