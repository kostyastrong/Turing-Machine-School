#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <QDebug>
#include <QThread>
#include <iostream>


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

void MainWindow::EraseAll() {
    ui->states->setRowCount(0);
    ui->states->setColumnCount(0);
    ui->showMeWhatYouGot->setColumnCount(0);
    ui->showMeWhatYouGot->setRowCount(0);

    oper = 0;
    ind = 0;
    lookAtMe = indAdd + 6;
    startOfWord = 400;
    stateNow = 0;
    finish = false;
}

void MainWindow::insertChar(QChar a, int indOfChar) {
    QTableWidgetItem* qcell;
    qcell = new QTableWidgetItem;
    qcell->setText(QString(a));
    ui->showMeWhatYouGot->setItem(0, indOfChar, qcell);
}

void MainWindow::on_newMachine_clicked()
{
    EraseAll();
    defString = ui->defaultString->text();
    canBe = ui->validChars->text();


    for (QChar i : canBe) {
        if (i != ' ') {
            setCanBe.insert(i);
        }
    }


    int indK = 0;
    for (QChar i : setCanBe) {
        mapCanBe[i] = indK++;
    }

    qAll = ui->numberStates->text().toInt();
    std::cout << defString.toStdString() << ' ' << qAll << std::endl;

    matrix.resize(qAll);
    for (int i = 0; i < qAll; ++i) {
        matrix[i].resize(setCanBe.size());
    }
    ui->states->setRowCount(qAll);
    ui->states->setColumnCount(setCanBe.size());

    QStringList forLabels;
    QStringList forVerLabels;
    for (QChar i : setCanBe) {
        forLabels.append(QString(i));
    }
    for (int i = 0; i < qAll; ++i) {
        forVerLabels.append(QString::number(i));
    }
    ui->states->setVerticalHeaderLabels(forVerLabels);
    ui->states->setHorizontalHeaderLabels(forLabels);

    ui->showMeWhatYouGot->insertRow(0);
    ui->showMeWhatYouGot->setColumnCount(showMeSize);
    std::cout << QString(defString[0]).toStdString() << std::endl;


    for (int i = 0; i < defString.size(); ++i) {
        insertChar(defString[i], indAdd + i);
        ui->showMeWhatYouGot->item(0, indAdd + i)->setBackground(Qt::gray);
    }
    for (int i = 0; i < indAdd; ++i) {
        insertChar('_', i);
        ui->showMeWhatYouGot->item(0, i)->setBackground(Qt::gray);
    }
    for (int i = indAdd + defString.size(); i < showMeSize; ++i) {
        insertChar('_', i);
        ui->showMeWhatYouGot->item(0, i)->setBackground(Qt::gray);
    }
    ui->showMeWhatYouGot->scrollToItem(ui->showMeWhatYouGot->item(0, lookAtMe));
    ui->showMeWhatYouGot->item(0, indAdd)->setBackground(Qt::darkCyan);
}


bool MainWindow::nextOper() {
    ++oper;
    if (oper > 10000) {
        std::cout << "To many operations";
        return true;
    }
    if (oper > 99) {
        qDebug() << stateNow;
    }

    QChar charNow = ind >= defString.size() || ind < 0 ? QChar('_') : defString[ind];
    int indOfLetter = mapCanBe[charNow];
    QString operNow = matrix[stateNow][indOfLetter];

    /*if (operNow[0] == '_' && ind >= 0 && ind < defString.size()) {
        defString.remove(ind, 1);
        int i = ind + 1;
        while (i < defString) {insertChar('_', i);
            insertChar(defString[i], startOfWord + i - 1);
        } operation of deleting*/

    if (operNow[0] != '-') {
        if (ind < 0) {
            defString = operNow[0] + defString;
            --startOfWord;
            insertChar(operNow[0], startOfWord);
        } else if (ind >= defString.size()) {
            insertChar(operNow[0], startOfWord + defString.size());
            defString += operNow[0];
        } else {
            defString[ind] = operNow[0];
            insertChar(operNow[0], startOfWord + ind);
        }
    }
    if (operNow[1] == '>') {
        ui->showMeWhatYouGot->item(0, startOfWord + ind)->setBackground(Qt::gray);
        ++ind;
        ++lookAtMe;
    } else if (operNow[1] == '<') {
        ui->showMeWhatYouGot->item(0, startOfWord + ind)->setBackground(Qt::gray);
        --ind;
        --lookAtMe;
    }
    std::cout << lookAtMe << std::endl;
    ui->showMeWhatYouGot->item(0, startOfWord + ind)->setBackground(Qt::darkCyan);
    ui->showMeWhatYouGot->scrollToItem(ui->showMeWhatYouGot->item(0, 0));
    ui->showMeWhatYouGot->scrollToItem(ui->showMeWhatYouGot->item(0, lookAtMe));
    if (operNow[2] != '-') {
        int nextState = 0;
        for (int i = 2; i < operNow.size() - 1; ++i) {
            nextState *= 10;
            nextState += operNow[i].toLatin1() - QChar('0').toLatin1();
        }
        stateNow = nextState;
    }

    if (operNow.back() == '!') {
        return 1;
    }
    return 0;

}
void MainWindow::on_nextAction_clicked()
{
    if (finish) {
        std::cout << "Finish" << std::endl;
        return;
    }
    finish = nextOper();
}

void MainWindow::on_pushButton_clicked()
{
    freopen("input.txt", "r", stdin);
    for (int i = 0; i < qAll; ++i) {
        for (int j = 0; j < setCanBe.size(); ++j) {
            std::string x;
            std::cin >> x;
            matrix[i][j] = QString::fromStdString(x);
        }
    }
    /*for (int i = 0; i < qAll; ++i) {
        for (int j = 0; j < setCanBe.size(); ++j) {
            QTableWidgetItem* itemNow = ui->states->item(i, j);
            matrix[i][j] = itemNow->text();
        }
    }*/
    for (int i = 0; i < qAll; ++i) {
        for (int j = 0; j < setCanBe.size(); ++j) {
            std::cout << matrix[i][j].toStdString() << ' ';
        }
        std::cout << std::endl;
    }


}

void MainWindow::on_autoComplete_clicked()
{
    for (;;) {
        for (int i = 0; i < 1000000; ++i);
        if (nextOper()) break;
    }
    finish = true;
    std::cout << "Finish" << std::endl;
}
