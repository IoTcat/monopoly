
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package controller
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#include "controller.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include "tools.h"
#include "startinterface.h"


/**
 * Create a Game
 *
 * @access public
 * @param void
 * @return void
 */
void Controller::Game(){

    Start(); //Game Start
    while(true){

    int top = 0;

    /* Mode Select */
    int chs = Select();
        switch (chs){

        case 1:
            if(login_pp()) top = 1;

            break;
        case 2:
            if(login_pc()) top = 1;

            break;

        case 3:
            if(login_cc()) top = 1;

            break;

        case 4:
            return;

        default:
            return;
        }

        /* set rand seed */
        srand((unsigned)time(NULL));

        /* Game */
        while (!top)
        {
            /* draw game background */
            DrawGame();
            int tmp;
            /* play game by mode */
            if(chs == 1) tmp = PlayGame_pp();
            if(chs == 2) tmp = PlayGame_pc();
            if(chs == 3) tmp = PlayGame_cc();
            if (tmp == 1) //restart game
            {
                system("cls");
                map = new Map(*p1, *p2);

                p1->setMap(map->getId());
                p2->setMap(map->getId());
                continue;
            }
            else if (tmp == 2) //return to menu
            {

                SetColor(3);
                system("cls");
                break;
            }
            else
            {
                break;
            }
        }
    }
}


/**
 * Start Page
 *
 * @access private
 * @param void
 * @return void
 */
void Controller::Start() const{

    SetWindowSize(59, 35);
    SetColor(10);

    /* play anime */
    StartInterface *start = new StartInterface();
    start->Action();
    delete start;

    /* print hint */
    SetCursorPosition(23, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(23, 27);
    system("pause");
    SetCursorPosition(23, 26);
    std::cout << "                           " ;
    SetCursorPosition(23, 27);
    std::cout << "                           " ;
}


/**
 * select zone
 *
 * @access private
 * @param void
 * @return void
 */
const short Controller::Select(){

    /* print selections */
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetCursorPosition(6, 21);
    std::cout << "Please Select the Mode: " ;
    SetCursorPosition(6, 22);
    std::cout << "(Use Arrows to Select)" ;
    SetCursorPosition(27, 22);
    SetBackColor(); //seleted
    std::cout << "Player vs Player" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Player vs Computer" ;
    SetCursorPosition(27, 26);
    std::cout << "Computer vs Computer" ;
    SetCursorPosition(27, 28);
    std::cout << "Quit Game" ;
    SetCursorPosition(0, 31);

    /* select */
    int ch;
    key = 1; //record select position
    bool flag = false; //is pressed Enter
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 72: //up arrow
            if (key > 1) //not first item
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);
                    SetBackColor();
                    std::cout << "Player vs Player" ;

                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "Player vs Computer" ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Player vs Computer" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Computer vs Computer" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Computer vs Computer" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "Quit Game" ;

                    --key;
                    break;
                }
            }
            break;

        case 80: //down arrow
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Player vs Computer" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "Player vs Player" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Computer vs Computer" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "Player vs Computer" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "Quit Game" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Computer vs Computer" ;

                    ++key;
                    break;
                }
            }
            break;

        case 13: //Enter
            flag = true;
            break;
        default: //others
            break;
        }
        if (flag) break;

        SetCursorPosition(0, 31); //hide cursor
    }

    return key;
}


/**
 * draw game background
 *
 * @access private
 * @param void
 * @return void
 */
const void Controller::DrawGame() const{

    system("cls");

    /* print map */
    SetColor(3);
    map->PrintInitmap();

    /* print score board */
    this->sb1->print(*p1);
    this->sb2->print(*p2);
}


