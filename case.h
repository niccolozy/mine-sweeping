#ifndef CASE_H
#define CASE_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>


class Case : public QPushButton
{
    Q_OBJECT
    int num;
    int etat;

    bool hidden;
    bool flag;
    bool clickable;
    bool left_click;
    bool right_click;
public:
    Case(int num,QWidget *parent);
    ~Case();

    int get_etat();
    bool get_hidden();
    bool get_flag();
    void set_etat(int etat);
    void set_hidden(bool hidden);
    void set_clickable(bool clickable);
    void incre_etat();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void is_empty(int);
    void is_mine(int);
    void is_double_clicked(int);
    void flag_mine();
    void deflag_mine();
    void need_update();
};

#endif // CASE_H
