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

void Controller::Select()//选择界面
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
    std::cout << "Easy" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "Normal" ;
    SetCursorPosition(27, 26);
    std::cout << "Difficult" ;
    SetCursorPosition(27, 28);
    std::cout << "Hell" ;
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
                    std::cout << "Easy" ;

                    SetCursorPosition(27, 24);//将已选中项取消我背景色
                    SetColor(3);
                    std::cout << "Normal   " ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "Normal" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Difficult" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Difficult" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "Hell" ;

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
                    std::cout << "Normal" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "Easy" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "Difficult" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "Easy" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "Hell" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "Difficult" ;

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

    switch (key)//根据所选选项设置蛇的移动速度，speed值越小，速度越快
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
}

void Controller::DrawGame()//绘制游戏界面
{
    system("cls");//清屏

    /*绘制地图*/
    SetColor(3);

    map = new Map();
    map->PrintInitmap();

    this->sb1->print(*p1);
    this->sb2->print(*p2);

}

int Controller::PlayGame()//游戏二级循环
{
    /*初始化蛇和食物*/

    srand((unsigned)time(NULL));//设置随机数种子，如果没有 食物的出现位置将会固定
    int ice_p1 = 0;
    int ice_p2 = 0;
    int tmp;

    /*游戏循环*/
    while (p1->getBalance() > 0 && p2->getBalance() > 0) //判断是否撞墙或撞到自身，即是否还有生命
    {


        hintBox.color(14);
        hintBox.print("MONOPOLY::PLAYER");
        if(!ice_p1){
            tmp = this->msgBox.print("Hi Player~", "It is YOUR turn.", "Please Select:", "Cast", "Quit");
            if(tmp == 2) return 2;

            tmp = this->roll.cast();
            Sleep(800);

            this->map->player_move(tmp);

            //this->hintBox.print(to_string(this->map->_map[this->map->_playerPos].getPrice()));

            //GO
            if(this->map->_map[map->_playerPos].type == GO){

                this->p1->gain(200);
                this->msgBox.print("Hi Player~", "You are into the GO zone..", "Gain $ 200 !!");

                this->UpdateScore();
                Sleep(1500);
            }else if(this->map->_map[map->_playerPos].type == JAIL){ //JAIL
                ice_p1 = 1;
                this->msgBox.print("Hi Player~", "You are into the JAIL zone..", "You need to wait for one round !!");
                Sleep(1500);
            }else if(this->map->_map[map->_playerPos].ownerType == ""){ //无人领地

                tmp = this->msgBox.print("Hi Player~", "This square is unoccupied.", "Do you want to BUY it?", "Yes", "No");
                if(tmp == 1){
                    this->map->_map[map->_playerPos].owner = p1->getName();
                    this->map->_map[map->_playerPos].ownerType = "PLAYER";
                    p1->cost(this->map->_map[this->map->_playerPos].getPrice());
                    this->map->_map[map->_playerPos].buy(*p1);

                    this->UpdateScore();
                }
            }else if(this->map->_map[map->_playerPos].ownerType == "PLAYER"){//玩家地盘

                tmp = this->msgBox.print("Hi Player~", "This square is occupied by you.", "Do you want to UPGRADE it?", "Yes", "No");
                if(tmp == 1){
                    this->map->_map[map->_playerPos].levelup();
                    this->map->_map[map->_playerPos].print();
                    this->p1->cost(this->map->_map[map->_playerPos]._price * .5);

                    this->UpdateScore();
                }
            }else if(this->map->_map[map->_playerPos].ownerType == "AI"){//ai地盘

                int t_price = this->map->_map[this->map->_playerPos].getPrice() * (1 + (this->map->_map[map->_playerPos - 1].ownerType == "AI" || this->map->_map[map->_playerPos + 1].ownerType == "AI")?.1 : 0);
                std::string t_s = "You need to PAY $ ";
                t_s += to_string(t_price);
                tmp = this->msgBox.print("Hi Player~", "This square is occupied by COMPUTER.", t_s);
                Sleep(1500);

                this->p1->cost(t_price);
                this->p2->gain(t_price);

                this->UpdateScore();
            }else{
                Sleep(800);
            }

        }else{
            ice_p1 = 0;
        }



        hintBox.color(13);
        hintBox.print("MONOPOLY::COMPUTER");
        if(!ice_p2){

            this->msgBox.print("Hi Player~", "It is Computer's turn.", "Please Wait..");
            Sleep(800);

            tmp = this->roll.cast();
            Sleep(800);

            map->ai_move(tmp);
            Sleep(300);

            //GO
            if(this->map->_map[map->_aiPos].type == GO){

                this->p2->gain(200);
                this->msgBox.print("WOW ~", "Computer into the GO zone..", "Gain $ 200 !!");
                this->UpdateScore();
                Sleep(1000);
            }else if(this->map->_map[map->_aiPos].type == JAIL){ //JAIL
                ice_p2 = 1;
                this->msgBox.print("AHA ...", "Computer are into the JAIL zone..", "He need to wait for one round !!");
                Sleep(1000);
            }else if(this->map->_map[map->_aiPos].ownerType == ""){ //无人领地

                tmp = this->msgBox.print("Lala..", "Computer Find a unoccupied space.", "What will he do?");
                Sleep(1500);
                tmp = rand() % 2;
                if(tmp == 1){
                    this->map->_map[map->_aiPos].owner = p2->getName();
                    this->map->_map[map->_aiPos].ownerType = "AI";
                    p2->cost(this->map->_map[this->map->_aiPos].getPrice());
                    this->map->_map[map->_aiPos].buy(*p2);
                    this->UpdateScore();
                    
                    tmp = this->msgBox.print("Lala..", "Computer Find a unoccupied space.", "The Computer BOUGHT it!!");
                    Sleep(1500);
                }else{
                    tmp = this->msgBox.print("Lala..", "Computer Find a unoccupied space.", "The Computer do NOTHING!!");
                    Sleep(1500);
                }
            }else if(this->map->_map[map->_aiPos].ownerType == "AI"){//玩家地盘

                tmp = this->msgBox.print("Ahm..", "Computer meet his own square.", "What will he do?");
                Sleep(1500);
                tmp = rand()%2;
                if(tmp == 1){
                    this->map->_map[map->_aiPos].levelup();
                    this->map->_map[map->_aiPos].print();
                    this->p2->cost(this->map->_map[map->_aiPos]._price * .5);
                    this->UpdateScore();
                    tmp = this->msgBox.print("Ahm..", "Computer meet his own square.", "The Computer UPGRADE it!!");
                    Sleep(1500);
                }else{
                    tmp = this->msgBox.print("Ahm..", "Computer meet his own square.", "The Computer do NOTHING!!");
                    Sleep(1500);
                }
            }else if(this->map->_map[map->_aiPos].ownerType == "PLAYER"){//ai地盘

                int t_price = this->map->_map[this->map->_aiPos].getPrice() * (1 + (this->map->_map[map->_aiPos - 1].ownerType == "PLAYER" || this->map->_map[map->_aiPos + 1].ownerType == "PLAYER")?.1 : 0);
                std::string t_s = "You GAIN $ ";
                t_s += to_string(t_price);
                tmp = this->msgBox.print("Xixi ^_^", "Computer meet your square..", t_s);
                Sleep(1500);

                this->p2->cost(t_price);
                this->p1->gain(t_price);
                this->UpdateScore();
            }else{
                Sleep(800);
            }


        }else{
            ice_p2 = 0;
        }

        /*调出选择菜单*/
 /*       if (0) //按Esc键时
        {
            int tmp = Menu();//绘制菜单，并得到返回值
            switch (tmp)
            {
            case 1://继续游戏
                break;

            case 2://重新开始
                delete csnake;
                delete cfood;
                return 1;//将1作为PlayGame函数的返回值返回到Game函数中，表示重新开始

            case 3://退出游戏
                delete csnake;
                delete cfood;
                return 2;//将2作为PlayGame函数的返回值返回到Game函数中，表示退出游戏

            default:
                break;
            }
        }*/
/*
        if (csnake->GetFood(*cfood)) //吃到食物
        {
            csnake->Move();//蛇增长
            UpdateScore(1);//更新分数，1为分数权重
            RewriteScore();//重新绘制分数
            cfood->DrawFood(*csnake);//绘制新食物
        }
        else
        {
            csnake->NormalMove();//蛇正常移动
        }

        if (csnake->GetBigFood(*cfood)) //吃到限时食物
        {
            csnake->Move();
            UpdateScore(cfood->GetProgressBar()/5);//分数根据限时食物进度条确定
            RewriteScore();
        }

        if (cfood->GetBigFlag()) //如果此时有限时食物，闪烁它
        {
            cfood->FlashBigFood();
        }

        Sleep(speed);//制造蛇的移动效果
        */
    }

    /*蛇死亡*/

    std::string t_score = "Your Score: ";
    t_score += this->score;
    tmp = this->msgBox.print("Game Over !!!", "You Lost!", "Play Again?", "OK", "Quit");//绘制游戏结束界面，并返回所选项
    hintBox.print("Press esc to quit");
    switch (tmp)
    {
    case 1:
        return 1;//重新开始
    case 2:
        return 2;//退出游戏
    default:
        return 2;
    }
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
    login();
    while (true)//游戏可视为一个死循环，直到退出游戏时循环结束
    {
        Select();//选择界面
        DrawGame();//绘制游戏界面
        int tmp = PlayGame();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
        if (tmp == 1) //返回值为1时重新开始游戏
        {
            system("cls");
            continue;
        }
        else if (tmp == 2) //返回值为2时退出游戏
        {
            break;
        }
        else
        {
            break;
        }
    }
}


void Controller::login(){

    /* 创建两个玩家 */
    this->p1 = new Player("yimian", "hhh");
    this->p2 = new Player("ai");

    this->sb1 = new Scoreboard(32, 20, 14);
    this->sb2 = new Scoreboard(42, 20, 13);

}