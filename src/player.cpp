#include "player.h"


void Player::save(){

    this->_d.insert("_player_uName", this->_uName);
    this->_d.insert("_player_passwd", this->_passwd);
    this->_d.insert("_player_balance", this->_balance);
    this->_d.insert("_player_map", this->_map);


    db.pushData(this->_d, this->getName());
}

double Player::cost(double fine){

    this->_balance -= fine;
    if(this->_balance < 0) this->_balance = 0;
    this->save();
}

double Player::gain(double money){

    this->_balance += money;
    this->save();
}