/**
 * play game p-c mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::PlayGame_pc(){

    short tmp;
    short ice_p1 = 0;
    short ice_p2 = 0;

    /* game */
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //if not bankrupt
    {
        if(this->player_play(p1, p2, ice_p1)) return 2;
        if(this->ai_play(p2, p1, ice_p2)) return 2;
    }


    /* player win */
    if(p1->getBalance() > 0){
        hintBox.color(10);
        hintBox.print("You WIN!!!");
        msgBox.title("Game Over");
        tmp = this->msgBox.print("You Win!!!", "Good Job!", "Play Again?", "OK", "Quit");
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//back to menu
        default:
            return 2;
        }
    }else{ //computer win
        hintBox.color(12);
        hintBox.print("You LOST!!!");
        msgBox.title("Game Over");
        tmp = this->msgBox.print("You LOST!!!", ">_<!", "Play Again?", "OK", "Quit");
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//quit game
        default:
            return 2;
        }
    }

}


/**
 * play game p-p mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::PlayGame_pp(){

    short tmp;
    short ice_p1 = 0;
    short ice_p2 = 0;

    /* game */
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //if not bankrupt
    {
        if(this->player_play(p1, p2, ice_p1)) return 2;
        if(this->player_play(p2, p1, ice_p2)) return 2;
    }


    if(p1->getBalance() > 0){ //p1 win
        std::string s = p1->getName();
        hintBox.color(14);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//back to menu
        default:
            return 2;
        }
    }else{ //p2 win
        std::string s = p2->getName();
        hintBox.color(13);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//to menu
        default:
            return 2;
        }
    }

}


/**
 * play game c-c mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::PlayGame_cc(){

    short tmp;
    short ice_p1 = 0;
    short ice_p2 = 0;

    /* game */
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //if not backrupt
    {
        if(this->ai_play(p1, p2, ice_p1)) return 2;
        if(this->ai_play(p2, p1, ice_p2)) return 2;
    }


    if(p1->getBalance() > 0){ //c1 win
        std::string s = p1->getName();
        hintBox.color(14);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//to menu
        default:
            return 2;
        }
    }else{
        std::string s = p2->getName();
        hintBox.color(13);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//restart
        case 2:
            return 2;//to menu
        default:
            return 2;
        }
    }

}


/**
 * player play
 *
 * @access private
 * @param Player pp1 #player 1
 * @param Player pp2 #player 2
 * @param short& ice #is ice
 * @return short
 */
