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
    // Check if the user's input command is valid or not
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
    // Read the input from the user and save them to a vector
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
    // The function check if user input is 16 distingushed integers from 1 to 16
    // If not the function returns the smallest integer which is missing
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

    // If the command is valid the programme continues
    // Else the programme raises error and exits
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

    // Check if the game grid is initially solvable
    // If not the programme teminates
    if (grid.solvable())
    {
        std::cout << "Game is solvable: Go ahead!" << std::endl;
        while(true)
        {
            grid.print();

            // If the puzzle is solved, the programme terminates
            if (grid.has_win())
            {
                std::cout << "You won!" << std::endl;
                return EXIT_SUCCESS;
            }

            std::cout << "Dir (command, number): ";
            getline(std::cin,Dir);

            // If the user's input is to quit, the programme terminates
            if(Dir == "q")
            {
                return EXIT_SUCCESS;
            }
            else
            {
                // Split the input string into 2 parts
                // The string command and integer need-to-move number
                char separator = ' ';
                std::string::size_type split_index = Dir.find(separator, 0);
                std::string Dir_command = Dir.substr(0, split_index);
                unsigned int Dir_number = stoi(Dir.substr(split_index + 1));

                // Require input again until the user's input is valid
                // Inform the user the invalid part of the invalid input
                if (Dir_command != "s" && Dir_command != "a" &&
                     Dir_command != "w" && Dir_command != "d")
                {
                    std::cout << "Unknown command: " << Dir_command << std::endl;
                }
                else if (Dir_number <= 0 || Dir_number > 16)
                {
                    std::cout << "Invalid number: " << Dir_number << std::endl;
                }
                else
                {
                    grid.move_number(Dir_command, Dir_number);
                }
            }
        }
    }
    else
    {
        std::cout << "Game is not solvable. What a pity." << std::endl;
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
