#include "player.hh"

Player::Player (std::string name){
    name_ = name ;
    _score = 0;
}

void Player::add_points(int pst) {
    _score += pst;
    if(_score > 50) {
        _score = 25;
    }
}

bool Player::has_won() {
    if (_score == 50){
        return 1;
    }
    else {
        return 0;
    }
}

int Player::get_points() {
    return _score;
}
