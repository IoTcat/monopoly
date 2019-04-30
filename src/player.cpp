
/**
 * Monopoly Game
 *
 * @category Monopoly Game
 * @package player
 * @copyright Copyright (c) 2019 yimian (https://yimian.xyz)
 * @license GNU General Public License 3.0
 * @version 0.0.1
 */

#include "player.h"

/**
 * save data
 *
 * @access private
 * @param void
 * @return void
 */
void Player::save(){

    this->_d.insert("_player_uName", this->_uName);
    this->_d.insert("_player_passwd", this->_passwd);
    this->_d.insert("_player_balance", this->_balance);
    this->_d.insert("_player_map", this->_map);
    this->_d.insert("_player_type", this->type);

    db.pushData(this->_d, this->getName());
}

/**
 * cost
 *
 * @access public
 * @param double& fine
 * @return double
 */
const double Player::cost(const double& fine){

    this->_balance -= fine;
    if(this->_balance < 0) this->_balance = 0;
    this->save();

    return this->_balance;
}

/**
 * gain
 *
 * @access public
 * @param double& fine
 * @return double
 */
const double Player::gain(const double& money){

    this->_balance += money;
    this->save();

    return this->_balance;
}