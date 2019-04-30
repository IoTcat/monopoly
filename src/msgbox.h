
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package msgbox
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __MSGBOX_H_
#define __MSGBOX_H_

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "tools.h"

/**
 * Message Box
 *
 * @author yimian
 * @category Monopoly Game
 * @package msgbox
 */
class Msgbox{

public:
    Msgbox(int x, int y, int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };
    ~Msgbox(){this->clear();};

    inline void title(const std::string& title){
        this->_title = title;
    };

    const short print(const std::string& msg1, const std::string& msg2, const std::string& msg3, const std::string& ch1 = "", const std::string& ch2 = "") const;
    void clear() const;


private:
    std::string _title;
    int _X;
    int _Y;
    int _color;

};







#endif