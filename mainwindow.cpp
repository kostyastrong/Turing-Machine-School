#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <set>
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->states->insertRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newMachine_clicked()
{
    QString defString = ui->defaultString->text();
    QString canBe = ui->validChars->text();

    std::set<QChar> setCanBe = {'_'};
    for (QChar i : canBe) {
        if (i != ' ') {
            setCanBe.insert(i);
        }
    }

    std::map<QChar, int> mapCanBe;
    int ind = 1;
    for (QChar i : setCanBe) {
        mapCanBe[i] = ind++;
    }

    int qAll = ui->numberStates->text().toInt();
    std::cout << defString.toStdString() << ' ' << qAll << std::endl;

    QString matrix[qAll][setCanBe.size() + 1];
    for (int i = 0; i < qAll; ++i) {
        ui->showMeWhatYouGot
    }

}
