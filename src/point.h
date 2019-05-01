
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
    void Print() const;
    void PrintCircular() const;
    void PrintStar() const;
    void PrintRowLine() const;
    void PrintColumnLine() const;
    void PrintLeftLine() const;
    void PrintRightLine() const;
    void Clear() const;
    void ChangePosition(const int x, const int y);
    bool operator== (const Point& point) { return (point.x == this->x) && (point.y == this->y); }
    inline const int GetX() const{ return this->x; }
    inline const int GetY() const{ return this->y; }
    inline void red() const{SetColor(13);}
    inline void yellow() const{SetColor(14);}
    inline void darkBlue() const{SetColor(3);}
    inline void lightBlue() const{SetColor(11);}
private:
    int x, y;
};

#endif // __POINT_H_
