#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "snake.h"
#include "food.h"


void Controller::Start()//开始界面
{
    SetWindowSize(59, 35);//设置窗口大小
    SetColor(10);//设置开始动画颜色
    StartInterface *start = new StartInterface();//动态分配一个StartInterface类start
    start->Action();//开始动画
    delete start;//释放内存空间

    /*设置关标位置，并输出提示语，等待任意键输入结束*/
    SetCursorPosition(23, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(23, 27);
    system("pause");
    SetCursorPosition(23, 26);
    std::cout << "                           " ;
    SetCursorPosition(23, 27);
    std::cout << "                           " ;
}

int Controller::Select()//选择界面
{
    /*初始化界面选项*/
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
    SetBackColor();//第一个选项设置背景色以表示当前选中
    std::cout << "Player vs Player" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Player vs Computer" ;
    SetCursorPosition(27, 26);
    std::cout << "Computer vs Computer" ;
    SetCursorPosition(27, 28);
    std::cout << "Quit Game" ;
    SetCursorPosition(0, 31);
    score = 0;

    /*上下方向键选择模块*/
    int ch;//记录键入值
    key = 1;//记录选中项，初始选择第一个
    bool flag = false;//记录是否键入Enter键标记，初始置为否
    while ((ch = getch()))
    {
        switch (ch)//检测输入键
        {
        case 72://UP上方向键
            if (key > 1)//当此时选中项为第一项时，UP上方向键无效
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//给待选中项设置背景色
                    SetBackColor();
                    std::cout << "Player vs Player" ;

                    SetCursorPosition(27, 24);//将已选中项取消我背景色
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

        case 80://DOWN下方向键
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

        case 13://Enter回车键
            flag = true;
            break;
        default://无效按键
            break;
        }
        if (flag) break;//输入Enter回车键确认，退出检查输入循环

        SetCursorPosition(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
    }

    return key;
}

void Controller::DrawGame()//绘制游戏界面
{
    system("cls");//清屏

    /*绘制地图*/
    SetColor(3);

    map->PrintInitmap();


    this->sb1->print(*p1);
    this->sb2->print(*p2);

}

int Controller::PlayGame_pc()//游戏二级循环
{
    /*初始化蛇和食物*/

    srand((unsigned)time(NULL));//设置随机数种子，如果没有 食物的出现位置将会固定
    int tmp;

    /*游戏循环*/
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //判断是否撞墙或撞到自身，即是否还有生命
    {
        if(this->player_play(p1, p2)) return 2;

        if(this->ai_play(p2, p1)) return 2;
    }


    if(p1->getBalance() > 0){ //玩家赢
        hintBox.color(10);
        hintBox.print("You WIN!!!");
        msgBox.title("Game Over");
        tmp = this->msgBox.print("You Win!!!", "Good Job!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }else{
        hintBox.color(12);
        hintBox.print("You LOST!!!");
        msgBox.title("Game Over");
        tmp = this->msgBox.print("You LOST!!!", ">_<!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }

}



int Controller::PlayGame_pp()//游戏二级循环
{
    /*初始化蛇和食物*/

    srand((unsigned)time(NULL));//设置随机数种子，如果没有 食物的出现位置将会固定
    int tmp;

    /*游戏循环*/
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //判断是否撞墙或撞到自身，即是否还有生命
    {
        if(this->player_play(p1, p2)) return 2;

        if(this->player_play(p2, p1)) return 2;
    }


    if(p1->getBalance() > 0){ //玩家赢
        std::string s = p1->getName();
        hintBox.color(14);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }else{
        std::string s = p2->getName();
        hintBox.color(13);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }

}

int Controller::PlayGame_cc()//游戏二级循环
{
    /*初始化蛇和食物*/

    srand((unsigned)time(NULL));//设置随机数种子，如果没有 食物的出现位置将会固定
    int tmp;

    /*游戏循环*/
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //判断是否撞墙或撞到自身，即是否还有生命
    {
        if(this->ai_play(p1, p2)) return 2;
        if(this->ai_play(p2, p1)) return 2;
    }


    if(p1->getBalance() > 0){ //玩家赢
        std::string s = p1->getName();
        hintBox.color(14);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }else{
        std::string s = p2->getName();
        hintBox.color(13);
        hintBox.print(s.append(" WIN!!!"));
        msgBox.title("Game Over");
        tmp = this->msgBox.print(s, "Good Job!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
        delete map;
        p1->reset();
        p2->reset();
        switch (tmp){
        case 1:
            return 1;//重新开始
        case 2:
            return 2;//退出游戏
        default:
            return 2;
        }
    }

}

int Controller::player_play(Player *pp1, Player *pp2){

    static int ice = 0;
    int tmp;
    std::string name = pp1->getName();
    if(pp1->type == "AI") hintBox.color(13);
    else hintBox.color(14);
    hintBox.print("MONOPOLY::" + name);
    if(!ice){
        this->printHint();
        tmp = this->msgBox.print("Hi " + name + "~", "It is YOUR turn.", "Please Select:", "Cast", "Quit");
        if(tmp == 2) return 2;
        this->clearHint();

        tmp = this->roll.cast();
        this->printHint();
        Sleep(800);
        this->clearHint();
        if(kbhit() && getch() == 27) return 2; 
        this->map->move(tmp, *pp1);

        //this->hintBox.print(to_string(this->map->_map[this->map->_playerPos].getPrice()));

        //GO
        if(this->map->_map[map->getPos(*pp1)].type == "GO"){

            pp1->gain(200);
            tmp = this->msgBox.print("Hi " + name + "~", "You are into the GO zone..", "Gain $ 200 !!");
            if(tmp == 2) return 2;

            this->UpdateScore();
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }else if(this->map->_map[map->getPos(*pp1)].type == "JAIL"){ //JAIL
            ice = 1;
            this->msgBox.print("Hi " + name + "~", "You are into the JAIL zone..", "You need to wait for one round !!");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }else if(this->map->_map[map->getPos(*pp1)].ownerType == " "){ //无人领地
            tmp = this->msgBox.print("Hi " + name + "~", "This square is unoccupied.", "Do you want to BUY it?", "Yes", "No");
            if(tmp == 1 && this->map->_map[map->getPos(*pp1)].getPrice() < pp1->getBalance()){
                this->map->_map[map->getPos(*pp1)].owner = pp1->getName();
                this->map->_map[map->getPos(*pp1)].ownerType = pp1->type;
                pp1->cost(this->map->_map[this->map->getPos(*pp1)].getPrice());
                this->map->_map[map->getPos(*pp1)].print();

                this->UpdateScore();
            }else if(tmp == 1){
                tmp = this->msgBox.print("Hi " + name + "~", "This square is unoccupied.", "You don't have ENOUGH MONEY to buy it!!");
                if(tmp == 2) return 2;
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }

        }else if(this->map->_map[map->getPos(*pp1)].ownerType == pp1->type){//玩家地盘
            tmp = this->msgBox.print("Hi " + name + "~", "This square is occupied by you.", "Do you want to UPGRADE it?", "Yes", "No");
            if(tmp == 1 && this->map->_map[map->getPos(*pp1)]._price * .5 < pp1->getBalance()){
                this->map->_map[map->getPos(*pp1)].levelup();
                this->map->_map[map->getPos(*pp1)].print();
                pp1->cost(this->map->_map[map->getPos(*pp1)]._price * .5);

                this->UpdateScore();
            }else if(tmp == 1){

                this->msgBox.print("Hi " + name + "~", "This square is occupied by you.", "You don't have ENOUGH MONEY to upgrade it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }
        }else if(this->map->_map[map->getPos(*pp1)].ownerType == pp2->type){//ai地盘

            int t_price = this->map->_map[this->map->getPos(*pp1)].getPrice() * (1 + (this->map->_map[map->getPos(*pp1) - 1].ownerType == pp2->type || this->map->_map[map->getPos(*pp1) + 1].ownerType == pp2->type)?.1 : 0);
            std::string t_s = "You need to PAY $ ";
            t_s += to_string(t_price);
            tmp = this->msgBox.print("Hi " + name + "~", "This square is occupied by COMPUTER.", t_s);
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            pp1->cost(t_price);
            pp2->gain(t_price);

            this->UpdateScore();
        }else{
            this->printHint();
            Sleep(800);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }

    }else{
        ice = 0;
    }

    return 0;

}


int Controller::ai_play(Player *pp2, Player *pp1){

    static int ice = 0;
    int tmp;
    std::string name = pp2->getName();
    if(pp2->type == "AI") hintBox.color(13);
    else hintBox.color(14);
    hintBox.print("MONOPOLY::" + name);
    if(!ice){

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
        //GO
        if(this->map->_map[map->getPos(*pp2)].type == "GO"){

            pp2->gain(200);
            this->msgBox.print("WOW ~", name + " into the GO zone..", "Gain $ 200 !!");
            this->UpdateScore();
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }else if(this->map->_map[map->getPos(*pp2)].type == "JAIL"){ //JAIL
            ice = 1;
            this->msgBox.print("AHA ...", name + " are into the JAIL zone..", "He need to wait for one round !!");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }else if(this->map->_map[map->getPos(*pp2)].ownerType == " "){ //无人领地

            tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "What will he do?");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
            tmp = rand() % 6;
            if(this->map->_map[this->map->getPos(*pp2)].getPrice() < pp2->getBalance() && ((this->map->_map[this->map->getPos(*pp2)].getPrice() > 88) || rand()%50 < 30) && pp2->getBalance() > 1000){
                this->map->_map[map->getPos(*pp2)].owner = pp2->getName();
                this->map->_map[map->getPos(*pp2)].ownerType = pp2->type;
                pp2->cost(this->map->_map[this->map->getPos(*pp2)].getPrice());
                this->map->_map[map->getPos(*pp2)].print();
                this->UpdateScore();
                
                tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "The " + name + " BOUGHT it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }else{
                tmp = this->msgBox.print("Lala..", name + " Find a unoccupied space.", "The " + name + " do NOTHING!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }
        }else if(this->map->_map[map->getPos(*pp2)].ownerType == pp2->type){//玩家地盘

            tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "What will he do?");
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
            tmp = rand()%6;
            if(this->map->_map[map->getPos(*pp2)]._price * .5 < pp2->getBalance() && pp2->getBalance() > 800){
                this->map->_map[map->getPos(*pp2)].levelup();
                this->map->_map[map->getPos(*pp2)].print();
                pp2->cost(this->map->_map[map->getPos(*pp2)]._price * .5);
                this->UpdateScore();
                tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "The " + name + " UPGRADE it!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }else{
                tmp = this->msgBox.print("Ahm..", name + " meet his own square.", "The " + name + " do NOTHING!!");
                this->printHint();
                Sleep(1500);
                this->clearHint();
                if(kbhit() && getch() == 27) return 2; 
            }
        }else if(this->map->_map[map->getPos(*pp2)].ownerType == pp1->type){//ai地盘

            int t_price = this->map->_map[this->map->getPos(*pp2)].getPrice() * (1 + (this->map->_map[map->getPos(*pp2) - 1].ownerType == pp1->type || this->map->_map[map->getPos(*pp2) + 1].ownerType == pp1->type)?.1 : 0);
            std::string t_s = pp1->getName() + " GAIN $ ";
            t_s += to_string(t_price);
            tmp = this->msgBox.print("Xixi ^_^", name + " meet " + pp1->getName() + "'s square..", t_s);
            this->printHint();
            Sleep(1500);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 

            pp2->cost(t_price);
            pp1->gain(t_price);
            this->UpdateScore();
        }else{
            this->printHint();
            Sleep(800);
            this->clearHint();
            if(kbhit() && getch() == 27) return 2; 
        }


    }else{
        ice = 0;
    }

    return 0;


}



void Controller::UpdateScore()//更新分数
{
    this->sb1->print(*p1);
    this->sb2->print(*p2);
}

void Controller::RewriteScore()//重绘分数
{
    /*为保持分数尾部对齐，将最大分数设置为6位，计算当前分数位数，将剩余位数用空格补全，再输出分数*/
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " " ;
    }
    std::cout << score ;
}

int Controller::Menu()//选择菜单
{
    /*绘制菜单*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "Menu: " ;
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << " Continue" ;
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "Play Again" ;
    Sleep(100);
    SetCursorPosition(34, 25);
    std::cout << "  Quit" ;
    SetCursorPosition(0, 31);

    /*选择部分*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = getch()))
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << " Continue" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "Play Again" ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "Play Again" ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "  Quit" ;

                    --tmp_key;
                    break;
                }
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "Play Again" ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << " Continue" ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "  Quit" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "Play Again" ;

                    ++tmp_key;
                    break;
                }
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //选择继续游戏，则将菜单擦除
    {
        SetCursorPosition(32, 19);
        std::cout << "      " ;
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//游戏一级循环
{
    Start();//开始界面

    while(1){

    int top = 0;

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
        srand(time(NULL));


        while (!top)//游戏可视为一个死循环，直到退出游戏时循环结束
        {

            DrawGame();//绘制游戏界面
            int tmp;
            if(chs == 1) tmp = PlayGame_pp();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
            if(chs == 2) tmp = PlayGame_pc();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
            if(chs == 3) tmp = PlayGame_cc();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
            if (tmp == 1) //返回值为1时重新开始游戏
            {
                system("cls");
                map = new Map(*p1, *p2);

                p1->setMap(map->getId());
                p2->setMap(map->getId());
                continue;
            }
            else if (tmp == 2) //返回值为2时退出游戏
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


int Controller::login_pc(){


    system("cls");

    srand((unsigned)time(NULL)+55);//设置随机数种子，如果没有 食物的出现位置将会固定
    std::string s = "AI";
    if(this->getUsr(this->p1)) return 2;

    if(this->d_player["_isExist"] == "NO" || p1->getMap() == " "){

        this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
        map = new Map(*p1, *p2);

        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{

        map = new Map(p1->getMap());

        this->d_player.clear();
        this->d_player = db.getData(map->_p2);

        if(this->d_player["_isExist"] == "NO"){
            delete map;
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);
            p1->setMap(map->getId());
            p2->setMap(map->getId());
        }else if(map->_p2.substr(0,2) != "AI"){
            delete map;
            this->p1->reset();
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);

            p1->setMap(map->getId());
            p2->setMap(map->getId());   
        }else{
            this->switchBox.title("Message Box");
            system("cls");
            int tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
            if(tmp == 1){
                this->p2 = new Player(d_player);
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

    this->p1->type = "PLAYER";
    this->p2->type = "AI";
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;
}

int Controller::login_pp(){


    system("cls");
    std::string old1, old2;
    /* 创建两个玩家 */
    if(this->getUsr(this->p1)) return 2;

    srand((unsigned)time(NULL)+55);

    old1 = this->d_player["_isExist"];

    if(this->getUsr(this->p2)) return 2;

    old2 = this->d_player["_isExist"];

    if(old1 == "NO" || old2 == "NO" || p1->getMap() != p2->getMap() || p1->getMap() == " " || p2->getMap() == " "){

        map = new Map(*p1, *p2);

        p1->reset();
        p2->reset();
        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{
        map = new Map(p1->getMap());

        if(map->_p1 != p1->getName()){

            Player *t_p;
            t_p = p1;
            p1 = p2;
            p2 = t_p;
        }

        this->switchBox.title("Message Box");
        system("cls");
        int tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
        if(tmp != 1){
            delete map;
            map = new Map(*p1, *p2);
            p1->reset();
            p2->reset();
        }

        p1->setMap(map->getId());
        p2->setMap(map->getId()); 
    }

    this->p1->type = "PLAYER";
    this->p2->type = "AI";
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;
}

int Controller::login_cc(){


    system("cls");
    std::string uName = "AI9di2s";
    this->d_player = db.getData(uName);

    srand((unsigned)time(NULL)+55);//设置随机数种子，如果没有 食物的出现位置将会固定
    std::string s = "AI";

    if(this->d_player["_isExist"] == "NO"){

        this->p1 = new Player(uName, uName, 5000);
        this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
        map = new Map(*p1, *p2);

        p1->setMap(map->getId());
        p2->setMap(map->getId());

    }else{
        this->p1 = new Player(this->d_player);
        map = new Map(p1->getMap());

        this->d_player.clear();
        this->d_player = db.getData(map->_p2);

        if(this->d_player["_isExist"] == "NO"){
            delete map;
            this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
            map = new Map(*p1, *p2);

            p1->setMap(map->getId());
            p2->setMap(map->getId());
        }else{
            this->switchBox.title("Message Box");
            system("cls");
            int tmp = this->switchBox.print("Detected Unfinished Game!!", "Do you want to CONTINUE?", "Please Select: ", "Yes", "No");
            if(tmp == 1){
                this->p2 = new Player(d_player);
            }else{
                delete map;
                this->p2 = new Player(s.append(m.md5(to_string(rand()))).substr(0, 7));
                map = new Map(*p1, *p2);
                this->p1->reset();
                p1->setMap(map->getId());
                p2->setMap(map->getId());   
            }
            
        }

    }

    this->p1->type = "PLAYER";
    this->p2->type = "AI";
    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

    return 0;

}



int Controller::getUsr(Player *&p){

    switchBox.title("Login ^_^");
    switchBox.print("","","");
    SetCursorPosition(26, 19);
    std::cout << "Press ESC to quit!!";
    SetCursorPosition(23, 12);
    std::string uName, uPasswd;
    std::cout << "Your Name = ";

    if(input(uName, 23 + 6, 12)) return 2;

    this->d_player = db.getData(uName);

    if(this->d_player["_isExist"] == "NO"){
        SetCursorPosition(26, 9);
        std::cout << "Hi~ New Visitor! " ;

        while(true){
            SetCursorPosition(23, 15);
            std::cout << "Set your Password =            ";
            std::string s1, s2;

            if(input(s1, 23 + 10, 15, "*")) return 2;

            SetCursorPosition(23, 15);
            std::cout << " REType Password  =            ";

            if(input(s2, 23 + 10, 15, "*")) return 2;

            if(s1 == s2){
                uPasswd = s1;
                break;
            }
            SetCursorPosition(23, 9);
            std::cout << "Two Passwords are NOT SAME!!" ;
            s1 = "";
            s2 = "";

        }

        p = new Player(uName, uPasswd);
        return 0;
    }

    p = new Player(this->d_player);

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



int Controller::input(std::string& uName, int x, int y, std::string star){

    char tmp;
    fflush(stdin);
    while((tmp = _getch()) && tmp != 13){
        std::stringstream ss;
        ss << tmp;

        if(tmp >= 33 && tmp <= 126 && uName.length() < 8) uName.append(ss.str());
        if(tmp == 8) uName = uName.substr(0, uName.length() - 1);
        SetCursorPosition(x,y);
        if(star == "") std::cout << uName << "        ";
        else{
            for(int i = 0; i < uName.length(); i ++){
                std::cout << star;
            }
            std::cout << "        ";
        };
        SetCursorPosition(x + uName.length() / 2, y);
        if(tmp == 27) {
            system("cls");
            return 2;
        }
        fflush(stdin);
    }
    SetCursorPosition(0, 31);

    return 0;
}



void Controller::printHint(){

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

void Controller::clearHint(){

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