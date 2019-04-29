#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "msgbox.h"
#include "hintbox.h"
#include "roll.h"
#include "player.h"
#include "map.h"
#include "scoreboard.h"
#include "../lib/ovo.h"

class Controller
{
public:
    Controller() : speed(200), key(1), score(0), msgBox(9, 8, 11), switchBox(19, 8, 11), hintBox(9, 22, 11), roll(40, 9) {
        msgBox.title("Message Box");
    }
    ~Controller(){
        delete p1, p2, map;
    };
    void Start();
    int Select();
    void DrawGame();
    int PlayGame_pc();
    int PlayGame_pp();
    int PlayGame_cc();
    void UpdateScore();
    void RewriteScore();
    int Menu();
    void Game();
    void login_pc();
    void login_pp();
    void login_cc();
    int player_play(Player *pp1, Player *pp2);
    void ai_play(Player *pp2, Player *pp1);
    void getUsr(Player *&p);
    
private:
    int speed;
    int key;
    int score;
    Msgbox msgBox, switchBox;
    Hintbox hintBox;
    Roll roll;
    Player *p1, *p2;
    Map *map;
    Scoreboard *sb1, *sb2;
    ovo::db db;
    ovo::math m;
    ovo::data d_player;

};
#endif // CONTROLLER_H
