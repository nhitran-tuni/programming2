#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
        // TODO: Implement your solution here
    }
}

// TODO: Implement your solution here
bool same_values(std::vector <int>& ints)
{
    int size = ints.size();
    bool check = 1;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (ints.at(i) != ints.at(j))
            {
                check = 0;
                break;
            }
        }
    }
    return check;
}

bool is_ordered_non_strict_ascending(std::vector <int>& ints)
{
    int size = ints.size();
    bool check = true;
    for (int i = 0; i <= size - 2; ++i)
    {
        if (ints.at(i) > ints.at (i+1))
        {
            check = false;
            break;
        }
    }
    return check;
}

bool is_arithmetic_series(std::vector <int>& ints)
{
    int size = ints.size();
    bool check = true;
    for (int i = 0; i <= size - 2; ++i)
    {
        if (ints.at(i+1) - ints.at(i) != ints.at(1) - ints.at(0))
        {
            check = false;
            break;
        }
    }
    return check;
}

bool is_geometric_series(std::vector <int>& ints)
{
    int size = ints.size();
    bool check = true;
    for (int i = 0; i <= size - 2; ++i)
    {
        if (ints.at(i+1) == ints.at(i) && ints.at(i) == 0)
        {
            check = false;
            break;
        }
        else for (int i = 0; i <= size - 2; ++i)
        {
            if (ints.at(i+1) / ints.at(i) != ints.at(1) / ints.at(0))
            {
                check = false;
                break;
            }
        }
    }
    return check;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);
//    std::cout << integers.size()<< std::endl;

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
