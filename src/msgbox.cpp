
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package msgbox
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */
#include "msgbox.h"

/**
 * print message
 *
 * @access publice
 * @param string& msg1
 * @param string& msg2
 * @param string& msg3
 * @param string& ch1
 * @param string& ch2
 * @return short
 */
const short Msgbox::print(const std::string& msg1, const std::string& msg2, const std::string& msg3, const std::string& ch1, const std::string& ch2) const
{

    Sleep(500);
    SetColor(this->_color);
    SetCursorPosition(this->_X + 1, this->_Y); /* 9,8 */
    std::cout << "------------------------------------------" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 1);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - this->_title.length() / 2) / 2, this->_Y + 1);
    std::cout << this->_title ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 2);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 3);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - msg1.length() / 2) / 2, this->_Y + 3);
    std::cout << msg1 ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 4);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 5);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - msg2.length() / 2) / 2, this->_Y + 5);
    std::cout << msg2 ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 6);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 7);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 1 + (21 - msg3.length() / 2) / 2, this->_Y + 7);
    std::cout << msg3 ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 8);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 9);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 10);
    std::cout << " |                                          |" ;
    SetCursorPosition(this->_X + 5, this->_Y + 10);
    std::cout << ch1 ;
    SetCursorPosition(this->_X + 15, this->_Y + 10);
    std::cout << ch2 ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 11);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X, this->_Y + 12);
    std::cout << " |                                          |" ;
    Sleep(30);
    SetCursorPosition(this->_X + 1, this->_Y + 13);
    std::cout << "------------------------------------------" ;

    Sleep(100);
    SetCursorPosition(this->_X + 5, this->_Y + 10);
    SetBackColor();
    std::cout << ch1 ;
    SetCursorPosition(0, 31);

    /* select part */
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while(kbhit()) getch(); //clear cache
    while (ch1.length() && (ch = getch()))
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(this->_X + 5, this->_Y + 10);
                SetBackColor();
                std::cout << ch1 ;
                SetCursorPosition(this->_X + 15, this->_Y + 10);
                SetColor(this->_color);
                std::cout << ch2 ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(this->_X + 15, this->_Y + 10);
                SetBackColor();
                std::cout << ch2 ;
                SetCursorPosition(this->_X + 5, this->_Y + 10);
                SetColor(this->_color);
                std::cout << ch1 ;
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;
        case 27:
            return 2;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(this->_color);
    switch (tmp_key)
    {
    case 1:
        return 1;//choose 1
    case 2:
        return 2;//choose 2
    default:
        return 0;
    }
}

/**
 * clear msgbox
 *
 * @access publice
 * @param void
 * @return void
 */
void Msgbox::clear() const{

    for(int i = this->_Y; i < this->_Y + 13; i++){

        SetCursorPosition(this->_X, i);
        std::cout << "                                           " ;
        Sleep(10);
    }
}