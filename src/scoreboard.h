#ifndef __SCOREBOARD_H_
#define __SCOREBOARD_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "player.h"


class Scoreboard{

public:
    Scoreboard(int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };


    int print(Player& p);


private:
    int _X;
    int _Y;
    int _color;


};







#endif