const short Controller::player_play(Player *pp1, Player *pp2, short& ice){

    short tmp;

    /* get player 1's name */
    std::string name = pp1->getName();

    /* set color */
    if(pp1->type == "AI") hintBox.color(13);
    else hintBox.color(14);

    /* display name */
    hintBox.print("MONOPOLY::" + name);

    /* if not iced */
    if(!ice){

        /* cast */
        this->printHint();
        tmp = this->msgBox.print("Hi " + name + "~", "It is YOUR turn.", "Please Select:", "Cast", "Quit");
        if(tmp == 2) return 2;
        this->clearHint();

        /* move */
        tmp = this->roll.cast();
        this->printHint();
        Sleep(800);
        this->clearHint();
        if(kbhit() && getch() == 27) return 2; 
        this->map->move(tmp, *pp1);

        /* what happen */
        if(this->map->_map[map->getPos(*pp1)].type == "GO"){ //GO

            /* gain 200 */
            pp1->gain(200);
            tmp = this->msgBox.print("Hi " + name + "~", "You are into the GO zone..", "Gain $ 200 !!");
            if(tmp == 2) return 2;

            /* update info */
            this->UpdateScore();
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

        }else if(this->map->_map[map->getPos(*pp1)].type == "JAIL"){ //JAIL

            /* ice next round */
            ice = 1;

            /* print hint */
            this->msgBox.print("Hi " + name + "~", "You are into the JAIL zone..", "You need to wait for one round !!");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2;

        }else if(this->map->_map[map->getPos(*pp1)].ownerType == " "){ //unoccupied

            /* print hint */
            tmp = this->msgBox.print("Hi " + name + "~", "This square is unoccupied.", "Do you want to BUY it?", "Yes", "No");
            
            /* if have enough balance */
            if(tmp == 1 && this->map->_map[map->getPos(*pp1)].getPrice() < pp1->getBalance()){

                /* buy square */
                this->map->_map[map->getPos(*pp1)].owner = pp1->getName();
                this->map->_map[map->getPos(*pp1)].ownerType = pp1->type;
                pp1->cost(this->map->_map[this->map->getPos(*pp1)].getPrice());

                /* update info */
                this->map->_map[map->getPos(*pp1)].print();
                this->UpdateScore();

            }else if(tmp == 1){

                /* dont have enough money */
                tmp = this->msgBox.print("Hi " + name + "~", "This square is unoccupied.", "You don't have ENOUGH MONEY to buy it!!");
                if(tmp == 2) return 2;
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }

        }else if(this->map->_map[map->getPos(*pp1)].ownerType == pp1->type){//your square

            /* print hint */
            tmp = this->msgBox.print("Hi " + name + "~", "This square is occupied by you.", "Do you want to UPGRADE it?", "Yes", "No");
            
            /* upgrade it */
            if(tmp == 1 && this->map->_map[map->getPos(*pp1)]._price * .5 < pp1->getBalance()){
                this->map->_map[map->getPos(*pp1)].levelup();
                this->map->_map[map->getPos(*pp1)].print();
                pp1->cost(this->map->_map[map->getPos(*pp1)]._price * .5);

                /* update info */
                this->UpdateScore();
            }else if(tmp == 1){

                /* not have enough money */
                this->msgBox.print("Hi " + name + "~", "This square is occupied by you.", "You don't have ENOUGH MONEY to upgrade it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }

        }else if(this->map->_map[map->getPos(*pp1)].ownerType == pp2->type){//opponent's square

            /* calculate price */
            int t_price = this->map->_map[this->map->getPos(*pp1)].getPrice() * (double)(0.1 + ((this->map->_map[map->getPos(*pp1) - 1].ownerType == pp2->type || this->map->_map[map->getPos(*pp1) + 1].ownerType == pp2->type)?0.1 : 0));
            
            /* print hint */
            std::string t_s = "You need to PAY $ ";
            t_s += to_string(t_price);
            tmp = this->msgBox.print("Hi " + name + "~", "This square is occupied by " + pp2->getName() + ".", t_s);
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            /* fine process */
            pp1->cost(t_price);
            pp2->gain(t_price);

            /* update info */
            this->UpdateScore();
        }else{
            /* wait */
            this->printHint();
            Sleep(800);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }

    }else{
        /* end ice */
        ice = 0;
    }

    return 0;
}


/**
 * player play
 *
 * @access private
 * @param Player pp1 #player 1
 * @param Player pp2 #player 2
 * @param short& ice #is ice
 * @return short
 */
const short Controller::ai_play(Player *pp2, Player *pp1, short& ice){

    short tmp;

    /* get AI's name */
    std::string name = pp2->getName();

    /* set color */
    if(pp2->type == "AI") hintBox.color(13);
    else hintBox.color(14);

    /* print name */
    hintBox.print("MONOPOLY::" + name);

    if(!ice){ //not iced

        this->msgBox.print("Hi ~", "It is " + name + "'s turn.", "Please Wait..");
        this->printHint();
        Sleep(800);
        this->clearHint();
        if(kbhit() && getch() == 27) return 2; 
        tmp = this->roll.cast();
        this->printHint();
        Sleep(800);
        this->clearHint();
        if(kbhit() && getch() == 27) return 2; 
        map->move(tmp, *pp2);
        this->printHint();
        Sleep(300);
        this->clearHint();
        if(kbhit() && getch() == 27) return 2; 

        /* what happened */
        if(this->map->_map[map->getPos(*pp2)].type == "GO"){ //GO

            /* gain 200 */
            pp2->gain(200);
            this->msgBox.print("WOW ~", name + " into the GO zone..", "Gain $ 200 !!");

            /* update info */
            this->UpdateScore();
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

        }else if(this->map->_map[map->getPos(*pp2)].type == "JAIL"){ //JAIL

            /* set ice for next round */
            ice = 1;

            /* print hint */
            this->msgBox.print("AHA ...", name + " are into the JAIL zone..", "He need to wait for one round !!");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2;

        }else if(this->map->_map[map->getPos(*pp2)].ownerType == " "){ //unoccupied

            /* print hint */
            tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "What will he do?");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            /* AI to buy this square */
            if(this->map->_map[this->map->getPos(*pp2)].getPrice() < pp2->getBalance() && ((this->map->_map[this->map->getPos(*pp2)].getPrice() > 88) || rand()%50 < 30) && pp2->getBalance() > 1000){
                
                /* buy process */
                this->map->_map[map->getPos(*pp2)].owner = pp2->getName();
                this->map->_map[map->getPos(*pp2)].ownerType = pp2->type;
                pp2->cost(this->map->_map[this->map->getPos(*pp2)].getPrice());

                /* update info */
                this->map->_map[map->getPos(*pp2)].print();
                this->UpdateScore();
                
                /* print hint */
                tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "The " + name + " BOUGHT it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2;

            }else{ //not buy

                /* print hint */
                tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "The " + name + " do NOTHING!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2;

            }
        }else if(this->map->_map[map->getPos(*pp2)].ownerType == pp2->type){//your square

            /* print hint */
            tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "What will he do?");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            /* AI to upgrade this square */
            if(this->map->_map[map->getPos(*pp2)]._price * .5 < pp2->getBalance() && pp2->getBalance() > 800){

                /* square level up */
                this->map->_map[map->getPos(*pp2)].levelup();
                this->map->_map[map->getPos(*pp2)].print();
                pp2->cost(this->map->_map[map->getPos(*pp2)]._price * .5);

                /* update info */
                this->UpdateScore();

                /* print hint */
                tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "The " + name + " UPGRADE it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2;

            }else{ //not upgrade

                tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "The " + name + " do NOTHING!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }
        }else if(this->map->_map[map->getPos(*pp2)].ownerType == pp1->type){//oponent's square

            /* calculate fee */ 
            int t_price = this->map->_map[this->map->getPos(*pp2)].getPrice() * (double)(0.1 + ((this->map->_map[map->getPos(*pp2) - 1].ownerType == pp1->type || this->map->_map[map->getPos(*pp2) + 1].ownerType == pp1->type)?.1 : 0));
            
            /* print hint */
            std::string t_s = pp1->getName() + " GAIN $ ";
            t_s += to_string(t_price);
            tmp = this->msgBox.print("Xixi ^_^", name + " meet " + pp1->getName() + "'s square..", t_s);

            /* wait */
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            /* fine process */
            pp2->cost(t_price);
            pp1->gain(t_price);
            this->UpdateScore();

        }else{
            /* wait */
            this->printHint();
            Sleep(800);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }
    }else{
        /* end ice */
        ice = 0;
    }

    return 0;
}


/**
 * update score board
 *
 * @access private
 * @param void
 * @return void
 */
void Controller::UpdateScore() const{

    this->sb1->print(*p1);
    this->sb2->print(*p2);
}


/**
 * login for p-c mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::login_pc(){

    system("cls");

    /* set AI reconginzer */
    std::string s = "AI";

    /* get user player */
    if(this->getUsr(this->p1)) return 2;

    /* if account not exist */
    if(this->d_player["_isExist"] == "NO" || p1->getMap() == " "){

        /* create new ai */
        this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));

        /* create new map */
        map = new Map(*p1, *p2);

        /* relink players and map */
        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{

        /* recover map */
        map = new Map(p1->getMap());

        /* get old ai data */
        this->d_player.clear();
        this->d_player = db.getData(map->_p2);

        /* if old ai not exist */
        if(this->d_player["_isExist"] == "NO"){

            /* create new map */
            delete map;
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);

            /* relink players and map */
            p1->setMap(map->getId());
            p2->setMap(map->getId());

        /* if the player2 is not AI */
        }else if(map->_p2.substr(0,2) != "AI"){

            /* create new map */
            delete map;
            this->p1->reset();
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);

            /* relink map and players */
            p1->setMap(map->getId());
            p2->setMap(map->getId());

        }else{ //if player exist

            this->switchBox.title("Message Box");
            system("cls");
            short tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
            
            /* continue game */
            if(tmp == 1){

                /* recover another player's info */
                this->p2 = new Player(d_player);

                /* if old player bankrupt */
                if(p1->getBalance() == 0 || p2->getBalance() == 0){

                    /* distory map an create new */
                    delete map;
                    this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
                    map = new Map(*p1, *p2);
                    p1->reset();
                    p1->setMap(map->getId());
                    p2->setMap(map->getId());   
                }

            /* create new map */
            }else{
                delete map;
                this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
                map = new Map(*p1, *p2);
                p1->reset();
                p1->setMap(map->getId());
                p2->setMap(map->getId());   
            }
        }
    }

    /* set player role/position */
    this->p1->type = "PLAYER";
    this->p2->type = "AI";

    /* create score board */
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;
}


