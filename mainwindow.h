#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Memento {
private:
    int lvl;
    int n1;
    int n2;
public:
    Memento(const int& l, const int& num1,const int& num2): lvl(l),n1(num1),n2(num2){}

    int getLvl() const;
    int getNum1() const;
    int getNum2() const;
};

class Originator{
private:
    int lvl;
    int n1,n2;

public:
    void setLvl(const int& l);
    int getLvl() const;
    void setN1(const int& n);
    int getN1() const;
    void setN2(const int& n);
    int getN2() const;

    Memento createMeme() const;
    void restoreMeme(const Memento& me);
};

class Caretaker{
private:
    std::vector<Memento> memes;
public:
    void addMemento(const Memento& me);
    Memento getMemento(int index) const;
};

class Game{
public:
    Game(){orig = Originator(); caret = Caretaker();}

    int n1,n2;

    void start();
    bool check(int inp);
    void save();
    void loadNextLvl();
    void loadChosenLvl(int index);
    int getCurLvl();

private:
    Originator orig;
    Caretaker caret;
    int answ=0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Game game;

    int LE_answ;
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
