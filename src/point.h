#ifndef POINT_H
#define POINT_H

#include "tools.h"

class Point
{
public:
    Point(){}
    Point(const int x, const int y) : x(x), y(y) {}
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
    int GetX(){ return this->x; }
    int GetY(){ return this->y; }
    void red(){SetColor(13);}
    void yellow(){SetColor(14);}
    void darkBlue(){SetColor(3);}
    void lightBlue(){SetColor(11);}
private:
    int x, y;
};
#endif // POINT_H
