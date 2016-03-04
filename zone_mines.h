#ifndef ZONE_MINES_H
#define ZONE_MINES_H

#include <QWidget>
#include <QLabel>
#include "case.h"

class Zone_mines : public QWidget
{
    Q_OBJECT
    std::vector<Case*> echequier;
    int num_mines;
    int dimension;
    QLabel* information;

public:
    explicit Zone_mines(int dimension,int num_mines,QWidget *parent = 0);
    ~Zone_mines();
    void put_mines();
    void lose();
    void win();

signals:

public slots:
    void click_empty(int num);
    void double_click(int num);
    void click_mine(int num);
    void check_win();
    void deflag();
    void echequier_update();

};

#endif // ZONE_MINES_H
