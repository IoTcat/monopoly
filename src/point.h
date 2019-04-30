
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package point
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */
#ifndef __POINT_H_
#define __POINT_H_

#include "tools.h"

/**
 * Point
 *
 * @author yimian
 * @category Monopoly Game
 * @package point
 */
class Point
{
public:
    Point(){};
    Point(const int x, const int y) : x(x), y(y) {};
    void Print();
    void PrintCircular();
    void PrintStar();
    void PrintRowLine();
    void PrintColumnLine();
    void PrintLeftLine();
    void PrintRightLine();
    void Clear();
    void ChangePosition(const int x, const int y);
    bool operator== (const Point& point) { return (point.x == this->x) && (point.y == this->y); }
    inline const int GetX() const{ return this->x; }
    inline const int GetY() const{ return this->y; }
    inline void red(){SetColor(13);}
    inline void yellow(){SetColor(14);}
    inline void darkBlue(){SetColor(3);}
    inline void lightBlue(){SetColor(11);}
private:
    int x, y;
};

#endif // __POINT_H_
