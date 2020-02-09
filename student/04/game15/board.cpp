/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

void Board::initalization_grid_shuffle (int seed)
{
    // Create vector contains integers from 1 to 16.
    std::vector<unsigned int> numbers;
    for(unsigned int i = 1; i <= EMPTY; ++i)
    {
        numbers.push_back(i);
    }
    // Shuffle integers in vector.
    my_shuffle(numbers, seed);

    // Create two-dimensional vector grid.
    initalization_grid(numbers);
}

void Board::initalization_grid( std::vector<unsigned int>& input_numbers)
{
    // Break vector containing 16 integers into 4 smaller vectors.
    // Save those to game grid vector.
    unsigned int StarIndex = 0;
    unsigned int EndIndex = 3;
    while( EndIndex < input_numbers.size())
    {
        std::vector <unsigned int> row;
        for (unsigned int i = StarIndex; i <= EndIndex; ++i)
        {
            row.push_back(input_numbers.at(i));
        }
        this->grid_.push_back(row);
        StarIndex = EndIndex + 1;
        EndIndex += 4;
    }
}

void Board:: find_position()
{
    // Find the location of EMPTY elements.
    for(unsigned int x = 0; x < grid_.size(); ++x)
    {
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            if (EMPTY == this->grid_.at(x).at(y))
            {
                col_empty = y;
                row_empty = x;
            }
        }
    }
}

void Board:: move_number(std::string Dir_command, unsigned int Dir_number)
{
    // Find the location of the need-to-move input number.
    unsigned int col = 0, row = 0;
    for(unsigned int x = 0; x < grid_.size(); ++x)
    {
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            if (Dir_number == this->grid_.at(x).at(y))
            {
                col = y;
                row = x;
            }
        }
    }

    // Find the position of EMPTY element at this time.
    find_position();

    // Movement of input number depending on the command.
    if (Dir_command == "a" && col - col_empty == 1 && row == row_empty)
    {
        this->grid_.at(row).at(col - 1) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == "w" && row - row_empty == 1 && col == col_empty)
    {
        this->grid_.at(row - 1).at(col) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == "d" && col_empty - col == 1 && row == row_empty)
    {
        this->grid_.at(row).at(col +1) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == "s" && row_empty - row == 1 && col == col_empty)
    {
        this->grid_.at(row + 1).at(col) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    // Case when the number cannot move.
    else
    {
        std::cout << "Impossible direction: " << Dir_command << std::endl;
    }
}

bool Board::has_win()
{
    // Check if the puzzle has been solve
    for(unsigned int x = 0; x < grid_.size(); ++x)
    {
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            if(grid_.at(x).at(y) != (4 * x + y + 1))
            {
                return false;
                break;
            }
        }
    }
    return true;
}

bool Board:: solvable()
{
    // The function check if the inititial puzzle can be solvable

    //Find the position of EMPTY elements
    find_position();
    std::vector <unsigned int> check_solvable;
    unsigned int check_sum = 0;

    // Move the EMPTY element to the last row
    unsigned int swap_number = grid_.at(3).at(col_empty);
    this->grid_.at(3).at(col_empty) = EMPTY;
    this->grid_.at(row_empty).at(col_empty) = swap_number;

    // Check if the sum of inverse number is even or odd
    // Return if the puzzle can be solve
    for(unsigned int x = 0; x < grid_.size(); ++x)
    {
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            check_solvable.push_back(grid_.at(x).at(y));
        }
    }
    for (unsigned int i = 0; i < EMPTY; ++i)
    {
        for (unsigned int j = i +1; j < EMPTY - 1; ++j)
        {
            if (check_solvable[i] > check_solvable[j])
            {
                check_sum += 1;
            }
        }
    }
    if (check_sum % 2 == 0)
    {
        return true;
    }
    else
        return false;
}
