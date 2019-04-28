#ifndef __HINTBOX_H_
#define __HINTBOX_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>


class Hintbox{

public:
    Hintbox(int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };
    ~Hintbox(){this->clear();};


    int print(std::string msg);
    void clear();
    void color(int color){
        this->_color = color;
    };


private:
    int _X;
    int _Y;
    int _color;

};







#endif