
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package hintbox
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#include "hintbox.h"


/**
 * print hint box
 *
 * @access public
 * @param string& msg
 * @return short
 */
const short Hintbox::print(const std::string& msg) const{

    Sleep(500);
    SetColor(this->_color);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "------------------------------------------" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - msg.length() / 2) / 2, this->_Y + 2);
    std::cout << msg ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X + 1, this->_Y + 4);
    std::cout << "------------------------------------------" ;
    Sleep(100);

    return 1;
}


/**
 * clear hint box
 *
 * @access public
 * @param void
 * @return void
 */
void Hintbox::clear() const{

    for(int i = this->_Y; i < this->_Y + 5; i++){

        SetCursorPosition(this->_X, i);
        std::cout << "                                           " ;
        Sleep(10);
    }
}