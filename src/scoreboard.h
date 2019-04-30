
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package scoreboard
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __SCOREBOARD_H_
#define __SCOREBOARD_H_


#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "player.h"
#include "tools.h"


/**
 * score board
 *
 * @author yimian
 * @category Monopoly Game
 * @package scoreboard
 */
class Scoreboard{

public:
    Scoreboard(const int x, const int y, const int color){
        this->_X = x;
        this->_Y = y;
        this->_color = color;
    };

    const int print(Player& p) const;

private:
    int _X;
    int _Y;
    int _color;

};


#endif // __SCOREBOARD_H_