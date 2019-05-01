
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package startinterface
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __STRATINTERFACE_H_
#define __STARTINTERFACE_H_

#include <deque>
#include <vector>
#include "point.h"


/**
 * start interface
 *
 * @author github.com/silence1772, yimian
 * @category Monopoly Game
 * @package startinterface
 */
class StartInterface
{
public:
    StartInterface() : speed(25) {

        int p;

        startsnake.emplace_back(Point(0,14));///\/\/\/
        startsnake.emplace_back(Point(1,14));
        startsnake.emplace_back(Point(2,15));
        startsnake.emplace_back(Point(3,16));
        startsnake.emplace_back(Point(4,17));
        startsnake.emplace_back(Point(5,18));
        startsnake.emplace_back(Point(6,17));
        startsnake.emplace_back(Point(7,16));
        startsnake.emplace_back(Point(8,15));
        startsnake.emplace_back(Point(9,14));

        p = -27;
        textsnake.emplace_back(Point(p+8, 18));
        textsnake.emplace_back(Point(p+7, 16));
        textsnake.emplace_back(Point(p+6, 14));//M
        textsnake.emplace_back(Point(p+5, 15));
        textsnake.emplace_back(Point(p+4, 16));
        textsnake.emplace_back(Point(p+3, 15));
        textsnake.emplace_back(Point(p+2, 14));
        textsnake.emplace_back(Point(p+1, 16));
        textsnake.emplace_back(Point(p, 18));


        p = -18;
        textsnake.emplace_back(Point(p, 15));//O
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p+1, 18));
        textsnake.emplace_back(Point(p+1, 14));
        textsnake.emplace_back(Point(p+2, 18));
        textsnake.emplace_back(Point(p+2, 14));
        textsnake.emplace_back(Point(p+3, 15));
        textsnake.emplace_back(Point(p+3, 16));
        textsnake.emplace_back(Point(p+3, 17));

        p += 5;
        textsnake.emplace_back(Point(p, 14));//N
        textsnake.emplace_back(Point(p, 15));
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p, 18));
        textsnake.emplace_back(Point(p+1, 15));
        textsnake.emplace_back(Point(p+2, 16));
        textsnake.emplace_back(Point(p+3, 17));
        textsnake.emplace_back(Point(p+4, 14));
        textsnake.emplace_back(Point(p+4, 15));
        textsnake.emplace_back(Point(p+4, 16));
        textsnake.emplace_back(Point(p+4, 17));
        textsnake.emplace_back(Point(p+4, 18));


        p += 6;
        textsnake.emplace_back(Point(p, 15));//O
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p+1, 18));
        textsnake.emplace_back(Point(p+1, 14));
        textsnake.emplace_back(Point(p+2, 18));
        textsnake.emplace_back(Point(p+2, 14));
        textsnake.emplace_back(Point(p+3, 15));
        textsnake.emplace_back(Point(p+3, 16));
        textsnake.emplace_back(Point(p+3, 17));

        p += 5;
        textsnake.emplace_back(Point(p, 14));//P
        textsnake.emplace_back(Point(p, 15));
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p, 18));
        textsnake.emplace_back(Point(p+1, 16));
        textsnake.emplace_back(Point(p+1, 14));
        textsnake.emplace_back(Point(p+2, 16));
        textsnake.emplace_back(Point(p+2, 14));
        textsnake.emplace_back(Point(p+3, 15));

        p += 5;
        textsnake.emplace_back(Point(p, 15));//O
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p+1, 18));
        textsnake.emplace_back(Point(p+1, 14));
        textsnake.emplace_back(Point(p+2, 18));
        textsnake.emplace_back(Point(p+2, 14));
        textsnake.emplace_back(Point(p+3, 15));
        textsnake.emplace_back(Point(p+3, 16));
        textsnake.emplace_back(Point(p+3, 17));

        p+=5;
        textsnake.emplace_back(Point(p, 14));//L
        textsnake.emplace_back(Point(p, 15));
        textsnake.emplace_back(Point(p, 16));
        textsnake.emplace_back(Point(p, 17));
        textsnake.emplace_back(Point(p, 18));
        textsnake.emplace_back(Point(p+1, 18));
        textsnake.emplace_back(Point(p+2, 18));
        textsnake.emplace_back(Point(p+3, 18));


        p+=4;
        textsnake.emplace_back(Point(p, 14));//Y
        textsnake.emplace_back(Point(p+1, 15));
        textsnake.emplace_back(Point(p+2, 16));
        textsnake.emplace_back(Point(p+3, 15));
        textsnake.emplace_back(Point(p+4, 14));
        textsnake.emplace_back(Point(p+2, 17));
        textsnake.emplace_back(Point(p+2, 18));

    }

    void Action();
private:
    std::deque<Point> startsnake;//开始动画中的蛇
    std::vector<Point> textsnake;//开始动画中的文字
    int speed;//动画的速度

    void PrintFirst();
    void PrintSecond();
    void PrintThird();
    void PrintText();
    void ClearText();

};
#endif // __STRATINTERFACE_H_
