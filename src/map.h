#ifndef MAP_H
#define MAP_H

#include <vector>
#include "point.h"
#include "square.h"

const unsigned short g_mapLength = 13;
const unsigned short g_mapWidth = 7;


class Map
{
public:
    Map()//默认构造函数，将正方形各点压入initmap
    {
        for(int i = 0; i < g_mapLength; i ++){

            this->_map.emplace_back(Square(1 + g_squareLength * i, 1));
        }

        for(int i = 0; i < g_mapWidth; i ++){

            this->_map.emplace_back(Square(1 + g_squareLength * g_mapLength, 1 + i * g_squareWidth));
        }
        
        for(int i = g_mapLength; i > 0; i --){

            this->_map.emplace_back(Square(1 + g_squareLength * i, 1 + g_squareLength * g_mapWidth));
        }

        for(int i = g_mapWidth; i > 0; i --){

            this->_map.emplace_back(Square(1, 1 + i * g_squareWidth));
        }

        this->_map[0].type = GO;
        this->_map[20].type = JAIL;
        this->_playerPos = 0;
        this->_aiPos = 0;

        player_move(2);
        ai_move(3);

        this->_map[15].player_buy();
        this->_map[35].ai_buy();

    }
    void PrintInitmap();//绘制初始地图
    void player_move(int i);
    void ai_move(int i);
private:
    std::vector<Point> initmap;//保存初始地图
    std::vector<Square> _map;
    unsigned int _playerPos;
    unsigned int _aiPos;
    void _draw_player(int pos);
    void _draw_ai(int pos);
    void _remove_player(int pos);
    void _remove_ai(int pos);

};
#endif // MAP_H
