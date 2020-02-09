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
    std::vector<unsigned int> numbers;
    for(unsigned int i = 1; i <= 16; ++i)
    {
        numbers.push_back(i);
    }
    my_shuffle(numbers, seed);
    initalization_grid(numbers);
}

void Board::initalization_grid( std::vector<unsigned int>& input_numbers)
{
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

void Board:: move_number(std::string Dir)
{
    char Dir_command = Dir.at(0);
    unsigned int Dir_number = stoi(Dir.substr(2));
    unsigned int col, row, col_empty, row_empty;
    for(unsigned int x = 0; x < grid_.size(); ++x)
    {
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            if (Dir_number == this->grid_.at(x).at(y))
            {
                col = y;
                row = x;
            }
            if (EMPTY == this->grid_.at(x).at(y))
            {
                col_empty = y;
                row_empty = x;
            }
        }
    }
    if (Dir_command == 'a' && col - col_empty == 1)
    {
        this->grid_.at(row).at(col - 1) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == 'w' && row - row_empty == 1)
    {
        this->grid_.at(row - 1).at(col) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == 'd' && col_empty - col == 1)
    {
        this->grid_.at(row).at(col +1) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else if (Dir_command == 's' && row_empty - row == 1)
    {
        this->grid_.at(row + 1).at(col) = Dir_number;
        this->grid_.at(row).at(col) = EMPTY;
    }
    else
    {
        std::cout << "Impossible direction: " << Dir_command << std::endl;
    }
}

