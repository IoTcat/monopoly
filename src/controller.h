#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "msgbox.h"
#include "hintbox.h"
#include "roll.h"

class Controller
{
public:
    Controller() : speed(200), key(1), score(0), msgBox(9, 8, 11), hintBox(9, 22, 11), roll(35, 9) {}
    void Start();
    void Select();
    void DrawGame();
    int PlayGame();
    void UpdateScore(const int&);
    void RewriteScore();
    int Menu();
    void Game();
    
private:
    int speed;
    int key;
    int score;
    Msgbox msgBox;
    Hintbox hintBox;
    Roll roll;
};
#endif // CONTROLLER_H