/**
 * login for p-p mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::login_pp(){

    system("cls");

    /* string for store players' state */
    std::string old1, old2;

    /* get player 1 */
    if(this->getUsr(this->p1)) return 2;

    /* recore player 1 */
    old1 = this->d_player["_isExist"];

    /* get player 2 */
    if(this->getUsr(this->p2)) return 2;

    /* recore player 2 */
    old2 = this->d_player["_isExist"];

    /* if two players are same */
    if(p1->getName() == p2->getName()){
        system("cls");
        switchBox.title("Message Box");
        switchBox.print("The Two Players are SAME!!", "Please ReLogin!!", "");
        Sleep(2000);
        system("cls");
        return 2;
    }

    /* if can not use old map */
    if(old1 == "NO" || old2 == "NO" || p1->getMap() != p2->getMap() || p1->getMap() == " " || p2->getMap() == " "){

        map = new Map(*p1, *p2);

        p1->reset();
        p2->reset();
        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{ // use old map
        map = new Map(p1->getMap());

        /* adjust player's position */
        if(map->_p1 != p1->getName()){

            Player *t_p;
            t_p = p1;
            p1 = p2;
            p2 = t_p;
        }

        this->switchBox.title("Message Box");
        system("cls");
        short tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
        
        /* if not use old map */
        if(tmp != 1 || p1->getBalance() == 0 || p2->getBalance() == 0){
            delete map;
            map = new Map(*p1, *p2);
            p1->reset();
            p2->reset();
        }

        p1->setMap(map->getId());
        p2->setMap(map->getId()); 
    }

    /* set player's role */
    this->p1->type = "PLAYER";
    this->p2->type = "AI";

    /* set score board */
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;
}


