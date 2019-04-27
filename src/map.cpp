#include "map.h"
#include <windows.h>
#include "tools.h"

void Map::PrintInitmap()//绘制初始地图
{
    SetColor(3);
    for (auto& square : this->_map)
    {
        square.print();
        Sleep(10);//调用Sleep函数可营造动画效果
    }
}


void Map::player_move(int i){

    this->_map[this->_playerPos].clear_player();
    this->_playerPos += i;
    if(this->_playerPos >= 40) this->_playerPos -= 40;
    this->_map[this->_playerPos].draw_player();
}


void Map::ai_move(int i){

    this->_map[this->_aiPos].clear_ai();
    this->_aiPos += i;
    if(this->_playerPos >= 40) this->_playerPos -= 40;
    this->_map[this->_aiPos].draw_ai();
}

