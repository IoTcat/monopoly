
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package point
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */
#include "point.h"

#include <iostream>

void Point::Print()//输出点
{
    SetCursorPosition(x, y);
    std::cout << "@" ;
}

void Point::PrintCircular()//输出圆形
{
    SetCursorPosition(x, y);
    std::cout << "o" ;
}

void Point::PrintStar()//输出星星
{
    SetCursorPosition(x, y);
    std::cout << " o" ;
}


void Point::PrintRowLine()//输出水平线
{
    SetCursorPosition(x, y);
    std::cout << "--" ;
}

void Point::PrintColumnLine()//输出水平线
{
    SetCursorPosition(x, y);
    std::cout << "| " ;
}

void Point::PrintLeftLine()//输出左上下角
{
    SetCursorPosition(x, y);
    std::cout << "--" ;
}

void Point::PrintRightLine()//输出右上下角
{
    SetCursorPosition(x, y);
    std::cout << "- " ;
}


void Point::Clear()//清除输出
{
    SetCursorPosition(x, y);
    std::cout << "  " ;
}

void Point::ChangePosition(const int x, const int y)//改变坐标
{
    this->x = x;
    this->y = y;
}
