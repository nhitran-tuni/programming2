/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <string>
#include <iostream>
#include <ctime>
#include <vector>

// More functions
std::string Check_Command()
{
    std::string command;
    std::cout << "Random initialization (y/n): ";
    getline(std::cin, command);
    while(command != "n" && command != "N" && command != "y" && command != "Y")
    {
        std::cout << "Unknown choice: " << command << std::endl;
        std::cout << "Random initialization (y/n): ";
        getline(std::cin, command);
    }
    return command;
}

std::vector <unsigned int> Read_input_numbers()
{
    std::vector<unsigned int> input_numbers;
    unsigned int new_integer = 0;
    std::cout << "Enter the numbers 1-16 in "
                 "a desired order (16 means empty):" << std::endl;
    for(int i = 0; i < 16; ++i)
    {
        std::cin >> new_integer;
        input_numbers.push_back(new_integer);
    }
    std::string newline;
    getline(std::cin, newline);
    return input_numbers;
}

int check_input_number (std::vector <unsigned int>& input_numbers)
{
    unsigned int check_array[17] = {0};
    unsigned int check_number = 0;
    check_array[1] = 0;
    for( unsigned int i = 0; i <= 15; ++i)
    {
        check_array[input_numbers.at(i)] = 1;
    }
    for (unsigned int j = 1; j <= 16; ++j)
    {
        if (check_array[j] == 0)
        {
            check_number = j;
            break;
        }
    }
    return check_number;
}

int main()
{
    // More functionality
    Board grid;
    std::string command = Check_Command();
    if (command == "y" ||  command == "Y")
    {
        std::string seed;
        std::cout << "Enter a seed value (or an empty line): ";
        getline(std::cin, seed);
        if(seed == "")
        {
            grid.initalization_grid_shuffle(time(0));
        }
        else
        {
            grid.initalization_grid_shuffle(stoi(seed));
        }
    }
    else if (command == "n" || command == "N")
    {
        std::vector<unsigned int> input_numbers = Read_input_numbers();
        unsigned int check_number = check_input_number(input_numbers);
        if(check_number != 0)
        {
            std::cout << "Number " << check_number <<
                         " is missing" << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            grid.initalization_grid(input_numbers);
        }
    }

    std::string Dir;
    while(true)
    {
        if (grid.solvable())
        {
            std::cout << "Game is solvable: Go ahead!" << std::endl;
            grid.print();
            if (grid.has_win())
            {
                std::cout << "You won!" << std::endl;
                return EXIT_SUCCESS;
            }

            std::cout << "Dir (command, number): ";
            getline(std::cin,Dir);

            if(Dir == "q")
            {
                return EXIT_SUCCESS;
            }
            else if (Dir[0] != 's' && Dir[0] != 'a' &&
                     Dir[0] != 'w' && Dir[0] != 'd')
            {
                std::cout << "Unknown command: " << Dir.at(0) << std::endl;
            }
            else if (stoi(Dir.substr(2)) <= 0 || stoi(Dir.substr(2)) > 16)
            {
                std::cout << "Invalid number: " << stoi(Dir.substr(2)) << std::endl;
            }
            else
            {
                grid.move_number(Dir);
            }
        }
        else
        {
            std::cout << "Game is not solvable. What a pity." << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
