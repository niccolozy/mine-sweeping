#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "zone_mines.h"



class MainWindow : public QWidget
{
    Q_OBJECT
    QSpinBox* dimension_box;
    int dimension;
    QSpinBox* num_mines_box;
    int num_mines;
    QPushButton* restart;
    Zone_mines* jeu;
    QVBoxLayout* layout1;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

public slots:
    void dimension_modified(int);
    void num_mines_modified(int);
    void new_game();

};

#endif // MAINWINDOW_H
