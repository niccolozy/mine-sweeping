#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    dimension = 9;
    num_mines = 10;

    dimension_box = new QSpinBox;
    dimension_box->setMinimum(9);
    dimension_box->setSuffix("  cases");
    connect(dimension_box,SIGNAL(valueChanged(int)),this,SLOT(dimension_modified(int)));

    num_mines_box = new QSpinBox;
    num_mines_box->setMinimum(10);
    num_mines_box->setMaximum(dimension*dimension/8);
    num_mines_box->setSuffix("  mines");
    connect(num_mines_box,SIGNAL(valueChanged(int)),this,SLOT(num_mines_modified(int)));

    restart = new QPushButton;
    restart->setText(tr("Restart"));
    connect(restart,SIGNAL(clicked()),this,SLOT(new_game()));

    jeu = new Zone_mines(dimension,num_mines);


    layout1 = new QVBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->addWidget(dimension_box);
    layout2->addWidget(num_mines_box);
    layout2->addWidget(restart);
    layout1->addLayout(layout2);
    layout1->addWidget(jeu);
    setLayout(layout1);
}

MainWindow::~MainWindow()
{

}

void MainWindow::dimension_modified(int dimension)
{
    this->dimension = dimension;
    num_mines_box->setMaximum(dimension*dimension/8);
}

void MainWindow::num_mines_modified(int num_mines)
{
    this->num_mines = num_mines;
}

void MainWindow::new_game()
{
    delete jeu;
    jeu = new Zone_mines(dimension,num_mines);
    layout1->addWidget(jeu);
    this->adjustSize();
}
