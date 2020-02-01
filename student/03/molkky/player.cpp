#include "player.hh"

Player::Player (std::string name):
    name_(name)
{}

void Player::add_points(int pst) {
    _score += pst;
    if(_score > 50) {
        _score = 25;
    }
}

bool Player::has_won() {
    if (_score == 50){
        return true;
    }
    else {
        return false;
    }
}

int Player::get_points() {
    return _score;
}
