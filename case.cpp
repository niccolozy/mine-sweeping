#include "case.h"

Case::Case(int num, QWidget *parent): QPushButton(parent)
{
    this->num = num;
    etat = 0;
    hidden = true;
    flag = false;
    clickable = true;
    left_click = false;
    right_click = false;
}

Case::~Case()
{

}

int Case::get_etat()
{
    return etat;
}

void Case::set_etat(int etat)
{
    this->etat = etat;
}

void Case::set_hidden(bool hidden)
{
    this->hidden = hidden;
}

void Case::set_clickable(bool clickable)
{
    this->clickable = clickable;
}

void Case::incre_etat()
{
    etat++;
}

bool Case::get_hidden()
{
    return hidden;
}

bool Case::get_flag()
{
    return flag;
}

void Case::mousePressEvent(QMouseEvent *event)
{
    if(clickable == false)
        return;
    if(event->button() == Qt::LeftButton)
        left_click = true;
    if(event->button() == Qt::RightButton)
        right_click = true;
}


void Case::mouseReleaseEvent(QMouseEvent *event)
{
    if(left_click ==true && right_click == false)
    {
        hidden = false;
        if(!flag)
        {
            if(etat == 0)
                emit is_empty(num);
            else if(etat == 9)
                emit is_mine(num);
        }
    }
    else if(left_click ==false && right_click == true)
    {
        if(hidden == false && flag == false)
            return;
        if(flag)
        {
            flag = false;
            hidden = true;
            emit deflag_mine();
        }
        else
        {
            flag = true;
            hidden = false;
            emit flag_mine();
        }
    }
    else if(left_click ==true && right_click == true)
        emit is_double_clicked(num);
    left_click = false;
    right_click = false;
    emit need_update();
}
