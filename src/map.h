
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package map
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */


#ifndef __MAP_H_
#define __MAP_H_

#include <vector>
#include <ctime>
#include <cstdlib>
#include "../lib/ovo.h"
#include "point.h"
#include "square.h"
#include "player.h"


/* default value for map shape */
const unsigned short g_mapLength = 13;
const unsigned short g_mapWidth = 7;


/**
 * map
 *
 * @author yimian
 * @category Monopoly Game
 * @package map
 */
class Map
{
public:
    /* constructor for Players */
    Map(Player& p1, Player& p2)
    {
        /* link to player */
        this->_p1 = p1.getName();
        this->_p2 = p2.getName();

        /* generate map id */
        srand(time(NULL) + p1.getName().length() * 1 + p2.getName().length() * 10);
        this->_id = m.md5(to_string(rand()).append(p1.getName()).append(p2.getName()));

        /* generate squares */
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


        /* link squares into ovo::data */
        for(int i = 0; i < 40; i ++){

            this->_d.insert(i, this->_map[i].getId());
        }

        /* set default params */
        this->_map[0].type = "GO";
        this->_map[20].type = "JAIL";
        this->_playerPos = 0;
        this->_aiPos = 0;

        /* save */
        this->save();
    }

    /* recover map with id */
    Map(const std::string& id){

        /* recover data */
        this->_d = db.getData(id);

        /* recover from data */
        this->_playerPos = atoi(this->_d["_map_playerPos"].c_str());
        this->_aiPos = atoi(this->_d["_map_aiPos"].c_str());
        this->_id = this->_d["_map_id"];
        this->_p1 = this->_d["_map_p1"];
        this->_p2 = this->_d["_map_p2"];

        /* recover squares */
        for(int i = 0; i < 40; i ++){

            this->_map.emplace_back(Square(this->_d[i]));
        }

        this->_d.clear();

        /* reset square data */
        for(int i = 0; i < 40; i ++){

            this->_d.insert(i, this->_map[i].getId());
        }
    };

    friend class Controller;

    /* print map */
    void PrintInitmap();
    /* player move */
    void move(const int& i, const Player& p);
    /* return position */
    inline const int getPos(const Player& p){
        if(p.type == "PLAYER") return this->_playerPos;
        else return this->_aiPos;
    };
    /* get map id */
    inline const std::string getId(){
        return this->_id;
    }

private:
    std::vector<Point> initmap;
    std::vector<Square> _map;
    std::string _id;
    unsigned int _playerPos;
    unsigned int _aiPos;
    std::string _p1, _p2;
    ovo::db db;
    ovo::data _d;
    const ovo::math m;

    /* player move */
    void player_move(int i);
    /* ai move */
    void ai_move(int i);
    /* save data */
    void save();

};

#endif //__MAP_H_
