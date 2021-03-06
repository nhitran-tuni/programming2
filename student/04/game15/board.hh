/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Thuy Phuong Nhi Tran
 * Student number: 291937
 * UserID: mpthtr ( Necessary due to gitlab folder naming. )
 * E-Mail: thuyphuongnhi.tran@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <string>

const int SIZE = 4;

class Board
{
public:
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way

    // Prints the game grid
    void print();

    // Create game grid using random number generator
    void initalization_grid_shuffle (int seed);

    // Create game grid vector using input from the user
    void initalization_grid( std::vector<unsigned int>& input_numbers);

    // Movement of the input number
    void move_number(std::string Dir_commad, unsigned int Dir_number);

    // Check if the puzzle has been solved
    bool has_win();

    // Find position of EMPTY (dot)
    void find_position();

    // Check if the puzzle is initally solvable
    bool solvable();
    // More methods

private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

    // The position of the EMPTY (dot)
    unsigned int row_empty;
    unsigned int col_empty;

    // More attributes/methods
};

#endif // BOARD_HH
