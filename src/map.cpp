#include "map.h"
#include <windows.h>
#include "tools.h"

void Map::PrintInitmap()
{
    SetColor(3);
    for (auto& square : this->_map)
    {
        square.print();
        Sleep(10);
    }
}


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
    
}


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
}