/**
 * login for c-c mode
 *
 * @access private
 * @param void
 * @return short
 */
const short Controller::login_cc(){

    system("cls");

    /* name for ai player 1 */
    std::string uName = "AI9di2s";

    /* get ai info */
    this->d_player = db.getData(uName);

    /* set AI identifer */
    std::string s = "AI";

    /* if not exist old AI*/
    if(this->d_player["_isExist"] == "NO"){

        /* register AI as player 1 */
        this->p1 = new Player(uName, uName, 5000);

        /* create ai player 2 */
        this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));

        /* create new map */
        map = new Map(*p1, *p2);

        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{
        /* recover old ai */
        this->p1 = new Player(this->d_player);
        map = new Map(p1->getMap());

        /* get old ai 2 */
        this->d_player.clear();
        this->d_player = db.getData(map->_p2);

        /* if old ai 2 not exist */
        if(this->d_player["_isExist"] == "NO"){

            /* create new map */
            delete map;
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);

            p1->setMap(map->getId());
            p2->setMap(map->getId());
        }else{ // old ai 2 exist

            this->switchBox.title("Message Box");
            system("cls");
            short tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
            
            /* usr choose to continue */
            if(tmp == 1){

                /* recover ai 2 */
                this->p2 = new Player(d_player);

                /* if one ai bankrupt */
                if(p1->getBalance() == 0 || p2->getBalance() == 0){

                    /* new map */
                    delete map;
                    this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
                    map = new Map(*p1, *p2);
                    p1->reset();
                    p1->setMap(map->getId());
                    p2->setMap(map->getId());   
                }

            }else{

                /* create new map */
                delete map;
                this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
                map = new Map(*p1, *p2);
                this->p1->reset();
                p1->setMap(map->getId());
                p2->setMap(map->getId());   
            }
        }
    }

    /* set role for players */
    this->p1->type = "PLAYER";
    this->p2->type = "AI";

    /* create socre board */
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;
}


