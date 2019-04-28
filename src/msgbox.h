#ifndef __MSGBOX_H_
#define __MSGBOX_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>


class Msgbox{

public:
    Msgbox(int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };
    ~Msgbox(){this->clear();};

    inline void title(std::string title){
        this->_title = title;
    };

    int print(std::string msg1, std::string msg2, std::string msg3, std::string ch1 = "", std::string ch2 = "");
    void clear();


private:
    std::string _title;
    int _X;
    int _Y;
    int _color;

};







#endif