
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package square
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __SQUARE_H_
#define __SQUARE_H_

#include <stdlib.h> 
#include <time.h>
#include <vector>
#include "point.h"
#include "player.h"
#include "../lib/ovo.h"

const unsigned short g_squareLength = 4;
const unsigned short g_squareWidth = 4; 

/**
 * square
 *
 * @author yimian
 * @category Monopoly Game
 * @package square
 */
class Square
{
public:
    Square(const int x, const int y)
    {
        srand(time(NULL) + x * 10 + y *1000);

        /* generate id */
        this->_id = m.md5(to_string(rand() * x * y));

        this->_X = x;
        this->_Y = y;
        this->_drawLines(x, y);

        this->_level = 0;
        
        this->_price = (rand() % (290 + 1)) + 10;

        this->type = "NORMAL";
        this->owner = " ";
        this->ownerType = " ";

        this->save();
    }

    Square(std::string id){

        this->_d = db.getData(id);

        this->_id = id;
        this->_X = atoi(this->_d["_square_X"].c_str());
        this->_Y = atoi(this->_d["_square_Y"].c_str());
        this->_level = atoi(this->_d["_square_level"].c_str());
        this->_price = atoi(this->_d["_square_price"].c_str());
        this->_drawLines(this->_X, this->_Y);

        this->type = this->_d["_square_type"];
        this->owner = this->_d["_square_owner"];
        this->ownerType = this->_d["_square_ownerType"];

    }

    std::string type;
    std::string owner;
    std::string ownerType;
    void draw_player() const;
    void draw_ai() const;
    void clear_player() const;
    void clear_ai() const;
    void print();
    void buy(Player& p);
    void save();
    inline const std::string getId() const{
        return this->_id;
    }

    inline const double getPrice() const{
        return (double)this->_price * (1 + this->_level * .05);
    };
    inline const unsigned short getLevel() const{
        return this->_level;
    };
    friend class Player;
    friend class Controller;
    inline const int levelup(){
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
    std::string _id;
    ovo::data _d;
    ovo::db db;
    ovo::math m;

    void _drawLines(const int x, const int y);


};


#endif