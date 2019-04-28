#ifndef __ROLL_H_
#define __ROLL_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include <time.h>


class Roll{

public:
    Roll(int x, int y){
        this->_X = x;
        this->_Y = y;
    };
    ~Roll(){this->clear();};


    int cast();
    void clear();
    void anime();


private:
    int _X;
    int _Y;
    int print(int num);

};



#endif