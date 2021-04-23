#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include <QDebug>


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


    int ind = 1;
    for (QChar i : setCanBe) {
        mapCanBe[i] = ind++;
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
    for (QChar i : setCanBe) {
        forLabels.append(QString(i));
    }
    ui->states->setHorizontalHeaderLabels(forLabels);

    ui->showMeWhatYouGot->insertRow(0);
    ui->showMeWhatYouGot->setColumnCount(1000);
}

void nextOper() {
    ++oper;

}
void MainWindow::on_nextAction_clicked()
{
}

void MainWindow::on_pushButton_clicked()
{
    for (int i = 0; i < qAll; ++i) {
        for (int j = 0; j < setCanBe.size(); ++j) {

        }
    }
}
