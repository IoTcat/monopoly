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
    Controller() : speed(200), key(1), score(0), msgBox(9, 8, 11), hintBox(9, 22, 11), roll(40, 9) {
        msgBox.title("Message Box");
    }
    ~Controller(){
        delete p1, p2, map;
    };
    void Start();
    void Select();
    void DrawGame();
    int PlayGame();
    void UpdateScore();
    void RewriteScore();
    int Menu();
    void Game();
    void login();
    
private:
    int speed;
    int key;
    int score;
    Msgbox msgBox;
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
