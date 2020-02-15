#include <iostream>
#include <string>
#include <map>
#include <fstream>

int main()
{
    std::string filename;
    std::cout << "Input file: ";
    getline(std::cin, filename);

    std::ifstream file_object(filename);

    if (not file_object)
    {
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::map <std::string, unsigned int> points;
        std::string line;
        char separator = ':';
        std::string::size_type EndIndex;

        while (getline(file_object,line))
        {
            EndIndex = line.find(separator, 0);
            if (points.find(line.substr(0, EndIndex)) == points.end())
            {
                points.insert({line.substr(0, EndIndex), (int)line.at(EndIndex + 1) });
            }
            else
            {
                points.at(line.substr(0, EndIndex)) += (int)line.at(EndIndex + 1);
            }
        }
        file_object.close();

        std::cout << "Final scores:" << std::endl;
        for (auto player : points)
        {
            std::cout << player.first << ": " << player.second << std::endl;
        }
    }
    return 0;
}
