
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package player
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "../lib/ovo.h"


/**
 * Player
 *
 * @author yimian
 * @category Monopoly Game
 * @package player
 */
class Player{

public:
    /* constructor for uname and password and balance */
    Player(const std::string& uName, const std::string& passwd, const double& balance){

        this->_uName = m.base64_encode(uName);
        this->_passwd = m.sha256(passwd);
        this->_balance = balance;
        this->type = "PLAYER";
        this->_map = " ";

        this->save();
    };
    /* constructor for default balance */
    Player(const std::string& uName, const std::string& passwd){

        this->_uName = m.base64_encode(uName);
        this->_passwd = m.sha256(passwd);
        this->_balance = 5000;
        this->type = "PLAYER";
        this->_map = " ";

        this->save();
    };
    /* recover from data */
    Player(ovo::data d){

        this->_uName = d["_player_uName"];
        this->_passwd = d["_player_passwd"];
        this->_balance = atof(d["_player_balance"].c_str());
        this->_map = d["_player_map"];
        this->type = d["_player_type"];

        this->save();
    };
    /* create ai */
    Player(const std::string& ai_id){

        this->_uName = m.base64_encode(ai_id);
        this->_passwd = m.sha256(ai_id);
        this->_balance = 5000;
        this->type = "AI";
        this->_map = " ";

        this->save();
    }

    /* cost */
    const double cost(const double& fine);
    /* gain */
    const double gain(const double& money);
    /* check password */
    inline const bool checkPasswd(const std::string& s){
        return (m.sha256(s) == this->_passwd) ? true : false;
    };
    /* link map */
    inline void setMap(const std::string& t_map){
        this->_map = t_map;
    };
    /* get linked map */
    inline const std::string getMap() const{
        return this->_map;
    };
    /* get name */
    inline const std::string getName(){
        return m.base64_decode(this->_uName);
    }
    /* get balance */
    inline const double getBalance(){
        return this->_balance;
    };
    /* reset player */
    inline void reset(){
        this->_balance = 5000;
        this->_map = " ";
        this->save();
    }

    /* store player type */
    std::string type;

private:
    std::string _uName;
    std::string _passwd;
    double _balance;
    std::string _map;
    ovo::data _d;
    ovo::math m;
    ovo::db db;

    /* save data */
    void save();

};


#endif //__PLAYER_H_