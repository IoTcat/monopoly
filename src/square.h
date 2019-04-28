#ifndef __SQUARE_H_
#define __SQUARE_H_

#include <stdlib.h> 
#include <time.h>
#include <vector>
#include "point.h"
#include "player.h"

const unsigned short g_squareLength = 4;
const unsigned short g_squareWidth = 4; 

enum squareType{NORMAL, GO, JAIL};


class Square
{
public:
    Square(int x, int y)//默认构造函数，绘制单元格外形
    {

        this->_X = x;
        this->_Y = y;
        this->_drawLines(x, y);

        this->_level = 0;
        
        this->_price = (rand() % (290 + 1)) + 10;

        this->type = NORMAL;
        this->owner = "";
        this->ownerType = "";
    }

    squareType type;
    std::string owner;
    std::string ownerType;
    void draw_player();
    void draw_ai();
    void clear_player();
    void clear_ai();
    void print();//绘制初始地图
    void buy(Player& p);

    inline double getPrice(){
        return (double)this->_price * (1 + this->_level * .05);
    };
    inline unsigned short getLevel(){
        return this->_level;
    };
    friend class Player;
    friend class Controller;
    inline int levelup(){
        this->_level += 1;
        this->print();
        return this->_level;
    }

private:
    std::vector<Point> _rowLines;//水平线
    std::vector<Point> _columnLines;//竖直线
    std::vector<Point> _leftLines;//左角线
    std::vector<Point> _rightLines;//右角线
    unsigned short _level;
    unsigned int _price;
    unsigned int _X;
    unsigned int _Y;

    void _drawLines(int x, int y);


};


#endif