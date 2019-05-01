
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package roll
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __ROLL_H_
#define __ROLL_H_

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include <time.h>
#include "tools.h"

/**
 * roll
 *
 * @author yimian
 * @category Monopoly Game
 * @package roll
 */
class Roll{

public:
    Roll(const int x, const int y){
        this->_X = x;
        this->_Y = y;
    };
    ~Roll(){this->clear();};


    const int cast() const;

private:
    int _X;
    int _Y;
    const int print(const int num) const;
    void clear() const;
    void anime() const;

};



#endif // __ROLL_H_