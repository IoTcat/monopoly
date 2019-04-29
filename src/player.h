#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "../lib/ovo.h"
//#include "square.h"


class Player{

public:
    Player(std::string uName, std::string passwd, double balance){

        this->_uName = m.base64_encode(uName);
        this->_passwd = m.sha256(passwd);
        this->_balance = balance;
        this->type = "PLAYER";
        this->_map = " ";

        this->save();
    };
    Player(std::string uName, std::string passwd){

        this->_uName = m.base64_encode(uName);
        this->_passwd = m.sha256(passwd);
        this->_balance = 5000;
        this->type = "PLAYER";
        this->_map = " ";

        this->save();
    };
    Player(ovo::data d){

        this->_uName = d["_player_uName"];
        this->_passwd = d["_player_passwd"];
        this->_balance = atof(d["_player_balance"].c_str());
        this->_map = d["_player_map"];
        this->type = d["_player_type"];

        this->save();
    };
    Player(std::string ai_id){

        this->_uName = m.base64_encode(ai_id);
        this->_passwd = m.sha256(ai_id);
        this->_balance = 5000;
        this->type = "AI";
        this->_map = " ";

        this->save();
    }

    inline bool checkPasswd(std::string s){
        return (m.sha256(s) == this->_passwd) ? true : false;
    };
    void save();
    double cost(double fine);
    double gain(double money);
    void setMap(std::string t_map){
        this->_map = t_map;
    };
    std::string getMap(){
        return this->_map;
    };
    inline std::string getName(){
        return m.base64_decode(this->_uName);
    }

    inline double getBalance(){
        return this->_balance;
    };

    inline void reset(){
        this->_balance = 5000;
        this->_map = " ";
        this->save();
    }

    //void AI();

    std::string type;

private:
    std::string _uName;
    std::string _passwd;
    double _balance;
    std::string _map;
    ovo::data _d;
    ovo::math m;
    ovo::db db;

};


#endif