/**
 * get user as player
 *
 * @access private
 * @param Player *&p
 * @return short
 */
const short Controller::getUsr(Player *&p){

    switchBox.title("Login ^_^");
    switchBox.print("","","");
    SetCursorPosition(26, 19);
    std::cout << "Press ESC to quit!!";
    SetCursorPosition(23, 12);
    std::string uName, uPasswd;
    std::cout << "Your Name = ";

    /* get name input */
    while(true){

        if(input(uName, 23 + 6, 12)) return 2;
        if(uName.length() != 0) break;
        SetCursorPosition(26, 9);
        std::cout << "You Input NOTHING!!! " ;
    }

    /* get user data */
    this->d_player = db.getData(uName);

    /* if data not exist */
    if(this->d_player["_isExist"] == "NO"){
        SetCursorPosition(26, 9);
        std::cout << "Hi~ New Visitor! " ;

        /* set password */
        while(true){
            SetCursorPosition(23, 15);
            std::cout << "Set your Password =            ";
            std::string s1, s2;

            if(input(s1, 23 + 10, 15, "*")) return 2;

            SetCursorPosition(23, 15);
            std::cout << " REType Password  =            ";

            if(input(s2, 23 + 10, 15, "*")) return 2;

            if(s1 == s2 && s1.length() != 0){
                uPasswd = s1;
                break;
            }else if(s1.length() == 0){
                SetCursorPosition(23, 9);
                std::cout << "    You input NOTHING!!      " ;
            }else{
                SetCursorPosition(23, 9);
                std::cout << "Two Passwords are NOT SAME!!" ;
            }
            s1 = "";
            s2 = "";
        }

        p = new Player(uName, uPasswd);
        return 0;
    }

    /* recover user */
    p = new Player(this->d_player);

    /* check password */
    while(true){
        SetCursorPosition(23, 15);
        std::cout << "Input Password =           ";

        if(input(uPasswd, 23 + 9, 15, "*")) return 2;

        if(p->checkPasswd(uPasswd)){
            break;
        }
        SetCursorPosition(25, 9);
        std::cout << "Password is WRONG!!" ;
        uPasswd = "";
    }
    return 0;
}


/**
 * get user as player
 *
 * @access private
 * @param string& uName #string to store input
 * @param int x #position x
 * @param int y #position y
 * @param string star #filler for password
 * @return short
 */
const short Controller::input(std::string& uName, const int& x, const int& y, const std::string star){

    char tmp;
    fflush(stdin);

    /* get input untill Enter */
    while((tmp = _getch()) && tmp != 13){
        std::stringstream ss;
        ss << tmp;

        /* push input to string */
        if(tmp >= 33 && tmp <= 126 && uName.length() < 8) uName.append(ss.str());

        /* backspace */
        if(tmp == 8) uName = uName.substr(0, uName.length() - 1);

        /* print string */
        SetCursorPosition(x,y);
        if(star == "") std::cout << uName << "        ";
        else{
            for(int i = 0; i < uName.length(); i ++){
                std::cout << star;
            }
            std::cout << "        ";
        }

        /* set cursor position */
        SetCursorPosition(x + uName.length() / 2, y);
        if(tmp == 27) {
            system("cls");
            return 2;
        }

        fflush(stdin);
    }

    /* set cursor to default position */
    SetCursorPosition(0, 31);

    return 0;
}


/**
 * print hint
 *
 * @access private
 * @param void
 * @return void
 */
void Controller::printHint() const{

    SetColor(10);
    SetCursorPosition(33, 15);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;
    Sleep(10);
    SetCursorPosition(38, 17);
    std::cout << "Press ESC to Quit!!" ;
    Sleep(10);
    SetCursorPosition(33, 19);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;
}


/**
 * clear hint
 *
 * @access private
 * @param void
 * @return void
 */
void Controller::clearHint() const{

    SetColor(10);
    SetCursorPosition(33, 15);
    std::cout << "                                       " ;
    Sleep(10);
    SetCursorPosition(38, 17);
    std::cout << "                    " ;
    Sleep(10);
    SetCursorPosition(33, 19);
    std::cout << "                                       " ;
}