#ifndef MAP_H
#define MAP_H

#include <vector>
#include "point.h"
#include "square.h"
#include "../lib/ovo.h"
#include "player.h"
#include <ctime>
#include <cstdlib>


const unsigned short g_mapLength = 13;
const unsigned short g_mapWidth = 7;


class Map
{
public:
    Map(Player& p1, Player& p2)//默认构造函数，将正方形各点压入initmap
    {
        this->_p1 = p1.getName();
        this->_p2 = p2.getName();

        srand(time(NULL) + p1.getName().length() * 1 + p2.getName().length() * 10);
        this->_id = m.md5(to_string(rand()).append(p1.getName()).append(p2.getName()));

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

        for(int i = 0; i < 40; i ++){

            this->_d.insert(i, this->_map[i].getId());
        }

        this->_map[0].type = "GO";
        this->_map[20].type = "JAIL";
        this->_playerPos = 0;
        this->_aiPos = 0;

        this->save();

    }

    Map(std::string id){

        this->_d = db.getData(id);

        this->_playerPos = atoi(this->_d["_map_playerPos"].c_str());
        this->_aiPos = atoi(this->_d["_map_aiPos"].c_str());
        this->_id = this->_d["_map_id"];
        this->_p1 = this->_d["_map_p1"];
        this->_p2 = this->_d["_map_p2"];

        for(int i = 0; i < 40; i ++){

            this->_map.emplace_back(Square(this->_d[i]));
        }

        this->_d.clear();

        for(int i = 0; i < 40; i ++){

            this->_d.insert(i, this->_map[i].getId());
        }

    };

    void PrintInitmap();//绘制初始地图
    void save();
    void move(int i, Player& p);
    int getPos(Player& p){
        if(p.type == "PLAYER") return this->_playerPos;
        else return this->_aiPos;
    };
    inline std::string getId(){
        return this->_id;
    }
    friend class Controller;
private:
    std::vector<Point> initmap;//保存初始地图
    std::vector<Square> _map;
    std::string _id;
    unsigned int _playerPos;
    unsigned int _aiPos;
    std::string _p1, _p2;
    ovo::db db;
    ovo::data _d;
    ovo::math m;

    void player_move(int i);
    void ai_move(int i);

};
#endif // MAP_H
