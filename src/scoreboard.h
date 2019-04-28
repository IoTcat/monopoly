#ifndef __SCOREBOARD_H_
#define __SCOREBOARD_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>


class ScoreBoard{

public:
    ScoreBoard(std::string title, int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
        this->_title = title;
    };


    int print(std::string msg1, std::string msg2, std::string msg3, std::string ch1 = "", std::string ch2 = "");


private:
    std::string _title;
    int _X;
    int _Y;
    int _color;


};







#endif