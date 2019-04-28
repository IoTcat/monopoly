#include "hintbox.h"


int Hintbox::print(std::string msg)//游戏结束界面
{
    /*绘制游戏结束界面*/
    Sleep(500);
    SetColor(this->_color);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "------------------------------------------" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - msg.length() / 2) / 2, this->_Y + 2);
    std::cout << msg ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X + 1, this->_Y + 4);
    std::cout << "------------------------------------------" ;
    Sleep(100);

    return 1;
}


void Hintbox::clear(){

    for(int i = this->_Y; i < this->_Y + 5; i++){

        SetCursorPosition(this->_X, i);
        std::cout << "                                           " ;
        Sleep(10);
    }
}