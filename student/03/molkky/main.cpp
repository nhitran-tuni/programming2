//#include "player.hh"
#include <cstdlib>
#include <iostream>
#include <string>

class Player {
private:
    std::string name_;
    int _score;
public:
    Player (std::string name, int score = 0);
    void add_points(int pst);
    bool has_won();
    int get_points();
    const std::string get_name() { return name_;}

};

Player::Player (std::string name, int score):
    name_(name), _score(score)
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


int main()
{
    Player player1 = Player("Matti");
    Player player2 = Player("Teppo");
    Player* in_turn = 0;

    int turn = 1;
    int score = 0;

    while (true)
    {
        if (turn % 2 != 0)
        {
            in_turn = &player1;
        }
        else
        { 
            in_turn = &player2;
        }

        std::cout << "Enter the score of player " << in_turn->get_name()
                  << " of turn " << turn << ": ";
        int pts = 0;
        std::cin >> pts;

        in_turn->add_points(pts);
        if (in_turn->has_won())
        {
            std::cout << "Game over! The winner is " << in_turn->get_name() << "!" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << std::endl;
        std::cout << "Scoreboard after turn " << turn << ":" << std::endl;
        std::cout << player1.get_name() << ": " << player1.get_points() << "p" << std::endl;
        std::cout << player2.get_name() << ": " << player2.get_points() << "p" << std::endl;
        std::cout << std::endl;

        turn += 1;
    }

    return EXIT_SUCCESS;
}
