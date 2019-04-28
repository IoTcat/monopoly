#include "square.h"
#include <windows.h>
#include <iostream>
#include "tools.h"
#include <iomanip>

void Square::print()//绘制单元格
{

    if(this->ownerType == "PLAYER") SetColor(14);
    if(this->ownerType == "AI") SetColor(13);

    for (auto& point : _rowLines) //水平制表
    {
        point.PrintRowLine();
        Sleep(4);//调用Sleep函数可营造动画效果
    }

    for (auto& point : _columnLines) //竖直制表
    {
        point.PrintColumnLine();
        Sleep(4);
    }

    if(this->type == GO){
        SetCursorPosition(this->_X + 1, this->_Y + 2);
        std::cout << " GO " ;
    }else if(this->type == JAIL){
        SetCursorPosition(this->_X + 1, this->_Y + 2);
        std::cout << "JAIL" ;
    }else{

        SetCursorPosition(this->_X + 1, this->_Y + 1);
        std::cout << "Lv. " << this->_level ;

        SetCursorPosition(this->_X + 1, this->_Y + 2);
        std::cout << "$ " << setprecision(4) << this->getPrice();
    }


}


void Square::_drawLines(int x, int y){

    for(int i = 1; i < g_squareLength; i++){

        this->_rowLines.emplace_back(Point(x + i, y));
        this->_rowLines.emplace_back(Point(x + i, y + g_squareWidth));
    }

    for(int i = 1; i < g_squareWidth; i++){

        this->_columnLines.emplace_back(Point(x, y + i));
        this->_columnLines.emplace_back(Point(x + g_squareLength, y + i));
    }

    this->_leftLines.emplace_back(Point(x, y));
    this->_leftLines.emplace_back(Point(x, y + g_squareWidth));
    this->_rightLines.emplace_back(Point(x, y));
    this->_rightLines.emplace_back(Point(x + g_squareLength, y));
}


void Square::draw_player(){

    Point point(this->_X + 1, this->_Y + 3);

    point.yellow();
    point.PrintStar();
}

void Square::draw_ai(){

    Point point(this->_X + 3, this->_Y + 3);

    point.red();
    point.PrintCircular();
}

void Square::clear_player(){

    Point point(this->_X + 1, this->_Y + 3);

    point.Clear();
}

void Square::clear_ai(){

    Point point(this->_X + 3, this->_Y + 3);

    point.Clear();
}


void Square::buy(Player& p){

    this->owner = p.getName();
    this->ownerType = p.type;
    if(this->ownerType == "PLAYER") SetColor(14);
    else SetColor(13);
    this->print();
}
