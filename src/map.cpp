
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package map
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */
#include "map.h"

#include <windows.h>
#include "tools.h"


/**
 * print ini map
 *
 * @access public
 * @param void
 * @return short
 */
void Map::PrintInitmap()
{
    SetColor(3);
    for (auto& square : this->_map)
    {
        square.print();
        Sleep(10);
    }

    this->_map[this->_playerPos].draw_player();
    this->_map[this->_aiPos].draw_ai();
}


/**
 * player move
 *
 * @access private
 * @param int i
 * @return void
 */
void Map::player_move(int i){


    for(int ii = 0; ii < i; ii++){

        Sleep(400);

        if((this->_playerPos + ii) >= 40) this->_map[this->_playerPos + ii - 40].clear_player();
        else this->_map[this->_playerPos + ii].clear_player();

        Sleep(400);

        if((this->_playerPos + ii + 1) >= 40) this->_map[this->_playerPos + ii + 1 - 40].draw_player();
        else this->_map[this->_playerPos + ii + 1].draw_player();
    }


    this->_playerPos += i;
    if(this->_playerPos >= 40) this->_playerPos -= 40;
    

    this->save();
}


/**
 * ai move
 *
 * @access private
 * @param int i
 * @return void
 */
void Map::ai_move(int i){

    for(int ii = 0; ii < i; ii++){

        Sleep(400);

        if((this->_aiPos + ii) >= 40) this->_map[this->_aiPos + ii - 40].clear_ai();
        else this->_map[this->_aiPos + ii].clear_ai();

        Sleep(400);

        if((this->_aiPos + ii + 1) >= 40) this->_map[this->_aiPos + ii + 1 - 40].draw_ai();
        else this->_map[this->_aiPos + ii + 1].draw_ai();
    }


    this->_aiPos += i;
    if(this->_aiPos >= 40) this->_aiPos -= 40;

    this->save();
}


/**
 * move player
 *
 * @access public
 * @param int& i
 * @param Player& p
 * @return void
 */
void Map::move(const int& i, const Player& p){

    if(p.type == "PLAYER")
        this->player_move(i);
    else if(p.type == "AI")
        this->ai_move(i);
}


/**
 * save data
 *
 * @access private
 * @param void
 * @return void
 */
void Map::save(){

    this->_d.insert("_map_playerPos", this->_playerPos);
    this->_d.insert("_map_aiPos", this->_aiPos);
    this->_d.insert("_map_p1", this->_p1);
    this->_d.insert("_map_p2", this->_p2);
    this->_d.insert("_map_id", this->_id);

    db.pushData(this->_d, this->_id);
}