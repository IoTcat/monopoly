
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package controller
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */



#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "msgbox.h"
#include "hintbox.h"
#include "roll.h"
#include "player.h"
#include "map.h"
#include "scoreboard.h"
#include "../lib/ovo.h"



/**
 * Game Controller
 *
 * @author yimian
 * @category Monopoly Game
 * @package controller
 */
class Controller
{
public:
    Controller() : key(1), msgBox(9, 8, 11), switchBox(19, 8, 11), hintBox(9, 22, 11), roll(40, 9) {
        /* set default msgBox title */
        msgBox.title("Message Box");
    }
    ~Controller(){
        /* distory all pointers */
        delete p1, p2, map, sb1, sb2;
    };

    /* create a game */
    void Game();
    
private:
    short key;
    Msgbox msgBox, switchBox;
    Hintbox hintBox;
    /* dice */
    Roll roll;
    Player *p1, *p2;
    Map *map;
    Scoreboard *sb1, *sb2;
    /* include methods from ovo.h */
    ovo::db db;
    const ovo::math m;
    ovo::data d_player;

private:

    /* Game start page */
    void Start() const;
    /* game menu area */
    const short Select();
    /* draw game page */
    const void DrawGame() const;
    /* play game for player-computer mode */
    const short PlayGame_pc();
    /* play game for player-player mode */
    const short PlayGame_pp();
    /* play game for computer-computer mode */
    const short PlayGame_cc();
    /* privide players options in game */
    const short player_play(Player *pp1, Player *pp2, short& ice);
    /* AI in game */
    const short ai_play(Player *pp2, Player *pp1, short& ice);
    /* update the info Board of players */
    void UpdateScore() const;
    /* login page/logic for player_computer mode */
    const short login_pc();
    /* login page/logic for player_player mode */
    const short login_pp();
    /* login page/logic for computer_computer mode */
    const short login_cc();
    /* get a user */
    const short getUsr(Player *&p);
    /* get input from keyboard */
    const short input(std::string& uName, const int& x, const int& y, const std::string star = "");
    /* print hint */
    void printHint() const;
    /* clear hint */
    void clearHint() const;

};


#endif // __CONTROLLER_H_
