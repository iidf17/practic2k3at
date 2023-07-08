#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Memento {
private:
    int lvl;
public:
    Memento(const int& l): lvl(l){}

    int getLvl() const;
};

class Originator{
private:
    int lvl;

public:
    void setLvl(const int& l);
    int getLvl() const;
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Originator orig;
    Caretaker caret;

    int curLvl = 1;
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
