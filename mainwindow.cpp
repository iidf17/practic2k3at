    #include "mainwindow.h"
    #include "ui_mainwindow.h"
    #include <QDebug>
    #include <cstdlib>
    #include <ctime>

    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        ui->ifLvlUp->clear();
        game.start();
        ui->YourLvl->setText("Your level: " + QString::number(game.getCurLvl()));
        ui->primerLabel->setText(QString::number(game.n1) + " + " + QString::number(game.n2) + " = ");
        qDebug()<<game.n1<<" + "<< game.n2 << " = " << game.n1+game.n2;
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    int Memento::getLvl() const{ return lvl; }
    int Memento::getNum1() const{ return n1; }
    int Memento::getNum2() const{ return n2; }

    void Originator::setLvl(const int &l){ lvl = l; }
    int Originator::getLvl() const{ return lvl; }

    void Originator::setN1(const int &n){ n1 = n; }
    int Originator::getN1() const{ return n1; }

    void Originator::setN2(const int &n){ n2 = n; }
    int Originator::getN2() const{ return n2; }

    Memento Originator::createMeme() const{ return Memento(lvl,n1,n2) ;}
    void Originator::restoreMeme(const Memento &me){ lvl = me.getLvl();  n1 = me.getNum1(); n2 = me.getNum2();}

    void Caretaker::addMemento(const Memento& me){ memes.push_back(me); }
    Memento Caretaker::getMemento(int index) const { return memes[index];}

    void Game::start(){
        orig.setLvl(1);
        std::srand(std::time(nullptr));

        n1 = std::rand()%100;
        n2 = std::rand()%100;
        orig.setN1(n1);
        orig.setN2(n2);
        answ = n1+n2;
        caret.addMemento(orig.createMeme());
    }

    bool Game::check(int inp){
        if (answ == inp)return true;
        else return false;
    }

    void Game::loadNextLvl(){
        orig.setLvl(orig.getLvl()+1);

        n1 = std::rand()%100;
        n2 = std::rand()%100;
        orig.setN1(n1);
        orig.setN2(n2);
        answ = n1+n2;
    }

    void Game::loadChosenLvl(int index){
        int idx = index;
        //orig.setLvl(me.getLvl());
        //orig.setN1(me.getNum1());
        //orig.setN2(me.getNum2());
        orig.restoreMeme(caret.getMemento(idx));
        n1=orig.getN1();
        n2=orig.getN2();
        answ=n1+n2;
    }

    void Game::save(){
        caret.addMemento(orig.createMeme());
    }

    int Game::getCurLvl(){ return orig.getLvl(); }

    void MainWindow::on_pushButton_clicked()
    {

        if(game.check(LE_answ)){
            int lvl_ = game.getCurLvl()+1;
            qDebug()<<lvl_;
            int index = ui->comboBox->findText(QString::number(lvl_));
            qDebug()<<index;
            if (index == -1) {
                ui->comboBox->addItem(QString::number((game.getCurLvl())+1));
                game.loadNextLvl();
                game.save();
            }
            else game.loadChosenLvl(game.getCurLvl());
            ui->YourLvl->setText("Your level: " + QString::number(game.getCurLvl()));
            ui->ifLvlUp->setText("Correct! Level up!");
            //ui->comboBox->setCurrentIndex(game.getCurLvl());
            ui->primerLabel->setText(QString::number(game.n1) + " + " + QString::number(game.n2) + " = ");

        }
        else ui->ifLvlUp->setText("Wrong! Try again.");
        qDebug()<<game.n1<<" + "<<game.n2;

    }

    void MainWindow::on_comboBox_currentIndexChanged(int index)
    {
        game.loadChosenLvl(index);
        ui->ifLvlUp->setText("Level changed");
        ui->YourLvl->setText("Your level: " + QString::number(game.getCurLvl()));
        ui->primerLabel->setText(QString::number(game.n1) + " + " + QString::number(game.n2) + " = ");
    }

    void MainWindow::on_lineEdit_textChanged(const QString &arg1)
    {
        LE_answ = arg1.toInt();
    }
