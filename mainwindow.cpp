#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ifLvlUp->clear();

    orig.setLvl(curLvl);
    caret.addMemento(orig.createMeme());
}

MainWindow::~MainWindow()
{
    delete ui;
}

int Memento::getLvl() const{ return lvl; }

void Originator::setLvl(const int &l){ lvl = l; }

int Originator::getLvl() const{ return lvl; }

Memento Originator::createMeme() const{ return Memento(lvl) ;}

void Originator::restoreMeme(const Memento &me){ lvl = me.getLvl(); }

void Caretaker::addMemento(const Memento& me){ memes.push_back(me); }

Memento Caretaker::getMemento(int index) const { return memes[index];}

void MainWindow::on_pushButton_clicked()
{
    curLvl++;

    QString clvl = QString::number(curLvl);

    orig.setLvl(curLvl);
    caret.addMemento(orig.createMeme());

    ui->YourLvl->setText("Your level: " + QString::number(curLvl));
    ui->ifLvlUp->setText("Level up!");

    int index = ui->comboBox->findText(clvl);

    if (index == -1) {
        ui->comboBox->addItem(clvl);
    }

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    curLvl=index+1;

    orig.restoreMeme(caret.getMemento(index));

    ui->ifLvlUp->setText("Level changed");
    ui->YourLvl->setText("Your level: " + QString::number(curLvl));

}
