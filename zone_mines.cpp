#include "zone_mines.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <cstdlib>
#include <ctime>

int Delta_X[8]={-1,-1,-1,0,0,1,1,1};
int Delta_Y[8]={-1,0,1,-1,1,-1,0,1};

Zone_mines::Zone_mines(int dimension, int num_mines, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    QGridLayout* layout1 = new QGridLayout;
    layout1->setSpacing(3);

    this->num_mines = num_mines;
    this->dimension = dimension;

    information = new QLabel;
    information->setText(tr("Current mines :")+QString::number(this->num_mines));
    information->setAlignment(Qt::AlignCenter);
    layout->addWidget(information);

    for(int i=0;i < dimension*dimension;i++)
    {
        Case* new_case = new Case(i,this);
        new_case->setFixedSize(QSize(29,29));
        new_case->setIcon(QPixmap("hidden.png"));
        new_case->setIconSize(QSize(25,25));

        connect(new_case,SIGNAL(is_empty(int)),this,SLOT(click_empty(int)));
        connect(new_case,SIGNAL(is_mine(int)),this,SLOT(click_mine(int)));
        connect(new_case,SIGNAL(is_double_clicked(int)),this,SLOT(double_click(int)));
        connect(new_case,SIGNAL(flag_mine()),this,SLOT(check_win()));
        connect(new_case,SIGNAL(deflag_mine()),this,SLOT(deflag()));
        connect(new_case,SIGNAL(need_update()),this,SLOT(echequier_update()));

        echequier.push_back(new_case);
        layout1->addWidget(new_case,i/dimension,i%dimension);
    }

    layout->addLayout(layout1);
    setLayout(layout);


    put_mines();
}

Zone_mines::~Zone_mines()
{

}

void Zone_mines::echequier_update()
{
    for(int i=0;i < echequier.size();i++)
    {
        if(echequier[i]->get_hidden())
            echequier[i]->setIcon(QPixmap("hidden.png"));
        else if(echequier[i]->get_flag())
        {
            if(echequier[i]->get_etat() == 11)
                echequier[i]->setIcon(QPixmap("wrong_flag.png"));
            else
                echequier[i]->setIcon(QPixmap("flag.png"));
        }
        else
        {
            switch (echequier[i]->get_etat())
            {
            case 0:
                echequier[i]->setIcon(QPixmap("empty.png"));
                break;
            case 1:
                echequier[i]->setIcon(QPixmap("1.png"));
                break;
            case 2:
                echequier[i]->setIcon(QPixmap("2.png"));
                break;
            case 3:
                echequier[i]->setIcon(QPixmap("3.png"));
                break;
            case 4:
                echequier[i]->setIcon(QPixmap("4.png"));
                break;
            case 5:
                echequier[i]->setIcon(QPixmap("5.png"));
                break;
            case 6:
                echequier[i]->setIcon(QPixmap("6.png"));
                break;
            case 7:
                echequier[i]->setIcon(QPixmap("7.png"));
                break;
            case 8:
                echequier[i]->setIcon(QPixmap("8.png"));
            case 9:
                echequier[i]->setIcon(QPixmap("mine.png"));
                break;
            case 10:
                echequier[i]->setIcon(QPixmap("explosion.png"));
                break;
            default:
                break;
            }
        }
    }
}

void Zone_mines::put_mines()
{
    srand(time(NULL));
    for(int i=0;i<num_mines;i++)
    {
        int x=rand()%dimension;
        int y=rand()%dimension;
        if(echequier[x*dimension+y]->get_etat() != 9)
        {
            echequier[x*dimension+y]->set_etat(9);
            for(int j=0;j<8;j++)
            {
                int new_x = x+Delta_X[j];
                int new_y = y+Delta_Y[j];
                if(new_x > -1 && new_x < dimension && new_y > -1 && new_y < dimension)
                {
                    if(echequier[new_x*dimension+new_y]->get_etat() != 9)
                        echequier[new_x*dimension+new_y]->incre_etat();
                }
            }
        }
        else
            i--;
    }
}

void Zone_mines::click_empty(int num)
{
    int x = num / dimension;
    int y = num % dimension;
    for(int i=0;i<8;i++)
    {
        int new_x = x+Delta_X[i];
        int new_y = y+Delta_Y[i];
        int new_num = new_x*dimension+new_y;
        if(new_x > -1 && new_x < dimension && new_y > -1 && new_y < dimension)
        {
            if(echequier[new_num]->get_etat() != 9 && echequier[new_num]->get_flag() == false
                    && echequier[new_num]->get_hidden() == true)
            {
                echequier[new_num]->set_hidden(false);
                if(echequier[new_num]->get_etat() == 0)
                    click_empty(new_num);
            }
        }
    }
}

void Zone_mines::click_mine(int num)
{
    echequier[num]->set_etat(10);
    lose();
}

void Zone_mines::lose()
{
    for(int i=0;i<echequier.size();i++)
    {
        echequier[i]->set_clickable(false);
        if(echequier[i]->get_etat() == 9)
            echequier[i]->set_hidden(false);
    }
    information->setText(tr("You lose... "));
}

void Zone_mines::double_click(int num)
{
    int x = num / dimension;
    int y = num % dimension;
    int num_case_flagged = 0;
    bool lose = false;

    for(int i=0;i<8;i++)
    {
        int new_x = x+Delta_X[i];
        int new_y = y+Delta_Y[i];
        int new_num = new_x*dimension+new_y;
        if(new_x > -1 && new_x < dimension && new_y > -1 && new_y < dimension)
        {
            if(echequier[new_num]->get_flag() == true)
                num_case_flagged++;
        }
    }

    if(num_case_flagged == echequier[num]->get_etat())
    {
        for(int i=0;i<8;i++)
        {
            int new_x = x+Delta_X[i];
            int new_y = y+Delta_Y[i];
            int new_num = new_x*dimension+new_y;
            if(new_x > -1 && new_x < dimension && new_y > -1 && new_y < dimension)
            {
                if(echequier[new_num]->get_flag() == false)
                {
                    echequier[new_num]->set_hidden(false);
                    if(echequier[new_num]->get_etat() == 9)
                    {
                        echequier[new_num]->set_etat(10);
                        lose = true;
                    }
                    else if(echequier[new_num]->get_etat() == 0)
                        click_empty(new_num);
                }
                if(echequier[new_num]->get_flag() == true && echequier[new_num]->get_etat() != 9)
                    echequier[new_num]->set_etat(11);
            }
        }
    }
    if(lose == true)
        this->lose();
}

void Zone_mines::check_win()
{
    num_mines--;
    information->setText(tr("Current mines :")+QString::number(this->num_mines));
    for(int i=0;i<echequier.size();i++)
    {
        if(echequier[i]->get_etat() == 9 && echequier[i]->get_flag() == false)
            return;
        if(echequier[i]->get_etat() != 9 && echequier[i]->get_flag() == true)
            return;
    }
    win();
}

void Zone_mines::win()
{
    for(int i=0;i<echequier.size();i++)
    {
        echequier[i]->set_clickable(false);
        if(echequier[i]->get_etat() != 9)
            echequier[i]->set_hidden(false);
    }
    information->setText(tr("You win !!!!"));
}

void Zone_mines::deflag()
{
    num_mines++;
    information->setText(tr("Current mines :")+QString::number(this->num_mines));
}
