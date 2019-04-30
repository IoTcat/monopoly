
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package scoreboard
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#include "scoreboard.h"

#include <iomanip>


const int Scoreboard::print(Player& p) const
{
    
    Sleep(500);
    SetColor(this->_color);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "--------------------" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |                   |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |                   |" ;
    SetCursorPosition(this->_X + 1 + (10 - p.getName().length() / 2) / 2, this->_Y + 2);
    std::cout << p.getName();
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |                   |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 4);
    std::cout << " |                   |" ;
    SetCursorPosition(this->_X + 1 + 7 / 2, this->_Y + 4);
    std::cout << "$ " << setprecision(4) << p.getBalance() ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 5);
    std::cout << " |                   |" ;
    Sleep(100);

    return 1;
}