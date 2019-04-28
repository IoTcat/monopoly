#include "roll.h"


int Roll::cast(){

    int res = (rand() % 6)+ 1;
    this->anime();
    this->print(res);
    return res;
}


void Roll::anime(){
    for(float i = 1; i < 300; i *= 1.2){
        this->print((rand() % 6)+ 1);
    }
    for(float i = 1; i < 500; i *= 1.2){
        this->print((rand() % 6)+ 1);
        Sleep(i);
    }
}

int Roll::print(int num)//游戏结束界面
{
    /*绘制游戏结束界面*/
    SetColor((rand() % (15-9+1))+ 9);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "----------" ;
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |          |" ;
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |          |" ;
    SetCursorPosition(this->_X + 1 + (5 - 1) / 2, this->_Y + 2);
    std::cout << num ;
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |          |" ;
    SetCursorPosition(this->_X + 1, this->_Y + 4);
    std::cout << "----------" ;

    return 1;
}


void Roll::clear(){

    for(int i = this->_Y; i < this->_Y + 5; i++){

        SetCursorPosition(this->_X, i);
        std::cout << "          " ;
    }
}