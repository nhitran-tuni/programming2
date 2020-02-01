#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
class Player {
private:
    std::string name_;
    int _score;
public:
    Player (std::string name);
    void add_points(int pst);
    bool has_won();
    int get_points();
    const std::string get_name() { return name_;}

};

#endif // PLAYER_HH
