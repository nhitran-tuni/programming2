#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

bool check (std::string word_, std::string find_word)
{
    bool sign = true;
    for (unsigned int i = 0; i < word_.size(); ++i)
    {
        if(word_.at(i) == find_word.at(0))
        {
            sign = false;
            break;
        }
    }
    return sign;
}

unsigned int number (std::string value)
{
    unsigned int number_line = 0;
    for (unsigned int i = 0; i < value.size(); ++i)
        if(value.at(i) != ' ' and value.at(i) != ',')
        {
            ++number_line;
        }
    return number_line;
}

int main()
{
    std::string filename;
    std::cout << "Input file: ";
    getline(std::cin, filename);

    std::ifstream openfile(filename);

    if (not openfile)
    {
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::string line;
        std::map <std::string, std::string> word;
        unsigned int i = 1;

        while (getline(openfile, line))
        {
            char separator = ' ';
            std::string::size_type StartIndex, EndIndex;
            StartIndex = 0;
            EndIndex = line.find(separator, StartIndex);

            std::string line_num;

            while (EndIndex < line.size())
            {
                std::string part = line.substr(StartIndex, EndIndex - StartIndex);
                if (word.find(part) == word.end())
                {
                    word.insert( {part, std::to_string(i)} );
                }
                else if (check(word.at(part), std::to_string(i)))
                {
                    word.at(part) += ", " + std::to_string(i);
                }
                StartIndex = EndIndex + 1;
                EndIndex =line.find(separator, StartIndex);
            }

            if (StartIndex < line.size())
            {
                std::string part = line.substr(StartIndex);
                if (word.find(part) == word.end())
                {
                    word.insert( {part, std::to_string(i)} );
                }
                else if (check(word.at(part), std::to_string(i)))
                {
                    word.at(part) += ", " + std::to_string(i);
                }
            }
            ++i;
        }
        openfile.close();

        std::string output_str;
        for (auto ele : word)
        {
            unsigned int number_line = number(ele.second);
            std::cout << ele.first << " " << number_line << ": " << ele.second << std::endl;
        }
    }

    return 0;
}
