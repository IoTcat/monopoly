
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package hintbox
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */


#ifndef __HINTBOX_H_
#define __HINTBOX_H_

#include "tools.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>


/**
 * Hint Box
 *
 * @author yimian
 * @category Monopoly Game
 * @package hintbox
 */
class Hintbox{

public:
    Hintbox(int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };
    ~Hintbox(){
        this->clear();
    };

    /* print hint box */
    const short print(const std::string& msg) const;
    /* clear hint box */
    void clear() const;
    /* set color */
    inline void color(const int& color){
        this->_color = color;
    };

private:
    int _X;
    int _Y;
    int _color;

};


#endif //__HINTBOX_H_