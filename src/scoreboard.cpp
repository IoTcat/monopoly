#include "scoreboard.h"
#include <iomanip>


int Scoreboard::print(Player& p)//游戏结束界面
{
    /*绘制游戏结束界面*/
    Sleep(500);
    SetColor(this->_color);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "--------------------" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |                   |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |                   |" ;
    SetCursorPosition(this->_X + 1 + (10 - p.getName().length() / 2) / 2, this->_Y + 2);
    std::cout << p.getName();
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |                   |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 4);
    std::cout << " |                   |" ;
    SetCursorPosition(this->_X + 1 + 7 / 2, this->_Y + 4);
    std::cout << "$ " << setprecision(4) << p.getBalance() ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 5);
    std::cout << " |                   |" ;
    Sleep(100);

    return 1;
}